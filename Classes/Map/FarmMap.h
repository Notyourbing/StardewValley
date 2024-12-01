#ifndef __FARMMAP_H__
#define __FARMMAP_H__

#include "cocos2d.h"
#include "Crop.h"
#include "../Npc/Npc.h"
#include "Entity.h"
#include "../Festival/Festival.h"
#include <string>
#include <memory>
#include <vector>

enum class TileType {
	SOIL,
	GRASS,
	PLOWEDSOIL,
	WATEREDSOIL,
	CROP,
	HOUSE,
	STONE,
	WATER,
};

enum class SoilStage {
	ROW,
	TILLED,
	WATERED,
	PLANTED,
};

// 土壤类
class Soil {
public:
	// 土壤类的构造函数
	Soil(Vec2 position) :
		isTilled(false), isFertilized(false), isWatered(false),
		isDry(false), isDiseased(false), position(position),
		entity(nullptr),soilStage(SoilStage::ROW),isPlanted(false){}

	// 翻耕土壤
	void till();

	// 获得该地块位置
	Vec2 getPosition();

	// 是否可锄地
	bool isTillable();

	// 判断该点是否可种植
	bool isPlantable();
	// 浇水
	//void water();
	// 施肥
	//void fertilize();
	// 种植作物
	//void plantCrop(const std::string& type, int maturityDays); 
	// 消灭病害
	//void applyPesticide();       
	// 每日更新土壤状态
	//void updateSoil();       
	// 收获作物
	//void harvestCrop();                       
private:
	// 当前土地的状态
	SoilStage soilStage;
	// 是否被锄地
	bool isTilled;
	// 是否被种植
	bool isPlanted;
	bool isFertilized;
	bool isWatered;
	bool isDry;
	bool isDiseased;
	// 记录当前位置
	Vec2 position;
	Entity* entity;
};

// 草地类 负责
class Grass {
public:   
	// 判断是否有动物
	bool hasAnimal() const;

	// 获取当前动物
	Entity* getAnimal() const;

	// 添加动物到草地
	bool addAnimal(Entity* newEntity) {
		if (!entity) {
			entity = newEntity;
			return true;
		}
		return false; // 草地已经有动物
	}

	// 移除草地上的动物
	void removeAnimal() {
		entity = nullptr;
	}

private:
	// 记录当前瓦片位置的动物
	Entity* entity;
	// 记录当前瓦片的位置
	Vec2 position;
};

// 农场地图类
class FarmMap : public cocos2d::Node {
public:
	// 获取单例实例
	static FarmMap* getInstance();

	// 初始化地图
	bool init(const std::string& tmxFile);

	std::vector<Festival*> festivals;

	//随地图创建npc
	bool npcInit(const Vec2& position, Npc* npc);

	// 更新地图位置
	void moveMapByDirection(const cocos2d::Vec2& direction);

	// 获取地图大小
	cocos2d::Size getMapSize() const;

	// 碰撞检测：检查给定位置是否是障碍物
	bool isCollidable(const cocos2d::Vec2& position) const;

	// 用于鼠标左键与农场的交互逻辑
	void interactWithFarmMap(Vec2 position);

	// 瓦片地图对象
	cocos2d::TMXTiledMap* map;

	// 存储瓦片的类型
	//std::vector<std::vector<std::unique_ptr<TileNode>>> mapTiles;

	// 将瓦片替换成不同类型
	void replaceTile(const Vec2& position,int GID);

	cocos2d::TMXLayer* grassLayer;
	cocos2d::TMXLayer* obstacleLayer;
	cocos2d::TMXLayer* stoneLayer;
	cocos2d::TMXLayer* soilLayer;
	cocos2d::TMXLayer* waterLayer;

	// 用来存储不同图层上的类
	std::vector<Soil*> soil;
 
private:
	// 构造函数和析构函数私有化
	FarmMap();
	~FarmMap();

	// 禁用拷贝构造和赋值操作
	FarmMap(const FarmMap&) = delete;
	FarmMap& operator=(const FarmMap&) = delete;

	// 地图当前的偏移位置
	cocos2d::Vec2 currentPosition;

	// 地图的偏移速度
	cocos2d::Vec2 velocity;

	// 单例实例
	static FarmMap* instance;

	// 存储瓦片的类型
	//std::vector<std::vector<TileNode>> mapTiles;


};

#endif