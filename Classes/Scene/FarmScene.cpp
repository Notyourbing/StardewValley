#include "FarmScene.h"
#include "../Map/FarmMap.h"

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
	if (!farmMap->init("Maps/farm.tmx")) {
		return false;
	}
	const auto farmMapSize = farmMap->getMapSize();
	farmMap->setPosition(visibleSize.width / 2 - farmMapSize.width / 2, visibleSize.height / 2 - farmMapSize.height / 2);
	this->addChild(farmMap, 0);

	// 加载TMX地图
	tmxMap = TMXTiledMap::create("Maps/farm.tmx");
	if (!tmxMap) {
		return false; // 地图加载失败时返回 false
	}

	// 初始化图层
	initLayers();

	

	// 初始化瓦片节点
	//initTileNodes();

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
		direction.y += 1;
	}
	if (keysPressed.count(EventKeyboard::KeyCode::KEY_S)) { // 下
		direction.y -= 1;
	}
	if (keysPressed.count(EventKeyboard::KeyCode::KEY_A)) { // 左
		direction.x -= 1;
	}
	if (keysPressed.count(EventKeyboard::KeyCode::KEY_D)) { // 右
		direction.x += 1;
	}

	// 归一化方向，避免斜方向移动速度过快
	if (direction != Vec2::ZERO) {
		direction.normalize();
	}

	// 获取玩家实例
	auto player = Player::getInstance();
	Vec2 currentPlayerPosition = player->getPosition();


	// 计算新的位置
	Vec2 newPosition = currentPlayerPosition + direction;

	// 检查新位置是否会发生碰撞
	if (isCollidingWithTile(newPosition)) {
		direction = Vec2::ZERO;
	}

	// 更新玩家和地图的移动方向
	auto farmMap = FarmMap::getInstance();
	farmMap->moveMapByDirection(-direction);
	player->moveByDirection(direction);
}

void Farm::initLayers(){
	// 初始化背景层
	backgroundLayer = tmxMap->getLayer("background");

	// 初始化碰撞层
	collisionLayer = tmxMap->getLayer("Block");
}

void Farm::initTileNodes() {
	// 地图大小
	const Size mapSize = tmxMap->getMapSize();

	// 遍历需要处理的图层
	for (const auto& layerName : { "Background", "Collision", "Interact" }) {
		TMXLayer* layer = tmxMap->getLayer(layerName);
		if (!layer) continue;

		for (int x = 0; x < mapSize.width; ++x) {
			for (int y = 0; y < mapSize.height; ++y) {
				Vec2 tileCoord(x, y);
				auto tile = layer->getTileAt(tileCoord);

				if (tile) {
					// 创建瓦片节点
					auto tileNode = createTileNode(layerName, tileCoord);
					if (tileNode) {
						tileNodes.push_back(tileNode);
						this->addChild(tileNode.get());
					}
				}
			}
		}
	}
}

std::shared_ptr<TileNode> Farm::createTileNode(const std::string& layerName, const Vec2& position) {
	std::shared_ptr<TileNode> tileNode = nullptr;

	if (layerName == "Background Layer") {
		tileNode = std::make_shared<Soil>();
	}
	else if (layerName == "Collision Layer") {
		tileNode = std::make_shared<House>();
	}
	else if (layerName == "Interact Layer") {
		tileNode = std::make_shared<Soil>();
	}

	if (tileNode) {
		// 设置瓦片节点的位置
		const Size tileSize = tmxMap->getTileSize();
		tileNode->setPosition(position.x * tileSize.width, position.y * tileSize.height);
	}

	return tileNode;
}

bool Farm::isCollidingWithTile(const Vec2& position) const {
	if (!collisionLayer) {
		CCLOG("Collision Layer is not found.");
		return false; // 如果碰撞图层未初始化，视为无碰撞
	}

	// 将世界坐标转换为地图坐标
	Vec2 mapPosition = tmxMap->convertToNodeSpace(position);

	// 获取 farmMap 的位置
	auto farmMap = FarmMap::getInstance();
	Vec2 farmMapPosition = farmMap->getPosition();

	// 计算偏移量，这样我们可以将玩家的位置转换到地图内部的坐标系
	mapPosition.x -= farmMapPosition.x;
	mapPosition.y -= farmMapPosition.y;

	// 获取瓦片大小和地图尺寸
	Size tileSize = tmxMap->getTileSize();  // 瓦片的大小
	Size mapSize = tmxMap->getMapSize();    // 地图的大小（瓦片的列数和行数）

	// 计算瓦片坐标
	int tileX = mapPosition.x / tileSize.width;
	int tileY = (mapSize.height * tileSize.height - mapPosition.y) / tileSize.height;

	// 获取该位置的瓦片 GID
	int tileGID = collisionLayer->getTileGIDAt(Vec2(tileX, tileY));

	// 假设你在 Tiled 中为不可通行的瓦片设置了 GID，例如 GID 为 1 代表土块
	if (tileGID == 1) {  // 如果该瓦片的 GID 为 1，表示不可通行
		CCLOG("Collision detected at position (%f, %f) with blocked tile GID %d.",
			mapPosition.x, mapPosition.y, tileGID);
		return true;  // 碰撞检测成功
	}

	CCLOG("No collision detected at position (%f, %f).", mapPosition.x, mapPosition.y);
	return false;  // 如果是可通行区域，返回无碰撞
}