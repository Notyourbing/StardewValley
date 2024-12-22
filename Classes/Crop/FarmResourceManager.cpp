/****************************************************************
 * File Function: 农场资源管理类的实现
 * Author:        高鑫
 ****************************************************************/

#include "FarmResourceManager.h"
#include "../Constant/Constant.h"
#include "cocos2d.h"

 // 静态创建函数
FarmResourceManager* FarmResourceManager::create() {
	FarmResourceManager* farmResourceManager = new (std::nothrow) FarmResourceManager();
	if (farmResourceManager && farmResourceManager->init()) {
		return farmResourceManager;
	}
	CC_SAFE_DELETE(farmResourceManager);
	return nullptr;
}

// 初始化
bool FarmResourceManager::init() {
	waterResource=MAX_WATER_RESOURCE;				// 水资源
	seedResource = MAX_SEED_RESOURCE;				// 种子资源
	ferilizerResource = MAX_FERTILIZE_RESOURCE;		// 肥料资源
	return true;
}

// 浇水
void FarmResourceManager::useWater() {
	// 水资源减少
	waterResource -= AMOUNT_OF_WATER_PER_USE;
}

// 施肥
void FarmResourceManager::useFertilize() {
	// 肥料资源减少
	ferilizerResource-= AMOUNT_OF_FERTILIZE_PER_USE;
}

// 播种
void FarmResourceManager::useSeed() {
	// 种子减少
	seedResource--;
}