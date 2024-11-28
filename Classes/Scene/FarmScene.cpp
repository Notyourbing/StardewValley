#include "FarmScene.h"
#include "../Map/FarmMap.h"
#include "../Npc/Npc.h"


USING_NS_CC;

Scene* Farm::createScene() {
	return Farm::create();
}

bool Farm::init() {
	if (!Scene::init()) {
		return false;
	}

	// 获取屏幕大小和原点
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto farmMap = FarmMap::getInstance();
	if (!farmMap->init("Maps/farmSpring11_28/farmSpring11_28.tmx")) {
		return false;
	}
	const auto farmMapSize = farmMap->getMapSize();
	farmMap->setPosition(visibleSize.width / 2 -farmMapSize.width / 2, visibleSize.height / 2 -farmMapSize.height / 2);
	this->addChild(farmMap, 0);

	// 创建NPC
	
	Npc* wizard = new Npc("Wizard Yuuu", "Fall 5",
		{ "Magic Essence", "Diamond" },
		{ "Milk" },
		{ "Get out of my way", "How are you?","I like to spend time with you." },
		{ "npcImages/wizard.png" },
		Vec2(origin.x + 420, origin.y + 300));  // 传入图像路径

	Npc* cleaner = new Npc("Cleaner Levi", "Winter 25",
		{ "Milk", "Cleaning tools" },
		{ "Clay" },
		{ "...", "Ahh, hi.","Come and have some black-tea with me." },
		{ "npcImages/cleaner.png" },
		Vec2(origin.x + 300, origin.y + 300));
	farmMap->npcInit(Vec2(origin.x + 300, origin.y + 300), wizard);
	farmMap->npcInit(Vec2(origin.x + 370, origin.y + 300), cleaner);

	//设置NPC的关系
	wizard->setNpcRelation("cleaner", RelationshipStatus::Romance);
	cleaner->setNpcRelation("wizard", RelationshipStatus::Romance);


	// 获取玩家单例并添加到场景中
	auto player = Player::getInstance();
	player->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2); // 初始位置
	this->addChild(player, 3);

	// 显示玩家名字
	auto nameLabel = Label::createWithTTF(player->getPlayerName() + "'s farm", "fonts/Marker Felt.ttf", 24);
	if (nameLabel) {
		nameLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 50));
		this->addChild(nameLabel, 4);
	}

	// 初始化键盘和鼠标监听器
	initKeyboardListener();
	initMouseListener();
	return true;
}

void Farm::initKeyboardListener() {
	// 创建键盘事件监听器
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
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

void Farm::updateMovement() {
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
	auto farmMap = FarmMap::getInstance();
	auto farmDirection = -direction;
	farmMap->moveMapByDirection(farmDirection);
	player->moveByDirection(direction);
}

void Farm::initMouseListener() {
	auto listener = EventListenerMouse::create();

	listener->onMouseDown = [](Event* event) {
		auto mouseEvent = dynamic_cast<EventMouse*>(event);
		if (mouseEvent && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			Player::getInstance()->useCurrentTool();
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

