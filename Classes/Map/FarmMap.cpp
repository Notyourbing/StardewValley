#include "FarmMap.h"
#include "../Player/Player.h"

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

        // 获取障碍物层
        obstacleLayer = map->getLayer("obstacles");
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

            auto playerPositionInMap = player->getPosition() - getPosition() - playerSize2 * 0.5f + player->getVelocity() / 200.0f * 10.0f;
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
    velocity = direction * 200.f;
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
    int tileGID = obstacleLayer->getTileGIDAt(Vec2(x, y));
    if (tileGID != 0) {
        return true;
    }
    else {
        return false;
    }
}

