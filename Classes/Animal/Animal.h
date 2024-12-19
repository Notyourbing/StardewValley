#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#include "cocos2d.h"
#include<string>

// Animal类：动物基类
class Animal : public cocos2d::Sprite {
public:
	// 获取动物位置
	cocos2d::Vec2 getPosition();
	
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
};
#endif 
