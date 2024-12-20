/****************************************************************
 * File Function: 实现洞穴地图类
 * Author:        赵卓冰
 ****************************************************************/
#ifndef __CAVEMAP_H__
#define __CAVEMAP_H__

#include "cocos2d.h"
#include "TileNode.h"
#include "../Festival/Festival.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "SceneMap.h"

// 洞穴地图
class CaveMap : public SceneMap {
public:
    // 获取单例实例
    static CaveMap* getInstance();

    // 初始化地图
    bool init(const std::string& tmxFile) override;

    // 更新地图位置
    void moveMapByDirection(const cocos2d::Vec2& direction) override;

    // 碰撞检测：检查给定位置是否是障碍物
    bool isCollidable(const cocos2d::Vec2& position) const override;

    // 用于鼠标左键与洞穴的交互逻辑
    void interactWithMap() override;

    // 地图随着时间的更新
    void mapUpdateByTime() override;

private:
    // 构造函数和析构函数私有化
    CaveMap();
    ~CaveMap();

    // 禁用拷贝构造和赋值操作
    CaveMap(const CaveMap&) = delete;
    CaveMap& operator=(const CaveMap&) = delete;

    // 单例实例
    static CaveMap* instance;

    // 用来存储TMX地图的各个层
    cocos2d::TMXLayer* backgroundLayer;
    cocos2d::TMXLayer* obstacleLayer;
};

#endif
