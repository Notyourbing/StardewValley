#include "FarmMap.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"
#include<string>

USING_NS_CC;

// 初始化静态实例
FarmMap* FarmMap::instance = nullptr;

FarmMap::FarmMap() : velocity(Vec2::ZERO) {}

FarmMap::~FarmMap() {}

FarmMap* FarmMap::getInstance() {
    if (!instance) {
        instance = new (std::nothrow) FarmMap();
        if (instance) {
            instance->autorelease();
        }
        else {
            CC_SAFE_DELETE(instance);
        }
    }
    return instance;
}

bool FarmMap::init(const std::string& tmxFile) {
    if (!Node::init()) {
        return false;
    }

    velocity = Vec2::ZERO;

    // 如果传入了文件名,加载地图
    if (!tmxFile.empty()) {
        map = TMXTiledMap::create(tmxFile);
        if (!map) {
            return false;
        }
        this->addChild(map);

        // 获取地图的各个图层
        grassLayer = map->getLayer("Grass");
        soilLayer = map->getLayer("Soil");
        obstacleLayer = map->getLayer("Obstacles");
        moldLayer = map->getLayer("Mold");
        waterLayer = map->getLayer("Water");
        stoneLayer = map->getLayer("Stone");

        // 获取瓦点地图的长宽
        int width = map->getMapSize().width;
        int height = map->getMapSize().height;
        
        // 遍历图层为每一个图层
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (stoneLayer->getTileGIDAt(Vec2(x, y))) {
                    mapTileNode[x][y] = new Stone(Vec2(x,y));
                }
                else if (waterLayer->getTileGIDAt(Vec2(x, y))) {
                    mapTileNode[x][y] = new Water(Vec2(x,y));
                }
                else if (moldLayer->getTileGIDAt(Vec2(x, y))) {
                    mapTileNode[x][y] = new Mold(Vec2(x,y));
                }
                else if(obstacleLayer->getTileGIDAt(Vec2(x,y))){
                    mapTileNode[x][y] = new Obstacle(Vec2(x, y));
                }
                else if (soilLayer->getTileGIDAt(Vec2(x, y))) {
                    mapTileNode[x][y] = new Soil(Vec2(x, y));
                }
                else {
                    mapTileNode[x][y] = new Grass(Vec2(x, y));
                }
            }
        }

        // 这个lambda函数会在FarmMap的生存期内每dt时间调用一次
        schedule([this](float dt) {
            // 获取界面尺寸
            const auto visibleSize = Director::getInstance()->getVisibleSize();

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
            position.x = std::max(visibleSize.width - getMapSize().width, std::min(position.x, 0.0f));
            position.y = std::max(visibleSize.height - getMapSize().height, std::min(position.y, 0.0f));

            setPosition(position);
            }, "farm_map");
    }

    return true;
}

bool FarmMap::npcInit(const Vec2& position, Npc* npc)
{
    npc->sprite->setPosition(position);
    this->addChild(npc->sprite, 5);

    return true;
}

void FarmMap::moveMapByDirection(const Vec2& direction) {
    velocity = direction * MAP_MOVE_SPEED;
}

Size FarmMap::getMapSize() const {
    return map->getContentSize();
}

// 碰撞检测：检查给定位置是否是障碍物, positon是人物在地图坐标系（原点在左下角）中的坐标
bool FarmMap::isCollidable(const Vec2& position) const {
    if (!obstacleLayer) {
        return false;
    }

    // 获取地图的瓦片大小
    const Size tileSize = map->getTileSize();
    const Size mapSize = map->getMapSize();

    // 将人物在地图中的坐标转换为瓦片地图坐标（原点在左上角）
    int x = position.x / tileSize.width;
    int y = (mapSize.height * tileSize.height - position.y) / tileSize.height;

    // 检查是否在地图范围内
    if (x < 0 || x >= mapSize.width || y < 0 || y >= mapSize.height) {
        return true; // 超出地图范围视为障碍物
    }

    // 碰撞检测
    TileType tileType = mapTileNode[x][y]->getTileType();
    if (tileType == TileType::STONE || tileType == TileType::OBSTACLE || tileType == TileType::WATER||tileType == TileType::MOLD) {
        return true;
    }
    else {
        return false;
    }
}

// 玩家与农场的接口
void FarmMap::interactWithFarmMap() {
    // 获取玩家以及地图实例
    Player* player = Player::getInstance();
    FarmMap* farmMap = FarmMap::getInstance();

    // 获取要交互的土块位置
    Vec2 playerPosition = player->getPosition();
    const Size tileSize = farmMap->map->getTileSize();
    const Size mapSize = farmMap->map->getMapSize();
    playerPosition = playerPosition - farmMap->getPosition();
    playerPosition.y = playerPosition.y - player->getContentSize().height / 2 + 10.0f;
    int x = playerPosition.x / tileSize.width;
    int y = (mapSize.height * tileSize.height - playerPosition.y) / tileSize.height;
    Vec2 lastDirection = player->getLastDirection();

    if (lastDirection == Vec2(1, 0) && x + 1 < mapSize.width - 1) {
        x++;
    }
    else if (lastDirection == Vec2(0, 1) && y - 1 >= 0) {
        y--;
    }
    else if (lastDirection == Vec2(-1, 0) && x - 1 >= 0) {
        x--;
    }
    else if (lastDirection == Vec2(0, -1) && y + 1 < mapSize.height - 1) {
        y++;
    }

    // 获得了要交互的位置
    Vec2 interactPosition = Vec2(x, y);

    // 获得当前人物所使用的工具
    std::string currentTool = player->getCurrentToolName();

    // 与地图块的交互
    mapTileNode[x][y]->interact(currentTool);

    // 更新图块
    soilLayer->setTileGID(mapTileNode[x][y]->getCurrentGID(), Vec2(x, y));
}