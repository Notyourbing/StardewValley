#include "Hoe.h"
#include "../Player/Player.h"

USING_NS_CC;

Hoe* Hoe::create() {
	Hoe* hoe = new (std::nothrow) Hoe();
	if (hoe && hoe->init()) {
		hoe->autorelease();
		return hoe;
	}
	CC_SAFE_DELETE(hoe);
}

bool Hoe::init() {
	// 调用基类的初始化方法
	return Tool::init("hoe");
}

void Hoe::useTool() {
	// 播放斧头使用动画
	auto rotationAction = RotateBy::create(0.2f, 90); // 顺时针旋转九十度，耗时0.2秒
	auto resetRotationAction = RotateBy::create(0.2f, -90); // 回复初始角度
	setVisible(true);
	// 动作序列
	auto sequence = Sequence::create(
		rotationAction,
		CallFunc::create([=]() {
			CCLOG("Using axe at player position (%f, %f)", getPositionX(), getPositionY());
			// todo 可以添加逻辑，比如检测是否命中目标
			}),
		resetRotationAction,
		nullptr
	);

	this->runAction(sequence);
	setVisible(false);
}