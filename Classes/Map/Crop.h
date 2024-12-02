#ifndef __CROP_H__
#define __CROP_H__

#include "cocos2d.h"

// 作物的种类
enum class CropType {
	APPLE,
	CORN,
	CARROT,
};

// 季节
enum class Season {
	SPRING,
	SUMMER,
	AUTUMN,
	WINTER,
};

// 作物的基类
class Crop {
private:

protected:
	// 作物的种类
	CropType cropType;
	// 最长的成熟天数
	int maxGrowthDay;
	// 当前的成长阶段
	int growthStage;
	// 收获的种植季节
	Season season;
	// 是否遭受虫害
	bool isInfested;
	// 遭受虫害天数
	int infestedDay;
	// 是否干旱
	bool isDrought;
	// 当前肥料值
	int fertilizedLevel;
	// 当前图层对应图块的GID
	int cropGID;
	// 当前作物在瓦片地图上的位置
	cocos2d::Vec2 position;
public:
	// 构造函数
	Crop(const CropType& cropType,const int& maxGrowthDay,const Season& season,
		const int& cropGID,cocos2d::Vec2 position):
		cropType(cropType),maxGrowthDay(maxGrowthDay),growthStage(0),
		season(season),isInfested(false),isDrought(false),
		fertilizedLevel(0),cropGID(cropGID),position(position) ,
		infestedDay(0)
	{}

	// 处理作物的生长,虚函数
	virtual void grow();

	// 判断是否成熟
	bool isMature() const;

	// 浇水
	void irrigate();

	// 施肥
	void fertilize();

	// 使用农药
	void applyPesticide();

	// 作物的丰收
	void harvest();
};

//具体子类的继承

// 苹果作物
class Apple : public Crop {
private:
	Season season;
public:
	// 获取当前的GID
	int getCurrentGID();
};

// 玉米作物
class Corn : public Crop {
private:
	Season season;
public:
	// 获取当前的GID
	int getCurrentGID();
};

// 胡萝卜作物
class Carrot : public Crop {
private:
	// 当前的GID
	int currentGID;
public:
	// 获取当前的GID
	int getCurrentGID();
};

#endif