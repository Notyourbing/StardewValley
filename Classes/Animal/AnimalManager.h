/****************************************************************
 * File Function: 农场动物管理类的实现，实现农场上的动物的管理
 * Author:        高鑫
 ****************************************************************/
#ifndef __ANIMAL_MANAGER_H__
#define __ANIMAL_MANAGER_H__

#include "cocos2d.h"
#include "Animal.h"
#include<vector>

// AnimalManager类：农场中的动物管理
class AnimalManager :public cocos2d::Node {
public:
	// 静态创建
	static AnimalManager* create();

	// 添加单个动物
	void addAnimal(Animal* animal, const cocos2d::Vec2& position);

	// 更新所有动物状态
	void updateAnimals();

	// 喂养动物
	void feedAnimal();
private:
	// 动物数量
	int animalCount;

	// 构造函数
	AnimalManager();

	// 析构函数
	virtual ~AnimalManager();

	// 农场包含的动物
	std::vector<Animal*> animals;
};

#endif 