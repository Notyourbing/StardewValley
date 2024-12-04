#include "WateringCan.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"

USING_NS_CC;

Kettle* Kettle ::create() {
	Kettle *kettle = new(std::nothrow) Kettle();
	if (kettle && kettle->init()) {
		kettle->autorelease();
		return kettle;
	}
	CC_SAFE_DELETE(kettle);
	return nullptr;
}

bool Kettle::init() {
	// 调用基类的初始化方法
	return Tool::init("wateringCan");
}

// 使用工具
void Kettle::useTool() {

}