#include "FarmScene.h"

USING_NS_CC;

Scene* Farm::createScene() {
	auto scene = new (std::nothrow) Farm();
	// 二段构建
	if (scene && scene->init()) {
		scene->autorelease();
		return scene;
	}
	else {
		delete scene;
		scene = nullptr;
		return nullptr;
	}
}

bool Farm::init() {
	if (!Scene::init()) {
		return false;
	}
	// 获取屏幕大小和原点
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	// 加载农场的瓦片地图

	auto map = TMXTiledMap::create("Scene/FarmScene.tmx");

	if (map == nullptr) {
		return false;			//地图加载失败
	}
	this->addChild(map, 0, 99);

	auto mapSize = map->getContentSize();
	auto winSize = Director::getInstance()->getVisibleSize();

	const float x = winSize.width / 2.0f - mapSize.width / 2.0f;
	const float y = winSize.height / 2.0f - mapSize.height / 2.0f;

	map->setPosition(Vec2(x, y));


	// 获取玩家单例并添加到场景中
	auto player = Player::getInstance();
	player->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2); // 初始位置
	this->addChild(player, 3);

	// 显示玩家名字
	auto nameLabel = Label::createWithTTF(player->getName(), "fonts/Marker Felt.ttf", 24);
	if (nameLabel) {
		nameLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 50));
		this->addChild(nameLabel, 2);
	}

	// 初始化键盘监听器
	initKeyboardListener();

	return true;
}

void Farm::initKeyboardListener() {
	// 创建键盘事件监听器
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
		Vec2 direction = Vec2::ZERO;

		// 根据按键设置方向
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_W:  // 上
			direction.y = 1;
			break;
		case EventKeyboard::KeyCode::KEY_S:  // 下
			direction.y = -1;
			break;
		case EventKeyboard::KeyCode::KEY_A:  // 左
			direction.x = -1;
			break;
		case EventKeyboard::KeyCode::KEY_D:  // 右
			direction.x = 1;
			break;
		default:
			break;
		}

		Player::getInstance()->moveByDirection(direction);
		};

	listener->onKeyReleased = [](EventKeyboard::KeyCode KeyCode, Event* event) {
		// 停止玩家移动
		Player::getInstance()->stopMoving();
		};

	// 添加监听器到事件分发器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}