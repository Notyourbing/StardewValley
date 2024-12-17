#include "BeachMap.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// 初始化静态实例
BeachMap* BeachMap::instance = nullptr;

TileNode* BeachMap::getTileNode(const int x, const int y) const {
    return mapTileNode[x][y];
}

BeachMap::~BeachMap() {
    instance = nullptr;
}

BeachMap::BeachMap() : velocity(Vec2::ZERO) {}

BeachMap* BeachMap::getInstance() {
    if (!instance) {
        instance = new (std::nothrow) BeachMap();
        if (instance && instance->init("Maps/beach/beachMap.tmx")) {
            instance->autorelease();
        }
        else {
            CC_SAFE_DELETE(instance);
        }
    }
    return instance;
}

bool BeachMap::init(const std::string& tmxFile) {
    if (!Node::init()) {
        return false;
    }

    velocity = Vec2::ZERO;

    // 如果传入了文件名,加载地图
    if (!tmxFile.empty()) {
        tiledMap = TMXTiledMap::create(tmxFile);
        if (!tiledMap) {
            return false;
        }
    }
    addChild(tiledMap);

    const Size beachMapSize = getMapSize();
    setPosition(WINSIZE.width / 2 - beachMapSize.width / 2, WINSIZE.height / 2 - beachMapSize.height / 2);

    backgroundLayer = tiledMap->getLayer("Background");
    waterLayer = tiledMap->getLayer("Water");

    // 获取瓦点地图的长宽
    int width = tiledMap->getMapSize().width;
    int height = tiledMap->getMapSize().height;

    // 遍历图层为每一个图层
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (waterLayer->getTileGIDAt(Vec2(x, y))) {
                mapTileNode[x][y] = new Water(Vec2(x, y));
            }
            else if (backgroundLayer->getTileGIDAt(Vec2(x, y))) {
                mapTileNode[x][y] = new Soil(Vec2(x, y));
            }

        }
    }
    // 这个lambda函数会在BeachMap的生存期内每dt时间调用一次
    schedule([this](float dt) {

        // 检查目标位置是否是障碍物
        auto player = Player::getInstance();

        // 人在地图坐标中下一步会到达的位置
        // 这里的- velocity / 200.0f * 10.0f是预测下一步的位置
        // velocity / 200.0f是因为velocity的绝对值是200
        Vec2 playerSize2 = Vec2(0.0f, player->getContentSize().height * 1.0f);

        auto playerPositionInMap = player->getPosition() - getPosition() - playerSize2 * 0.5f + player->getVelocity() / MAP_MOVE_SPEED * 10.0f;
        if (isCollidable(playerPositionInMap)) {
            velocity = Vec2::ZERO;
        }
        auto position = getPosition() + velocity * dt;
        // max保证大于等于下界， min保证小于等于上界
        position.x = std::max(WINSIZE.width - getMapSize().width, std::min(position.x, 0.0f));
        position.y = std::max(WINSIZE.height - getMapSize().height, std::min(position.y, 0.0f));

        setPosition(position);
        }, "beach_map");
    return true;
}

void BeachMap::moveMapByDirection(const Vec2& direction) {
    velocity = direction * MAP_MOVE_SPEED;
}

const Size& BeachMap::getMapSize() const {
    return tiledMap->getContentSize();
}


// 碰撞检测：检查给定位置是否是障碍物, positon是人物在地图坐标系（原点在左下角）中的坐标
bool BeachMap::isCollidable(const Vec2& position) const {
    // 获取地图的瓦片大小
    const Size tileSize = tiledMap->getTileSize();
    const Size mapSize = tiledMap->getMapSize();

    // 将人物在地图中的坐标转换为瓦片地图坐标（原点在左上角）
    int x = position.x / tileSize.width;
    int y = (mapSize.height * tileSize.height - position.y) / tileSize.height;

    // 检查是否在地图范围内
    if (x < 0 || x >= mapSize.width || y < 0 || y >= mapSize.height) {
        return true; // 超出地图范围视为障碍物
    }

    // 碰撞检测
    TileType tileType = mapTileNode[x][y]->getTileType();
    if (tileType == TileType::Water) {
        return true;
    }
    else {
        return false;
    }
}

void BeachMap::interactWithBeachMap() {
    //// 获取玩家、地图、背包实例
    //Player* player = Player::getInstance();
    //BeachMap* beachMap = BeachMap::getInstance();
    //Bag* bag = Bag::getInstance();

    //if (!player->getUseItemEnable()) {
    //    return;
    //}

    //// 获取要交互的土块位置
    //Vec2 playerPosition = player->getPosition();
    //const Size tileSize = beachMap->tiledMap->getTileSize();
    //const Size mapSize = beachMap->tiledMap->getMapSize();
    //playerPosition = playerPosition - beachMap->getPosition();
    //playerPosition.y = playerPosition.y - player->getContentSize().height / 2 + 10.0f;
    //playerPosition.x = playerPosition.x / tileSize.width;
    //playerPosition.y = (mapSize.height * tileSize.height - playerPosition.y) / tileSize.height;
    //const Vec2 lastDirection = player->getLastDirection();

    //// 当前人物前面的瓦点
    //if (lastDirection == Vec2(1, 0) && playerPosition.x + 1 < mapSize.width - 1) {
    //    playerPosition.x++;
    //}
    //else if (lastDirection == Vec2(0, 1) && playerPosition.y - 1 >= 0) {
    //    playerPosition.y--;
    //}
    //else if (lastDirection == Vec2(-1, 0) && playerPosition.x - 1 >= 0) {
    //    playerPosition.x--;
    //}
    //else if (lastDirection == Vec2(0, -1) && playerPosition.y + 1 < mapSize.height - 1) {
    //    playerPosition.y++;
    //}

    //const int x = playerPosition.x;
    //const int y = playerPosition.y;

    //// 获得当前人物所使用的工具
    //std::string currentItemName = player->getCurrentItemName();
}

void BeachMap::stopMoving() {
    velocity = Vec2::ZERO;
}

TMXTiledMap* BeachMap::getTiledMap() {
    return tiledMap;
}