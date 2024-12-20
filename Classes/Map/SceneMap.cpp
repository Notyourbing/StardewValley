/****************************************************************
 * File Function: 实现所有地图的基类
 * Author:        赵卓冰
 ****************************************************************/
#include "SceneMap.h"

USING_NS_CC;

// 构造函数
SceneMap::SceneMap() : velocity(Vec2::ZERO), tiledMap(nullptr) {}

// 析构函数
SceneMap::~SceneMap() {
    // 清理 mapTileNode
    for (auto& row : mapTileNode) {
        for (auto& tile : row) {
            if (tile) {
                delete tile;
                tile = nullptr;
            }
        }
    }
}

// 加载 TMX 地图
bool SceneMap::loadMap(const std::string& tmxFile) {
    if (tmxFile.empty()) {
        return false;
    }

    tiledMap = TMXTiledMap::create(tmxFile);
    if (!tiledMap) {
        CCLOG("Failed to load TMX file: %s", tmxFile.c_str());
        return false;
    }

    addChild(tiledMap);
    return true;
}

// 初始化地图
bool SceneMap::init(const std::string& tmxFile) {
    if (!Node::init()) {
        return false;
    }

    // 加载地图
    if (!loadMap(tmxFile)) {
        return false;
    }

    // 设置地图位置为屏幕中心
    const Size mapSize = getMapSize();
    setPosition(WINSIZE.width / 2 - mapSize.width / 2, WINSIZE.height / 2 - mapSize.height / 2);

    // 获取所有层并存储
    auto allLayers = tiledMap->getChildren();
    for (auto& layer : allLayers) {
        auto tmxLayer = dynamic_cast<TMXLayer*>(layer);
        if (tmxLayer) {
            layers.push_back(tmxLayer);
        }
    }

    // 获取地图的长宽
    int width = tiledMap->getMapSize().width;
    int height = tiledMap->getMapSize().height;

    // 初始化 mapTileNode
    mapTileNode.resize(width, std::vector<TileNode*>(height, nullptr));

    return true;
}

// 更新地图位置
void SceneMap::moveMapByDirection(const Vec2& direction) {
    velocity = direction;
}

// 获取地图大小
const Size& SceneMap::getMapSize() const {
    return tiledMap->getContentSize();
}

// 碰撞检测
bool SceneMap::isCollidable(const Vec2& position) const {
    // 默认实现，子类可以重写
    return false;
}

// 与地图交互
void SceneMap::interactWithMap() {
    // 默认实现，子类可以重写
}

// 停止地图移动
void SceneMap::stopMoving() {
    velocity = Vec2::ZERO;
}

// 获取 TMX 瓦片地图对象
TMXTiledMap* SceneMap::getTiledMap() {
    return tiledMap;
}

// 获取特定位置的 TileNode
TileNode* SceneMap::getTileNode(const int x, const int y) const {
    if (x < 0 || y < 0 || x >= static_cast<int>(mapTileNode.size()) || y >= static_cast<int>(mapTileNode[0].size())) {
        return nullptr;
    }
    return mapTileNode[x][y];
}

// 地图随时间更新
void SceneMap::mapUpdateByTime() {
    // 默认实现，子类可以重写
}