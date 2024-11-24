#ifndef __Tile_Map_H__
#define __Tile_Map_H__

#include "Crop.h"
#include "cocos2d.h"
#include<vector>
#include<memory>
#include<array>
#include<unordered_map>

USING_NS_CC;



// ��Ƭ����
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

    // ������ʽ,������ʵ��
    virtual void interact() = 0;
    // �����Ƭ����
    TileType getType() const { return type; }
    // ������Ƭ����
    virtual void setType(TileType newType);
    // �ж��Ƿ���Խ���
    virtual bool isWalkable() = 0;
private:
    TileType type;
};

class Soil : public TileNode
{
public:
    Soil() : TileNode(TileType::SOIL), isPlowed(false), isWatered(false), isFertilized(false), health(100), droughtTime(0) {}

    // ��������
    void plow();

    // ��ֲ����
   void plantCrop(CropType cropType);

    // ������������
    void updateCropGrowth(int deltaTime);

    // �ջ�����
    bool harvestCrop();

    // ��������
    void interact() override;

    // ��ˮ
    void water();

    // ʩ��
    void fertilize();

    // �������ؽ���
    void setHealth(int newHealth);

    // �ܹ�����
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
    // ��ʼ�����캯��
    Tree() : TileNode(TileType::TREE), isCut(false) {}
    // ���Ľ����߼�
    void interact() override;
private:
    // �����ж��������û�б�����
    bool isCut;
};

class TreeStump : public TileNode
{
public:
    // ��ʼ�����캯��
    TreeStump() : TileNode(TileType::TREE_STUMP), isCut(false) {}
    // ��׮�Ľ����߼�
    void interact() override;
    // �ж��Ƿ��ܽ���
    bool isWalkable() override { return false; }
private:
    // �����ж������׮��û�б�����
    bool isCut;
};

class Flower : public TileNode
{
public:
    Flower() : TileNode(TileType::FLOWER), isCut(false) {}

    void interact() override;
    // �ж��Ƿ����
    bool isWalkable() override { return true; }
private:
    // �����жϻ��Ƿ񱻿���
    bool isCut;
};

class House : public TileNode
{
public:
    House() : TileNode(TileType::HOUSE) {}

    void interact() override {}
    // �ж��Ƿ��ܹ�����
    bool isWalkable() override { return false; }
};

class Water : public TileNode
{
public:
    Water() : TileNode(TileType::WATER) {}

    void interact() override {}

    // �ж��Ƿ��ܹ�����
    bool isWalkable() override { return false; }
};

class TileMapLayer
{
public:
    TileMapLayer(int width, int height) : width(width), height(height) {}

    // ����ָ��λ�õ���Ƭ
    void addTile(int x, int y, std::shared_ptr<TileNode> tile) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            tiles[y][x] = tile;  // ������Ƭ
        }
    }

    // ��ȡָ��λ�õ���Ƭ
    std::shared_ptr<TileNode> getTileAtPosition(int x, int y) const {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return tiles[y][x];  // ������Ƭ
        }
        return nullptr;
    }

    // ����ͼ��
    void updateLayer(int deltaTime) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (tiles[y][x]) {
                    tiles[y][x]->update(deltaTime);  // ����ÿ����Ƭ�ĸ��º���
                }
            }
        }
    }

private:
    int width, height;
    std::vector<std::vector<std::shared_ptr<TileNode>>> tiles;  // ��Ƭ����
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

    // ���ͼ��
    void addLayer(TileMapLayer* layer) {
        layers.push_back(layer);
    }

    // ��ȡָ��λ�õ���Ƭ
    std::shared_ptr<TileNode> getTileAt(int x, int y) const {
        for (auto layer : layers) {
            auto tile = layer->getTileAtPosition(x, y);  // ������Ƭ
            if (tile) {
                return tile;
            }
        }
        return nullptr;  // ���û���ҵ���Ƭ������ nullptr
    }

    // ��ȡ��ͼ�Ŀ�Ⱥ͸߶�
    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    // ���µ�ͼ���������������ȣ�
    void update(int deltaTime) {
        for (auto layer : layers) {
            layer->updateLayer(deltaTime);  // ����ÿ��ͼ��
        }
    }

private:
    int width, height;  // ��ͼ�Ŀ�Ⱥ͸߶�
    std::vector<TileMapLayer*> layers;  // ͼ���б�
};

#endif