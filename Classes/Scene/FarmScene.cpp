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
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	// 加载农场的瓦片地图
	auto map = TMXTiledMap::create("Maps/farm.tmx");
	if (map == nullptr) {
		return false;			//地图加载失败
	}
	map->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	map->setPosition(origin.x, origin.y);
	this->addChild(map, 0, "Map");

	// 保存地图信息
	auto mapSize = map->getContentSize();


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

	// 初始化键盘监听器
	initKeyboardListener();

	// 定时器，用于更新地图位置
	schedule([this](float dt) {
		updateMapPosition();
		}, "update_map_position");

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

void Farm::updateMapPosition() {
	auto mapNode = this->getChildByName("Map");
	auto map = dynamic_cast<TMXTiledMap*>(mapNode); // 转换为 TMXTiledMap*
	auto player = Player::getInstance();

	if (!map || !player) {
		return;
	}

	// 获取地图和屏幕尺寸
	auto mapSize = map->getContentSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// 玩家当前位置
	Vec2 playerPos = player->getPosition();

	// 我真是服了，这个地图的锚点在左下角！！！我还以为和精灵一样在中心

	float offsetX = playerPos.x - visibleSize.width / 2;
	float offsetY = playerPos.y - visibleSize.height / 2;
	if (offsetX >= (mapSize.width - visibleSize.width) / 2) {
		offsetX = (mapSize.width - visibleSize.width) / 2;
	}
	if (offsetX <= -(mapSize.width - visibleSize.width) / 2) {
		offsetX = -(mapSize.width - visibleSize.width) / 2;
	}
	if (offsetY >= (mapSize.height - visibleSize.height) / 2) {
		offsetY = (mapSize.height - visibleSize.height) / 2;
	}
	if (offsetY <= -(mapSize.height - visibleSize.height) / 2) {
		offsetY = -(mapSize.height - visibleSize.height) / 2;
	}
	const float currentX = -(mapSize.width - visibleSize.width) / 2 - offsetX;
	const float currentY = -(mapSize.height - visibleSize.height) / 2 - offsetY;
	map->setPosition(-(mapSize.width - visibleSize.width) / 2 -offsetX, -(mapSize.height - visibleSize.height) / 2 - offsetY);
}