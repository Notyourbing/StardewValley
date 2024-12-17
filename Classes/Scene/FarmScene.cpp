#include "FarmScene.h"
#include "../Map/BeachMap.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "../MyButton/MyButton.h"
#include "../Control/Control.h"
#include "../DialogueBox/DialogueBox.h"
#include "../DateManage/WeatherManager.h"
#include "../SaveManage/SaveManage.h"

USING_NS_CC;

// 地图上的npc;
std::vector<Npc*> Farm::npcs;

// 创建场景，静态函数
Scene* Farm::createScene() {
	return Farm::create();
}

// 初始化农场场景
bool Farm::init() {
	// 首先初始化父类
	if (!Scene::init()) {
		return false;
	}

	// 农场地图
	FarmMap* farmMap = FarmMap::getInstance();
	if (farmMap) {
		addChild(farmMap, 0);
	}
	                                                               
	// 两个NPC
	Npc* wizard = Npc::create(WIZARD_INFO);
	Npc* cleaner = Npc::create(CLEANER_INFO);
	if (wizard && cleaner) {
		npcs.push_back(cleaner);
		npcs.push_back(wizard);
		farmMap->npcInit(Vec2(WIZARD_X, WIZARD_Y), wizard);
		farmMap->npcInit(Vec2(CLEANER_X, CLEANER_Y), cleaner);
	}

	// 玩家
	auto player = Player::getInstance();
	if (player) {
		addChild(player, 3);
	}
	player->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);

	// 玩家名字标签
	auto nameLabel = Label::createWithTTF(player->getPlayerName() + "'s farm", ResPath::FONT_TTF, 24);
	if (nameLabel) {
		nameLabel->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height - 50));
		addChild(nameLabel, 4);
	}

	// 背包
	Bag* bag = Bag::getInstance();
	if (bag) {
		addChild(bag, 4);
	}

	// 退出按钮
	auto closeButton = MyButton::create(ResPath::CLOSE_BUTTON_NORMAL, ResPath::CLOSE_BUTTON_HOVER);
	if (closeButton) {
		const Size closeButtonSize = closeButton->getContentSize();
		closeButton->setPosition(Vec2(closeButtonSize.width / 2, WINSIZE.height - closeButtonSize.height / 2)); // 放在左上角
		addChild(closeButton, 4);
		closeButton->addClickEventListener(CC_CALLBACK_1(Farm::closeButtonClicked, this));
	}

	// 控制鼠标和键盘的交互
	Control* control = Control::create();
	if (control) {
		addChild(control, 4);
	}

	// 日期管理
	DateManage* dateManage = DateManage::getInstance();
	if (dateManage) {
		addChild(dateManage, 5);
	}

	// 天气管理
	WeatherManager* weatherManager = WeatherManager::create();
	if (weatherManager) {
		addChild(weatherManager, 5);
	}

	// 启动定时器，每秒调用一次 updateDate 方法
	schedule([this, dateManage, farmMap,weatherManager](float deltaTime) {
		dateManage->updateDate();
		farmMap->farmMapTimeUpdate();
		weatherManager->updateWeather(dateManage->getCurrentWeather());
		this->changeSceneAuto();
		}, 1.0f, "update_date_key");

	return true;
}

// 关闭按钮的回调函数
void Farm::closeButtonClicked(Ref* pSender) {
	SaveManage::getInstance()->saveGameData();
	Director::getInstance()->popScene();
}

// 析构函数，防止npcs中存在野指针
Farm::~Farm() {
	npcs.clear();
}

// 根据人物的位置自动从农场场景切换到其他四个场景
void Farm::changeSceneAuto() {
	// 计算人物在地图中的位置
	auto player = Player::getInstance();
	auto farmMap = FarmMap::getInstance();
	const auto positionInMap = player->getPosition() - farmMap->getPosition();

	// 人物的朝向
	const auto playerDirection = player->getLastDirection();

	// 人物走向下边界
	if (playerDirection == Vec2(0, -1) && positionInMap.y < 80.0f) {
		auto beachMap = BeachMap::getInstance();
		addChild(beachMap, 1);
	}
}
