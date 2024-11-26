#include "FarmScene.h"
#include "../Map/FarmMap.h"
#include "../Npc/Npc.h"
#include "ui/CocosGUI.h"

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
	farmMap->setPosition(visibleSize.width / 2 -farmMapSize.width / 2, visibleSize.height / 2 -farmMapSize.height / 2);
	this->addChild(farmMap, 0);


	// 创建 NPC 示例
	Npc* wizard = new Npc("Wizard Yuuu", "Fall 5",
		{ "Magic Essence", "Diamond" },
		{ "Milk" },
		{ "Get out of my way", "How are you?", "I like to spend time with you." },
		"npcImages/wizard.png");

	Npc* cleaner = new Npc("Cleaner Levi", "Winter 25",
		{ "Milk", "Cleaning tools" },
		{ "Clay" },
		{ "...", "Ahh, hi.", "Come and have some black-tea with me." },
		"npcImages/cleaner.png");

	//测试：亲密度90
	wizard->increaseFriendship(90);
	npcs.push_back(cleaner);
	npcs.push_back(wizard);


	farmMap->npcInit(Vec2(origin.x + 300, origin.y + 300), wizard);
	farmMap->npcInit(Vec2(origin.x + 500, origin.y + 300), cleaner);

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

	// 更新玩家和地图的移动方向
	auto player = Player::getInstance();
	auto farmMap = FarmMap::getInstance();
	farmMap->moveMapByDirection(-direction);
	player->moveByDirection(direction);

	//显示对话框,添加鼠标事件监听器
	initMouseListener();
}

void Farm::showDialogue(Npc* npc) {

	if (isDialogueVisible) {
		return;  // 如果对话框已经显示，则不再显示
	}
	// 获取屏幕尺寸
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Player* player = Player::getInstance();
	// 获取玩家的位置
	auto playerPosition = player->getPosition();

	// 创建对话框背景图片
	auto dialogueBackground = Sprite::create("npcImages/dialogueBox.png");
	if (!dialogueBackground) {
		return;
	}

	// 设置文字大小
	const float padding = 20.0f;  // 背景与文字的间距
	auto label = Label::createWithTTF(npc->printDialogue(), "fonts/Marker Felt.ttf", 44);
	if (!label) {
		return;
	}

	// 计算文字的宽度和高度，确保背景能够容纳文字
	const float labelWidth = 720;  // 文字占宽度
	const float labelHeight = 390;  // 文字占高度

	// 调整背景框的大小
	dialogueBackground->setContentSize(Size(1283, 462));//素材框大小

	// 设置对话框背景的位置
	dialogueBackground->setPosition(Vec2(640, 200));//使对话框在屏幕下半侧占满
	this->addChild(dialogueBackground, 10);  // 确保背景图在最上层

	// 设置文字的位置和对齐方式
	label->setDimensions(labelWidth - 50, labelHeight - 50);  // 文字框的宽度为背景框的宽度，设置高度为背景框高度,稍微缩小
	label->setPosition(Vec2(dialogueBackground->getPositionX() - 240,
		dialogueBackground->getPositionY()));
	label->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);  // 文字左上对齐
	label->setTextColor(Color4B::WHITE);  // 设置文字颜色为白色
	this->addChild(label, 11);  // 确保文字在背景图之上
	isDialogueVisible = true;

	//添加人物立绘
	std::string npcImageName = "npcImages/" + npc->getNpcName() + "Talk.png";  // 假设NPC的名字就是图片的文件名，且图片后缀为 .png

	// 创建并显示NPC的立绘
	auto npcTalkImage = Sprite::create(npcImageName);
	if (npcTalkImage) {
		npcTalkImage->setPosition(Vec2(dialogueBackground->getPositionX() + 365, dialogueBackground->getPositionY() + 40));  // 设置图片显示的位置
		this->addChild(npcTalkImage, 12);  // 确保图像在最上层
	}

	// 添加鼠标点击事件监听器,左键关闭对话框
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = [=](Event* event) {
		if (static_cast<EventMouse*>(event)->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			dialogueBackground->setVisible(false);  // 隐藏对话框
			label->setVisible(false);  // 隐藏文字
			npcTalkImage->setVisible(false); // 隐藏人物立绘
			isDialogueVisible = false;
		}
		};

	// 添加鼠标事件监听器到事件分发器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void Farm::initMouseListener()
{
	// 创建鼠标事件监听器
	auto listener = EventListenerMouse::create();

	if (isDialogueVisible == false) {
		listener->onMouseDown = [](Event* event) {
			auto mouseEvent = dynamic_cast<EventMouse*>(event);
			if (mouseEvent && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
				Player::getInstance()->useCurrentTool();
			}
			};
	}
	for (auto npc : npcs) {
		// 计算玩家与 NPC 的距离
		Player* player = Player::getInstance();
		FarmMap* farmMap = FarmMap::getInstance();
		float distance = player->getPosition().distance(npc->sprite->getPosition() + farmMap->getPosition());

		// 设定一个合适的距离阈值
		float interactionRange = 100.0f;  // 可调整的阈值，表示玩家与 NPC 之间的最大交互距离
		CCLOG("distance:(%f)\n", distance);
		// 如果玩家与 NPC 的距离小于阈值，则触发对话框
		if (distance < interactionRange) {
			listener->onMouseDown = [=](Event* event) {
				// 检查是否是右键点击
				if (static_cast<EventMouse*>(event)->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT
					&& player->getPosition().distance(npc->sprite->getPosition() + farmMap->getPosition()) < interactionRange) {
					showDialogue(npc);  // 显示对话框
				}
				};
		}
	}
	// 添加鼠标事件监听器到事件分发器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
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