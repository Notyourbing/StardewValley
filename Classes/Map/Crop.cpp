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

Corn::Corn()
{
	// 空构造函数，父类已经进行初始化了

}

void Corn::updateGrowth(int deltaTime)
{
	
}