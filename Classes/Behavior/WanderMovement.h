/****************************************************************
 * File Function: 漫游移动类，继承自移动控制基类，控制精灵漫游移动
 * Author:        高鑫
 ****************************************************************/
#ifndef __WANDERMOVEMENT_H__
#define __WANDERMOVEMENT_H__

#include "cocos2d.h"
#include "MovementBehavior .h"
#include "../Animal/Animal.h"

// 漫游移动控制类
class WanderMovement : public MovementBehavior {
public:
	// 静态构造函数
	static WanderMovement* create(float radius,float interval);

	// 初始化
	bool init(float radius , float interval );

	// 构造函数
	WanderMovement();

	// 析构函数
	virtual ~WanderMovement();

	// 执行移动行为函数
	void execute(Animal* animal) ;

	// 天气影响
	void weatherChanged(float& radius, float& moveDuration) override;
private:
	// 移动距离
	float moveRadius;

	// 移动间隔
	float moveInterval;

	// 动物的初始位置
	cocos2d::Vec2 initialPosition;

	// 具体移动实现
	void performRandomMove(Animal* animal);

	// 定时器key
	std::string moveScheduleKey;
};
#endif 