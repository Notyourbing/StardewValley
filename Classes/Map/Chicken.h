#ifndef __CHICKEN_H__
#define __CHICKEN_H__

#include "Animal.h"

// Chicken类：继承自Animal
class Chicken : public Animal {
public:
	// 静态成员函数，用于创建并返回一个新的 Cow 类型对象的实例
	static Chicken* create(const cocos2d::Vec2& position);

	// 初始化对象
	bool init() override;
private:
	// 构造函数
	Chicken(const cocos2d::Vec2& position);

	// 析构函数
	~Chicken();

	// 下蛋数量
	int eggCount;
};

#endif 
