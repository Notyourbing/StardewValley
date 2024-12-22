/****************************************************************
 * File Function: 农场资源管理类，管理农场资源，如⽔资源、种⼦和肥料存储
 * Author:        高鑫
 ****************************************************************/
#ifndef __FARM_RESOURCE_MANAGER_H__
#define __FARM_RESOURCE_MANAGER_H__

#include "cocos2d.h"
#include <map>

// 农场资源管理类
class FarmResourceManager {
private:
	int waterResource;				// 水资源
	int seedResource;				// 种子资源
	int ferilizerResource;			// 肥料资源

public:
	// 静态创建函数
	static FarmResourceManager* create();

	// 初始化
	bool init();

	// 浇水
	void useWater();

	// 施肥
	void useFertilize();

	// 播种
	void useSeed();
};

#endif 
