#include "Crop.h"

USING_NS_CC;

void Crop::water()
{
	watered = true;
}

void Crop::fertilize()
{
	fertilized = true;
}

int Crop::getCropState() const
{
	return growthStage;
}

Corn::Corn()
{
	// 空构造函数，父类已经进行初始化了

}


void Corn::updateGrowth(int deltaTime)
{
	
}