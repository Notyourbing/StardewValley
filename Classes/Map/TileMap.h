#ifndef __Tile_Map_H__
#define __Tile_Map_H__

#include "Crop.h"
#include "cocos2d.h"
#include<vector>
#include<memory>
#include<array>
#include<unordered_map>

USING_NS_CC;



// 瓦片类型
enum class TileType
{
    SOIL,
    GRASS,
    TREE,
    TREE_STUMP,
    FLOWER,
    HOUSE,
    WATER,
};

class TileNode :public cocos2d::Node
{
public:
    TileNode(TileType type = TileType::SOIL) : type(type) {}
    virtual ~TileNode() {}

    // 交互方式,由子类实现
    virtual void interact() = 0;
    // 获得瓦片类型
    TileType getType() const { return type; }
    // 设置瓦片类型
    virtual void setType(TileType newType);
    // 判断是否可以进入
    virtual bool isWalkable() = 0;
private:
    TileType type;
};

class Soil : public TileNode
{
public:
    Soil() : TileNode(TileType::SOIL), isPlowed(false), isWatered(false), isFertilized(false), health(100), droughtTime(0) {}

    // 耕种土地
    void plow();

    // 种植作物
   void plantCrop(CropType cropType);

    // 更新作物生长
    void updateCropGrowth(int deltaTime);

    // 收获作物
    bool harvestCrop();

    // 交互方法
    void interact() override;

    // 浇水
    void water();

    // 施肥
    void fertilize();

    // 设置土地健康
    void setHealth(int newHealth);

    // 能够进入
    bool isWalkable() override { return true; }
private:
    Crop* currentCrop;
    int droughtTime;
    int health;
    bool isPlowed;
    bool isWatered;
    bool isFertilized;
};

class Tree : public TileNode
{
public:
    // 初始化构造函数
    Tree() : TileNode(TileType::TREE), isCut(false) {}
    // 树的交互逻辑
    void interact() override;
private:
    // 用来判断这棵树有没有被砍倒
    bool isCut;
};

class TreeStump : public TileNode
{
public:
    // 初始化构造函数
    TreeStump() : TileNode(TileType::TREE_STUMP), isCut(false) {}
    // 树桩的交互逻辑
    void interact() override;
    // 判断是否能进入
    bool isWalkable() override { return false; }
private:
    // 用来判断这个树桩有没有被砍倒
    bool isCut;
};

class Flower : public TileNode
{
public:
    Flower() : TileNode(TileType::FLOWER), isCut(false) {}

    void interact() override;
    // 判断是否进入
    bool isWalkable() override { return true; }
private:
    // 用来判断花是否被砍掉
    bool isCut;
};

class House : public TileNode
{
public:
    House() : TileNode(TileType::HOUSE) {}

    void interact() override {}
    // 判断是否能够进入
    bool isWalkable() override { return false; }
};

class Water : public TileNode
{
public:
    Water() : TileNode(TileType::WATER) {}

    void interact() override {}

    // 判断是否能够进入
    bool isWalkable() override { return false; }
};

class TileMapLayer
{
public:
    TileMapLayer(int width, int height) : width(width), height(height) {}

    // 设置指定位置的瓦片
    void addTile(int x, int y, std::shared_ptr<TileNode> tile) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            tiles[y][x] = tile;  // 放置瓦片
        }
    }

    // 获取指定位置的瓦片
    std::shared_ptr<TileNode> getTileAtPosition(int x, int y) const {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return tiles[y][x];  // 返回瓦片
        }
        return nullptr;
    }

    // 更新图层
    void updateLayer(int deltaTime) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (tiles[y][x]) {
                    tiles[y][x]->update(deltaTime);  // 调用每个瓦片的更新函数
                }
            }
        }
    }

private:
    int width, height;
    std::vector<std::vector<std::shared_ptr<TileNode>>> tiles;  // 瓦片数组
};


class TileMap
{
public:
    TileMap(int width, int height) : width(width), height(height) {}

    virtual ~TileMap() {
        for (auto layer : layers) {
            delete layer;
        }
    }

    // 添加图层
    void addLayer(TileMapLayer* layer) {
        layers.push_back(layer);
    }

    // 获取指定位置的瓦片
    std::shared_ptr<TileNode> getTileAt(int x, int y) const {
        for (auto layer : layers) {
            auto tile = layer->getTileAtPosition(x, y);  // 查找瓦片
            if (tile) {
                return tile;
            }
        }
        return nullptr;  // 如果没有找到瓦片，返回 nullptr
    }

    // 获取地图的宽度和高度
    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    // 更新地图（例如作物生长等）
    void update(int deltaTime) {
        for (auto layer : layers) {
            layer->updateLayer(deltaTime);  // 更新每个图层
        }
    }

private:
    int width, height;  // 地图的宽度和高度
    std::vector<TileMapLayer*> layers;  // 图层列表
};

#endif