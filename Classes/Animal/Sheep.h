#ifndef __SHEEP_H__
#define __SHEEP_H__

#include "Animal.h"
#include "cocos2d.h"

// Sheep类：继承自Animal
class Sheep : public Animal {
public:
	// 静态成员函数，用于创建并返回一个新的Sheep类型对象的实例
	static Sheep* create(const cocos2d::Vec2& position);

	// 初始化对象
	bool init() override;

	// 获取羊毛数量
	int getWoolProduction() const;
private:
	// 构造函数
	Sheep(const cocos2d::Vec2& position);

	// 析构函数
	~Sheep();

	// 羊毛数量
	int woolProduction;

	// 设置移动行为
	void setMovementBehavior(MovementBehavior* behavior) override;

	// 移动行为
	MovementBehavior* movementBehavior;
};

#endif 
