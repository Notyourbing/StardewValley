/****************************************************************
 * File Function: 实现农场场景类，继承自Scene，是游戏的主要场景
 *				  农场中有npc，玩家可以耕种，养殖，钓鱼，砍树，交易等。
 * Author:        赵卓冰
 ****************************************************************/
#include "FarmScene.h"
#include "../Map/BeachMap.h"
#include "../Map/CaveMap.h"
#include "../Map/ForestMap.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "../MyButton/MyButton.h"
#include "../Control/Control.h"
#include "../DialogueBox/DialogueBox.h"
#include "../Weather/WeatherManager.h"
#include "../Save/SaveManage.h"
#include "../Npc/NoticeBoard.h"
#include "../Item/ItemFactory.h"

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
	Control* farmControl = Control::create(farmMap);
	if (farmControl) {
		addChild(farmControl, 4, "farm_control");
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
		farmMap->mapUpdateByTime();
		weatherManager->updateWeather(dateManage->getCurrentWeather());
		}, 5.0f, "update_date_key");

	// 每帧检测是否要切换场景
	schedule([this](float dt) {
		this->changeSceneAuto();
		}, "change_scene");

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

// 获取地图上所有的npc
std::vector<Npc*> Farm::getNpcs(){
	return npcs;
}

// 根据人物的位置自动从农场场景切换到其他四个场景
void Farm::changeSceneAuto() {
	// 计算人物在地图中的位置
	auto player = Player::getInstance();
	auto farmMap = FarmMap::getInstance();
	const auto positionInMap = player->getPosition() - farmMap->getPosition();
	const auto farmMapSize = farmMap->getMapSize();

	// 人物的朝向
	const auto playerDirection = player->getLastDirection();

	// 当前是农场地图
	if (getChildByName("farm_control")) {
		// 人物走向不同的边界进入不同的新地图
		if (playerDirection == Vec2(0, -1) && positionInMap.y < CHANGE_MAP_DISTANCE) {
			// 移除对农场的控制
			removeChildByName("farm_control");

			// 添加对沙滩的控制
			auto beachMap = BeachMap::getInstance();
			if (beachMap) {
				addChild(beachMap, 1, "beach_map");
				Control* beachControl = Control::create(beachMap);
				if (beachControl) {
					addChild(beachControl, 5, "beach_control");
					// 来到海滩获得新工具鱼竿
					auto bag = Bag::getInstance();
					// 如果背包中没有鱼竿，则获得工具鱼竿
					if (!bag->checkItemIn("fishingRod")) {
						auto fishingRod = ItemFactory::createItem("fishingRod");
						bag->addItem(fishingRod);
					}
				}
			}

			// 把人物从下边界转移到沙滩地图的上边界，实现平滑过渡
			const float newPlayerPosX = player->getPositionX();
			const float newPlayerPosY = WINSIZE.height - player->getPositionY();
			player->setPosition(Vec2(newPlayerPosX, newPlayerPosY));
		}
		else if (playerDirection == Vec2(0, 1) && positionInMap.y > farmMapSize.height - CHANGE_MAP_DISTANCE) {
			// 移除对农场的控制
			removeChildByName("farm_control");

			// 添加对洞穴的控制
			auto caveMap = CaveMap::getInstance();
			if (caveMap) {
				addChild(caveMap, 1, "cave_map");
				Control* caveControl = Control::create(caveMap);
				if (caveControl) {
					addChild(caveControl, 5, "cave_control");

					// 来到洞穴获得新工具十字镐
					auto bag = Bag::getInstance();
					if (!bag->checkItemIn("pickaxe")) {
						auto pickaxe = ItemFactory::createItem("pickaxe");
						bag->addItem(pickaxe);
					}
					// 把人物从下边界转移到洞穴地图的下边界，实现平滑过渡
					const float newPlayerPosX = player->getPositionX();
					const float newPlayerPosY = CHANGE_MAP_DISTANCE;
					player->setPosition(Vec2(newPlayerPosX, newPlayerPosY));
				}
			}

		}
		else if (playerDirection == Vec2(1, 0) && positionInMap.x > farmMapSize.width - CHANGE_MAP_DISTANCE) {
			// 移除对农场的控制
			removeChildByName("farm_control");

			// 添加对森林的控制
			auto forestMap = ForestMap::getInstance();
			if (forestMap) {
				addChild(forestMap, 1, "forest_map");
				Control* forestControl = Control::create(forestMap);
				if (forestControl) {
					addChild(forestControl, 5, "forest_control");
					// 把人物从下边界转移到洞穴地图的下边界，实现平滑过渡
					const float newPlayerPosX = CHANGE_MAP_DISTANCE;
					const float newPlayerPosY = player->getPositionY();
					player->setPosition(Vec2(newPlayerPosX, newPlayerPosY));
				}
			} 
		}


	}

	// 当前是海滩地图
	if (getChildByName("beach_control")) {
		auto beachMap = BeachMap::getInstance();
		const auto positionInBeachMap = player->getPosition() - beachMap->getPosition();
		const auto beachMapSize = beachMap->getMapSize();
		// 如果人物走向上边界
		if (playerDirection == Vec2(0, 1) && positionInBeachMap.y > beachMapSize.height - 2 * CHANGE_MAP_DISTANCE) {
			removeChildByName("beach_control");
			removeChildByName("beach_map");
			Control* farmControl = Control::create(farmMap);
			addChild(farmControl, 5, "farm_control");

			// 把人物从上边界转移到下边界
			const float newPlayerPosX = player->getPositionX();
			const float newPlayerPosY = WINSIZE.height - player->getPositionY();
			player->setPosition(Vec2(newPlayerPosX, newPlayerPosY));
		}
	}

	// 当前是洞穴地图
	if (getChildByName("cave_control")) {
		auto caveMap = CaveMap::getInstance();
		const auto positionInCaveMap = player->getPosition() - caveMap->getPosition();

		// 如果人物走向下边界
		if (playerDirection == Vec2(0, -1) && positionInCaveMap.y < CHANGE_MAP_DISTANCE) {
			removeChildByName("cave_control");
			removeChildByName("cave_map");
			Control* farmControl = Control::create(farmMap);
			addChild(farmControl, 5, "farm_control");

			// 把人物从下边界转移到上边界
			const float newPlayerPosX = player->getPositionX();
			const float newPlayerPosY = WINSIZE.height - player->getPositionY();
			player->setPosition(Vec2(newPlayerPosX, newPlayerPosY));
		}
	}

	// 当前是森林地图
	if (getChildByName("forest_control")) {
		auto forestMap = ForestMap::getInstance();
		const auto positionInForestMap = player->getPosition() - forestMap->getPosition();

		// 如果人物走向左边界
		if (playerDirection == Vec2(-1, 0) && positionInForestMap.x < CHANGE_MAP_DISTANCE) {
			removeChildByName("forest_control");
			removeChildByName("forest_map");
			Control* farmControl = Control::create(farmMap);
			addChild(farmControl, 5, "farm_control");

			// 把人物从左边界转移到右边界
			const float newPlayerPosX = WINSIZE.width - CHANGE_MAP_DISTANCE;
			const float newPlayerPosY = player->getPositionY();
			player->setPosition(Vec2(newPlayerPosX, newPlayerPosY));
		}
	}
}

