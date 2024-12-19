#ifndef __MOVEMENTBEHAVIOR_H__
#define __MOVEMENTBEHAVIOR_H__

#include "cocos2d.h"

/*
 * Class Name:     MovementBehavior
 * Class Function: 移动控制类
 */
class MovementBehavior {
public:
	// 虚析构函数
	virtual ~MovementBehavior() {};

	// 处理天气变化
	virtual void weatherChanged(float& radius, float& interval)=0;
};

#endif // !__MOVEMENTBEHAVIOR_H__

