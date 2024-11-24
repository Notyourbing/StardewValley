#include "Axe.h"

USING_NS_CC;

Axe* Axe::create() {
	Axe* axe = new (std::nothrow) Axe();
	if (axe && axe->init()) {
		axe->autorelease();
		return axe;
	}
	CC_SAFE_DELETE(axe);
	return nullptr;
}

bool Axe::init() {
	// 调用基类的初始化方法
	return Tool::init("axe");
}

void Axe::useTool(const Vec2& targetPosition) {
	// 播放斧头使用动画（示例实现）
	auto chopAction = Sequence::create(
		MoveTo::create(0.1f, targetPosition), // 移动到目标位置
		CallFunc::create([=]() {
			CCLOG("Chopping at position (%f, %f)", targetPosition.x, targetPosition.y);
			}),
		MoveTo::create(0.1f, this->getPosition()), // 返回原位置
		nullptr
	);
	this->runAction(chopAction);
}