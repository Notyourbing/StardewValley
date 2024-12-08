#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#include "cocos2d.h"
#include<vector>

// 动物的种类
enum AnimalType {
	CATTLE,			// 牛
	CHICKEN,		// 鸡
	SHEEP,			// 羊
	PIG,			// 猪
};

// 动物产品的列表
enum ProductType {
	BEEF,			// 牛肉
	EGG,			// 鸡蛋
	WOOL,			// 羊毛
	MUTTON,			// 羊肉
	PORK,			// 猪肉
};

// 动物的基类
class Animal : public cocos2d::Sprite{
private:
	AnimalType animalType;				// 动物的种类
	int age;							// 动物的年龄
	cocos2d::Vec2 position;				// 动物的位置
	std::vector<ProductType> product;	// 动物收获的产品
	int growthDay;						// 动物的成长天数
	int maxGrowthDay;					// 动物的成熟天数
	bool isMature;						// 动物是否成熟

protected:

public:

	// 收获
};

// Cattle类表示牛，继承自Animal
class Cattle : public Animal {
private:

public:

};

// Chicken类表示鸡，继承自Animal
class Chicken : public Animal {
private:

public:

};

// Sheep类表示羊，继承自Animal
class Sheep : public Animal {
private:

public:

};

// Pig类表示猪，继承自Animal
class Pig : public Animal {
private:

public:

};

#endif
