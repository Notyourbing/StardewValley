#include "FarmScene.h"

USING_NS_CC;

Scene* Farm::createScene() {
	return Farm::create();
}

bool Farm::init() {
	if (!Scene::init()) {
		return false;
	}
	// 获取屏幕大小和原点
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	// 添加背景图片
	auto background = Sprite::create("icon/farmBackground.png");
	if (background) {
		background->setPosition(origin.x + visibleSize.width / 2 , origin.y + visibleSize.height / 2);
		this->addChild(background, 0);
	}

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