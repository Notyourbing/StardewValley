#include "CaveMap.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "../Item/ItemFactory.h"
#include "../Npc/NoticeBoard.h"

USING_NS_CC;

// 初始化静态实例
CaveMap* CaveMap::instance = nullptr;

// 构造函数
CaveMap::CaveMap() : backgroundLayer(nullptr), obstacleLayer(nullptr) {}

// 析构函数
CaveMap::~CaveMap() {
    instance = nullptr;
}

// 获取单例实例
CaveMap* CaveMap::getInstance() {
    if (!instance) {
        instance = new (std::nothrow) CaveMap();
        if (instance && instance->init("Maps/cave/cave.tmx")) {
            instance->autorelease();
        }
        else {
            CC_SAFE_DELETE(instance);
        }
    }
    return instance;
}

// 初始化地图
bool CaveMap::init(const std::string& tmxFile) {
    if (!SceneMap::init(tmxFile)) {
        return false;
    }

    // 获取地图的各个层
    backgroundLayer = tiledMap->getLayer("Background");
    obstacleLayer = tiledMap->getLayer("Obstacle");

    // 放位置
    const Size mapSize = getMapSize();
    setPosition(WINSIZE.width / 2 - mapSize.width / 2, 0.0f);

    // 获取瓦点地图的长宽
    int width = tiledMap->getMapSize().width;
    int height = tiledMap->getMapSize().height;

    // 遍历图层为每一个图层
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (obstacleLayer->getTileGIDAt(Vec2(x, y))) {
                mapTileNode[x][y] = new Obstacle(Vec2(x, y));
            }
            else if (backgroundLayer->getTileGIDAt(Vec2(x, y))) {
                mapTileNode[x][y] = new Soil(Vec2(x, y));
            }
        }
    }

    // 这个lambda函数会在CaveMap的生存期内每dt时间调用一次
    schedule([this](float dt) {

        // 检查目标位置是否是障碍物
        auto player = Player::getInstance();

        // 人在地图坐标中下一步会到达的位置
        Vec2 playerSize2 = Vec2(0.0f, player->getContentSize().height * 1.0f);
        auto playerPositionInMap = player->getPosition() - getPosition() - playerSize2 * 0.5f + player->getVelocity() / MAP_MOVE_SPEED * 10.0f;
        if (isCollidable(playerPositionInMap)) {
            velocity = Vec2::ZERO;
            player->stopMoving();
        }
        auto position = getPosition() + velocity * dt;
        // max保证大于等于下界， min保证小于等于上界
        position.x = std::max(WINSIZE.width - getMapSize().width, std::min(position.x, 0.0f));
        position.y = std::max(WINSIZE.height - getMapSize().height, std::min(position.y, 0.0f));

        setPosition(position);
        }, "cave_map");
    return true;
}

// 更新地图位置
void CaveMap::moveMapByDirection(const Vec2& direction) {
    velocity = direction * MAP_MOVE_SPEED;
}

// 碰撞检测：检查给定位置是否是障碍物, position是人物在地图坐标系（原点在左下角）中的坐标
bool CaveMap::isCollidable(const Vec2& position) const {
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
    if (tileType == TileType::Obstacle) {
        return true;
    }
    else {
        return false;
    }
}

// 重写和地图交互
void CaveMap::interactWithMap() {
}

// 地图随时间更新
void CaveMap::mapUpdateByTime() {
}
