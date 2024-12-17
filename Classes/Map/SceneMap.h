#ifndef __SCENEMAP_H__
#define __SCENEMAP_H__
#include "cocos2d.h"
#include "TileNode.h"

// 基类 SceneMap
class SceneMap : public cocos2d::Node {
public:
    // 初始化地图
    virtual bool init(const std::string& tmxFile);

    // 更新地图位置
    virtual void moveMapByDirection(const cocos2d::Vec2& direction);

    // 获取地图大小
    virtual const cocos2d::Size& getMapSize() const;

    // 碰撞检测：检查给定位置是否是障碍物
    virtual bool isCollidable(const cocos2d::Vec2& position) const;

    // 用于鼠标左键与地图的交互逻辑
    virtual void interactWithMap();

    // 地图停止移动
    virtual void stopMoving();

    // 获取地图的瓦片地图对象
    virtual cocos2d::TMXTiledMap* getTiledMap();

    // 获取当前位置地图的类
    virtual TileNode* getTileNode(const int x, const int y) const;

    // 地图随着时间的更新
    virtual void mapUpdateByTime();

protected:
    // 地图的偏移速度
    cocos2d::Vec2 velocity;

    // 瓦片地图对象
    cocos2d::TMXTiledMap* tiledMap;

    // 存储地图上每个节点的类
    std::vector<std::vector<TileNode*>> mapTileNode;

    // 用来存储TMX地图的各个层
    std::vector<cocos2d::TMXLayer*> layers;

    // 通用地图加载函数
    bool loadMap(const std::string& tmxFile);

    // 构造函数和析构函数
    SceneMap();
    virtual ~SceneMap();
};
#endif
