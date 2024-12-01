#include "FarmMap.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"
USING_NS_CC;

// 土壤类的耕种
void Soil::till() {
    isTilled = true;
    soilStage = SoilStage::TILLED;
}

// 获得土壤块位置
Vec2 Soil::getPosition() {
    return position;
}

// 判断该土块是否可耕种
bool Soil::isTillable() {
    return isTilled == false && entity == nullptr;
}

// 判断该土块是否可种植
bool Soil::isPlantable() {
    return isTilled == true && entity == nullptr;
}

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

        // 获取障碍物层
        grassLayer = map->getLayer("Grass");
        soilLayer = map->getLayer("Soil");
        obstacleLayer = map->getLayer("obstacles");
        stoneLayer = map->getLayer("stone");
        waterLayer = map->getLayer("water");

        int width = map->getMapSize().width;
        int height = map->getMapSize().height;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (waterLayer->getTileGIDAt(Vec2(x, y))) {
                    //mapTiles[x][y] = TileNode(TileType::WATER);
                }
                else if (stoneLayer->getTileGIDAt(Vec2(x, y))) {
                    //mapTiles[x][y] = TileNode(TileType::STONE);
                }
                else if (obstacleLayer->getTileGIDAt(Vec2(x, y))) {
                    //mapTiles[x][y] = TileNode(TileType::HOUSE);
                }
                else if (soilLayer->getTileGIDAt(Vec2(x, y))) {
                    auto soilInMap = new Soil(Vec2(x, y));
                    soil.push_back(soilInMap);
                }
                else {
                    //mapTiles[x][y] = TileNode(TileType::GRASS);
                }
                //mapTiles[x][y].position = Vec2(x, y);
                
            }
        }
        
        //CCLOG("successful map");

        if (!obstacleLayer) {
            CCLOG("No 'obstacles' layer found in TMX file.");
            return false;
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

    // 获取障碍物瓦片的 GID（瓦片 ID）
    int tileGIDInObstacle = obstacleLayer->getTileGIDAt(Vec2(x, y));
    int tileGIDInStone = stoneLayer->getTileGIDAt(Vec2(x, y));
    int tileGIDInWater = waterLayer->getTileGIDAt(Vec2(x, y));
    if (tileGIDInObstacle||tileGIDInStone||tileGIDInWater) {
        return true;
    }
    else {
        return false;
    }
 
}

void FarmMap::replaceTile(const Vec2& position, int GID) {
    soilLayer->setTileGID(8, position);
}

// 玩家与农场的交互函数
void FarmMap::interactWithFarmMap(Vec2 position) {
    if (soilLayer->getTileGIDAt(position)){
        soilLayer->setTileGID(8, position);
    }
}