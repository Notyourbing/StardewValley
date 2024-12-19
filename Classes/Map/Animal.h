#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#include "cocos2d.h"
#include "../Behavior/MovementBehavior .h"
#include<string>

/*
 * Class Name:     Animal
 * Class Function: 农场动物基类类
 */
class Animal : public cocos2d::Sprite {
public:
	// 获取动物位置
	cocos2d::Vec2 getAnimalPosition();
	
	// 获取动物姓名
	std::string getAnimalName();

	// 初始化
	virtual bool init();
protected:
	// 构造函数
	Animal(cocos2d::Vec2 position);

	// 析构函数
	virtual ~Animal();

	// 是否饥饿
	bool isHungry;
private:
	// 动物姓名
	std::string animalName;

	// 动物位置
	cocos2d::Vec2 position;

	// 动物移动
	virtual void setMovementBehavior(MovementBehavior* behavior)=0;
};
#endif 
