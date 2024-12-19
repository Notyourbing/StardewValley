#ifndef __COW_H__
#define __COW_H__

#include "Animal.h"
#include "cocos2d.h"

// Cow类：继承自Animal
class Cow :public Animal {
public:
	// 静态成员函数，用于创建并返回一个新的 Cow 类型对象的实例
	static Cow* create(cocos2d::Vec2 position);

	// 初始化对象
	bool init() override;

private:
	// 构造函数
	Cow(cocos2d::Vec2 position);

	// 析构函数
	~Cow() ;

	// 产奶量
	int milkProduction;
};

#endif 
