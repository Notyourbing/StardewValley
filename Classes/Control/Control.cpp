#include "Control.h"
#include "../Constant/Constant.h"
#include "../Map/FarmMap.h"
#include "../Bag/Bag.h"
#include "../Player/Player.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../Skill/SkillTreeUI.h"

USING_NS_CC;

// 构造函数
Control::Control() : sceneMap(nullptr) {}

// 析构函数
Control::~Control() {}

// 静态创建Control方法
Control* Control::create(SceneMap* sceneMap) {
	Control* control = new(std::nothrow) Control();
	if (control  && sceneMap && control->init(sceneMap)) {
		control->autorelease();
		return control;
	}
	CC_SAFE_DELETE(control);
	return nullptr;
}

// 初始化
bool Control::init(SceneMap* sceneMap) {
	if (!Node::init()) {
		return false;
	}
	this->sceneMap = sceneMap;
	initKeyboardListener();
	initMouseListener();
	return true;
}

// 根据按下的键来更新玩家和地图移动的方向
void Control::updateMovement() {
	Vec2 direction = Vec2::ZERO;

	// 检查按键集合，根据按下的键计算方向
	if (keysPressed.count(EventKeyboard::KeyCode::KEY_W)) { // 上
		direction.y = 1;
	}
	else if (keysPressed.count(EventKeyboard::KeyCode::KEY_S)) { // 下
		direction.y = -1;
	}
	if (keysPressed.count(EventKeyboard::KeyCode::KEY_A)) { // 左
		direction.x = -1;
	}
	else if (keysPressed.count(EventKeyboard::KeyCode::KEY_D)) { // 右
		direction.x = 1;
	}

	// 归一化方向，避免斜方向移动速度过快
	if (direction != Vec2::ZERO) {
		direction.normalize();
	}

	// 更新玩家和地图的移动方向
	auto player = Player::getInstance();
	auto mapMoveDirection = -direction;
	if (sceneMap) {
		sceneMap->moveMapByDirection(mapMoveDirection);
	}
	if (player) {
		player->moveByDirection(direction);
	}
}

// 初始化键盘监听器
void Control::initKeyboardListener() {
	// 创建键盘事件监听器
	auto listener = EventListenerKeyboard::create();
	// 获取技能树UI界面层
	auto skillTreeLayer = SkillTreeUI::getInstance();
	addChild(skillTreeLayer);
	listener->onKeyPressed = [this, skillTreeLayer](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_E) {
			if (SkillTreeUI::isOpen == false) {
				skillTreeLayer->setVisible(true);
				skillTreeLayer->openSkillUI();
				SkillTreeUI::isOpen = true;
				Player::getInstance()->setUseItemEnable(false);
			}
			else {
				skillTreeLayer->setVisible(false);
				SkillTreeUI::isOpen = false;
				Player::getInstance()->setUseItemEnable(true);
			}
		}
		if (keyCode >= EventKeyboard::KeyCode::KEY_1 && keyCode <= EventKeyboard::KeyCode::KEY_9) {
			const int index = static_cast<int>(keyCode) - static_cast<int>(EventKeyboard::KeyCode::KEY_1);
			Bag::getInstance()->setSelectedItem(index);
		}
		keysPressed.insert(keyCode);
		updateMovement(); // 根据当前按下的键计算方向
		};

	// 松开键时从 keysPressed 移除
	listener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
		keysPressed.erase(keyCode);
		// 停止玩家移动
		Player::getInstance()->stopMoving();
		updateMovement(); // 更新方向
		};

	// 添加监听器到事件分发器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// 初始化鼠标监听器
void Control::initMouseListener() {
	// 创建鼠标事件监听器
	auto listener = EventListenerMouse::create();

	// 监听鼠标滚轮
	listener->onMouseScroll = [this](Event* event) {
		auto mouseEvent = dynamic_cast<EventMouse*>(event);
		const int scrollY = static_cast<int>(mouseEvent->getScrollY()); // 垂直滚轮值
		auto bag = Bag::getInstance();
		int targetIndex = bag->getSelectedIndex() + scrollY;
		if (targetIndex < 0) {
			targetIndex = 0;
		}
		if (targetIndex > bag->getSize() - 1) {
			targetIndex = bag->getSize() - 1;
		}
		bag->setSelectedItem(targetIndex);
		};

	// 监听鼠标按下
	listener->onMouseDown = [this](Event* event) {
		auto mouseEvent = dynamic_cast<EventMouse*>(event);
		Player* player = Player::getInstance();
		if (mouseEvent && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			if (DialogueBox::isDialogueVisible == false) {
				player->stopMoving();
				sceneMap->stopMoving();
				player->useCurrentItem();
				sceneMap->interactWithMap();
			}
		}
		else if (mouseEvent && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
			for (auto npc : Farm::npcs) {
				// 计算玩家与NPC的距离
				const float distance = player->getPosition().distance(npc->getPosition() + sceneMap->getPosition());

				// 当距离小于交互距离并且此时对话框没有显示
				if (distance < INTERACTION_RANGE && DialogueBox::isDialogueVisible == false) {
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