#ifndef __DOGBANEFOOD_H__
#define __DOGBANEFOOD_H__

#include "cocos2d.h"
#include "Food.h"

/*
 * Class Name:     DogbaneFood
 * Class Function: 防风草食物类
 */
class DogbaneFood : public Food {
public:
	// 静态创建方法
	static DogbaneFood* create();

	// 初始化防风草食物
	bool init() override;

};
#endif // !__DOGBANEFOOD_H__
