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

	// ��ȡ��Ļ��С��ԭ��
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto farmMap = FarmMap::getInstance();
	if (!farmMap->init("Maps/farm.tmx")) {
		return false;
	}
	const auto farmMapSize = farmMap->getMapSize();
	farmMap->setPosition(visibleSize.width / 2 - farmMapSize.width / 2, visibleSize.height / 2 - farmMapSize.height / 2);
	this->addChild(farmMap, 0);

	// ����TMX��ͼ
	tmxMap = TMXTiledMap::create("Maps/farm.tmx");
	if (!tmxMap) {
		return false; // ��ͼ����ʧ��ʱ���� false
	}

	// ��ʼ��ͼ��
	initLayers();

	

	// ��ʼ����Ƭ�ڵ�
	//initTileNodes();

	// ��ȡ��ҵ�������ӵ�������
	auto player = Player::getInstance();
	player->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2); // ��ʼλ��
	this->addChild(player, 3);

	// ��ʾ�������
	auto nameLabel = Label::createWithTTF(player->getPlayerName() + "'s farm", "fonts/Marker Felt.ttf", 24);
	if (nameLabel) {
		nameLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 50));
		this->addChild(nameLabel, 4);
	}

	// ��ʼ�����̼�����
	initKeyboardListener();

	return true;
}

void Farm::initKeyboardListener() {
	// ���������¼�������
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
		keysPressed.insert(keyCode);
		updateMovement(); // ���ݵ�ǰ���µļ����㷽��
		};

	// �ɿ���ʱ�� keysPressed �Ƴ�
	listener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
		keysPressed.erase(keyCode);
		// ֹͣ����ƶ�
		Player::getInstance()->stopMoving();
		updateMovement(); // ���·���

		};

	// ��Ӽ��������¼��ַ���
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Farm::updateMovement() {
	Vec2 direction = Vec2::ZERO;

	// ��鰴�����ϣ����ݰ��µļ����㷽��
	if (keysPressed.count(EventKeyboard::KeyCode::KEY_W)) { // ��
		direction.y += 1;
	}
	if (keysPressed.count(EventKeyboard::KeyCode::KEY_S)) { // ��
		direction.y -= 1;
	}
	if (keysPressed.count(EventKeyboard::KeyCode::KEY_A)) { // ��
		direction.x -= 1;
	}
	if (keysPressed.count(EventKeyboard::KeyCode::KEY_D)) { // ��
		direction.x += 1;
	}

	// ��һ�����򣬱���б�����ƶ��ٶȹ���
	if (direction != Vec2::ZERO) {
		direction.normalize();
	}

	// ��ȡ���ʵ��
	auto player = Player::getInstance();
	Vec2 currentPlayerPosition = player->getPosition();


	// �����µ�λ��
	Vec2 newPosition = currentPlayerPosition + direction;

	// �����λ���Ƿ�ᷢ����ײ
	if (isCollidingWithTile(newPosition)) {
		direction = Vec2::ZERO;
	}

	// ������Һ͵�ͼ���ƶ�����
	auto farmMap = FarmMap::getInstance();
	farmMap->moveMapByDirection(-direction);
	player->moveByDirection(direction);
}

void Farm::initLayers(){
	// ��ʼ��������
	backgroundLayer = tmxMap->getLayer("background");

	// ��ʼ����ײ��
	collisionLayer = tmxMap->getLayer("Block");
}

void Farm::initTileNodes() {
	// ��ͼ��С
	const Size mapSize = tmxMap->getMapSize();

	// ������Ҫ�����ͼ��
	for (const auto& layerName : { "Background", "Collision", "Interact" }) {
		TMXLayer* layer = tmxMap->getLayer(layerName);
		if (!layer) continue;

		for (int x = 0; x < mapSize.width; ++x) {
			for (int y = 0; y < mapSize.height; ++y) {
				Vec2 tileCoord(x, y);
				auto tile = layer->getTileAt(tileCoord);

				if (tile) {
					// ������Ƭ�ڵ�
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
		// ������Ƭ�ڵ��λ��
		const Size tileSize = tmxMap->getTileSize();
		tileNode->setPosition(position.x * tileSize.width, position.y * tileSize.height);
	}

	return tileNode;
}

bool Farm::isCollidingWithTile(const Vec2& position) const {
	if (!collisionLayer) {
		CCLOG("Collision Layer is not found.");
		return false; // �����ײͼ��δ��ʼ������Ϊ����ײ
	}

	// ����������ת��Ϊ��ͼ����
	Vec2 mapPosition = tmxMap->convertToNodeSpace(position);

	// ��ȡ farmMap ��λ��
	auto farmMap = FarmMap::getInstance();
	Vec2 farmMapPosition = farmMap->getPosition();

	// ����ƫ�������������ǿ��Խ���ҵ�λ��ת������ͼ�ڲ�������ϵ
	mapPosition.x -= farmMapPosition.x;
	mapPosition.y -= farmMapPosition.y;

	// ��ȡ��Ƭ��С�͵�ͼ�ߴ�
	Size tileSize = tmxMap->getTileSize();  // ��Ƭ�Ĵ�С
	Size mapSize = tmxMap->getMapSize();    // ��ͼ�Ĵ�С����Ƭ��������������

	// ������Ƭ����
	int tileX = mapPosition.x / tileSize.width;
	int tileY = (mapSize.height * tileSize.height - mapPosition.y) / tileSize.height;

	// ��ȡ��λ�õ���Ƭ GID
	int tileGID = collisionLayer->getTileGIDAt(Vec2(tileX, tileY));

	// �������� Tiled ��Ϊ����ͨ�е���Ƭ������ GID������ GID Ϊ 1 ��������
	if (tileGID == 1) {  // �������Ƭ�� GID Ϊ 1����ʾ����ͨ��
		CCLOG("Collision detected at position (%f, %f) with blocked tile GID %d.",
			mapPosition.x, mapPosition.y, tileGID);
		return true;  // ��ײ���ɹ�
	}

	CCLOG("No collision detected at position (%f, %f).", mapPosition.x, mapPosition.y);
	return false;  // ����ǿ�ͨ�����򣬷�������ײ
}