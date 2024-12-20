/****************************************************************
 * File Function: 农场动物管理类，实现农场上的动物的管理
 * Author:        高鑫
 ****************************************************************/
#include "AnimalManager.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// AnimalManager类：构造函数
AnimalManager::AnimalManager() :
	animalCount(0){
}

// AnimalManager类：析构函数
AnimalManager::~AnimalManager() {
}

// 静态创建
AnimalManager* AnimalManager::create() {
	AnimalManager* animalManager = new AnimalManager();
	if (animalManager && animalManager->init()) {
		animalManager->autorelease();
		return animalManager;
	}

	CC_SAFE_DELETE(animalManager);
	return nullptr;
}

// AnimalManager类：往场景中添加动物
void AnimalManager::addAnimal(Animal* animal, const cocos2d::Vec2& position) {

	// 判断是否为空
	if (animal == nullptr) {
		return;
	}
	// 添加动物
	animals.push_back(animal);
	addChild(animal,static_cast<int>(animals.size()));
	animal->setPosition(position);
}


// AnimalManager类：更新所有动物的状态
void AnimalManager::updateAnimals() {

}

// AnimalManager类：喂养动物
void AnimalManager::feedAnimal() {

}