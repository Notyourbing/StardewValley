/****************************************************************
 * File Function: 农场动物抽象基类的实现
 * Author:        高鑫
 ****************************************************************/
#include "Animal.h"

USING_NS_CC;

// 获得动物位置
Vec2 Animal::getAnimalPosition() {
	return position;
}

// 获得动物姓名
std::string Animal::getAnimalName() {
	return animalName;
}

// 初始化
bool Animal::init() {
	return true;
}

// 构造函数
Animal::Animal(Vec2 position) :
	position(position), isHungry(true){
}

// 析构函数
Animal::~Animal() {

}