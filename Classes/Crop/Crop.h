#ifndef __CROP_H__
#define __CROP_H__

#include "cocos2d.h"
#include "../Constant/Constant.h"
#include <vector>
#include <map>

// 作物的种类
enum class CropType {
	Dogbane,
	Corn,
	Carrot,
};

// 作物的基类
class Crop {
private:

protected:
	CropType cropType;		// 作物的种类
	int growedDay;			// 已经成长的天数
	int growthStage;		// 当前的成长阶段
	bool isInfested;		// 是否遭受虫害
	int infestedDay;		// 遭受虫害天数
	bool isDrought;			// 是否遭受干旱
	int droughtDay;			// 干旱天数
	bool isFertilized;		// 当前的作物是否施肥
	
	// 不同季节对应的生长阶段天数数组
	std::map<std::string, std::vector<int>> seasonalGrowthStageDay;
public:
	// 构造函数
	Crop(const CropType& cropType);

	// 初始化
	virtual bool init();

	// 处理作物的生长,虚函数
	virtual void grow() {};

	// 土壤对作物的影响
	void soilInfluence(int waterLevel,int fertilizeLevel);

	// 判断作物死亡
	bool isDead();

	// 判断作物成熟
	bool isMature();

	// 使用农药
	void applyPesticide();

	// 更新生长阶段
	void updateGrowthStage();

	// 产生病害
	virtual void generatePest()=0;

	// 获取当前作物生长阶段
	int getGrowthStage() const;

	// 判断虫害
	bool judgeInfested() const;

	// 获得当前作物种类
	CropType getCropType() const;
};
#endif