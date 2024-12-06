#include "FarmScene.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "../MyButton/MyButton.h"
#include "../Control/Control.h"
#include "../DialogueBox/DialogueBox.h"

USING_NS_CC;

Scene* Farm::createScene() {
	return Farm::create();
}

bool Farm::init() {
	if (!Scene::init()) {
		return false;
	}
	DateManage* dateManage = DateManage::getInstance();
	// 启动一个定时器，每秒调用一次 updateDate 方法
	schedule([this, dateManage](float deltaTime) {
		dateManage->updateDate();
		}, 1.0f, "update_date_key");

	auto farmMap = FarmMap::getInstance();
	if (!farmMap->init("Maps/farmSpring11_28/farmMap.tmx")) {
		return false;
	}

	const auto farmMapSize = farmMap->getMapSize();
	farmMap->setPosition(WINSIZE.width / 2 -farmMapSize.width / 2, WINSIZE.height / 2 -farmMapSize.height / 2);
	this->addChild(farmMap, 0);

	// 创建 NPC 示例
	Npc* wizard = new Npc(WIZARD);
	Npc* cleaner = new Npc(CLEANER);
	cleaner->increaseFriendship(90); // 亲密度90
	npcs.push_back(cleaner);
	npcs.push_back(wizard);
	farmMap->npcInit(Vec2(WIZARD_X, WIZARD_Y), wizard);
	farmMap->npcInit(Vec2(CLEANER_X, CLEANER_Y), cleaner);
	DialogueBox::isDialogueVisible = false;

	// 玩家
	auto player = Player::getInstance();
	player->setPosition(WINSIZE.width / 2, WINSIZE.height / 2); // 玩家初始位置在屏幕中央
	this->addChild(player, 3);

	// 玩家名字
	auto nameLabel = Label::createWithTTF(player->getPlayerName() + "'s farm", "fonts/Marker Felt.ttf", 24);
	if (nameLabel) {
		nameLabel->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height - 50));
		this->addChild(nameLabel, 4);
	}

	// 背包
	Bag* bag = Bag::getInstance();
	if (bag) {
		this->addChild(bag, 4);
	}

	// 退出按钮
	auto closeButton = MyButton::create(ResPath::CLOSE_BUTTON_NORMAL, ResPath::CLOSE_BUTTON_HOVER);
	if (closeButton) {
		const auto closeButtonSize = closeButton->getContentSize();
		closeButton->setPosition(Vec2(closeButtonSize.width / 2, WINSIZE.height - closeButtonSize.height / 2)); // 放在左上角
		this->addChild(closeButton, 4);
		closeButton->addClickEventListener(CC_CALLBACK_1(Farm::closeButtonClicked, this));
	}

	// 初始化键盘监听器
	// initKeyboardListener();

	Control* control = Control::create();
	this->addChild(control, 4);

	 // 初始化鼠标监听器
	 initMouseListener();
	 // 创建显示日期的标签
	 if (dateManage->dateLabel) {
		 dateManage->dateLabel->setPosition(Vec2(WINSIZE.width - 100, WINSIZE.height - 40));  // 右上角位置
		 this->addChild(dateManage->dateLabel, 5);
	 }
	return true;
}

void Farm::initMouseListener()
{
	// 创建鼠标事件监听器
	auto listener = EventListenerMouse::create();

	listener->onMouseDown = [this](Event* event) {
		auto mouseEvent = dynamic_cast<EventMouse*>(event);
		Player* player = Player::getInstance();
		FarmMap* farmMap = FarmMap::getInstance();
		player->stopMoving();
		farmMap->stopMoving();
		if (mouseEvent && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			if (DialogueBox::isDialogueVisible == false) {
				player->useCurrentTool();
				farmMap->interactWithFarmMap();
			}
		}
		else if (static_cast<EventMouse*>(event)->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
			for (auto npc : npcs) {
				// 计算玩家与NPC的距离
				const float distance = player->getPosition().distance(npc->sprite->getPosition() + farmMap->getPosition());
				// 设定一个合适的距离阈值
				const float interactionRange = 100.0f;  // 可调整的阈值，表示玩家与 NPC 之间的最大交互距离
				if (distance < interactionRange && DialogueBox::isDialogueVisible == false) {
					if (!DialogueBox::isDialogueVisible) {
						DialogueBox* dialogueBox = DialogueBox::create(npc);
						this->addChild(dialogueBox, 5);
						dialogueBox->showInitialDialogue();
						break;
					}
				}
			}
		}
		};
	
	// 添加鼠标事件监听器到事件分发器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


// 关闭按钮的回调函数
void Farm::closeButtonClicked(Ref* pSender) {
	Director::getInstance()->popScene();
}

// 动物管理
void Farm::animalManager() {

}