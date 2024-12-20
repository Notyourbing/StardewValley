/****************************************************************
 * File Function: 实现水壶类，继承自Tool类
 * Author:        韦瑾钰 高鑫
 ****************************************************************/
#include "Kettle.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// Kettle类：静态创建对象
Kettle* Kettle ::create() {
	Kettle *kettle = new(std::nothrow) Kettle();
	if (kettle && kettle->init()) {
		kettle->autorelease();
		return kettle;
	}
	CC_SAFE_DELETE(kettle);
	return nullptr;
}

// 初始化水壶
bool Kettle::init() {
	// 调用基类的初始化方法
    return Tool::init({"kettle", KETTLE});
}

// 获得当前水壶里的水量
int Kettle::getCurrentWaterLevel() const {
    return waterLevel;
}

// 补充当前水壶里的水量
void Kettle::refillWateringCan(int water) {
    waterLevel += water;
}

// Kettle类：构造函数
Kettle::Kettle() {
	waterLevel = MAX_WATERINGCAN_CAPACITY;
}

// 使用工具
void Kettle::useItem() {
    // 获取玩家实例
    Player* player = Player::getInstance();

    // 创建动画帧
    Vector<SpriteFrame*> frames;

    Vec2 direction = player->getLastDirection();
    if (direction.x > 0) { // 玩家面向右侧
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_RIGHT_1, ToolRects::KETTLE_RIGHT_1));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_RIGHT_2, ToolRects::KETTLE_RIGHT_2));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_RIGHT_3, ToolRects::KETTLE_RIGHT_3));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_RIGHT_4, ToolRects::KETTLE_RIGHT_4));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_RIGHT_5, ToolRects::KETTLE_RIGHT_5));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_RIGHT, ToolRects::STAND_RIGHT));
    }
    else if (direction.x < 0) { // 玩家面向左侧
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_LEFT_1, ToolRects::KETTLE_LEFT_1));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_LEFT_2, ToolRects::KETTLE_LEFT_2));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_LEFT_3, ToolRects::KETTLE_LEFT_3));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_LEFT_4, ToolRects::KETTLE_LEFT_4));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_LEFT_5, ToolRects::KETTLE_LEFT_5));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_LEFT, ToolRects::STAND_LEFT));
    }
    else if (direction.y > 0) { // 玩家面向上方
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_UP_1, ToolRects::KETTLE_UP_1));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_UP_2, ToolRects::KETTLE_UP_2));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_UP_3, ToolRects::KETTLE_UP_3));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_UP_4, ToolRects::KETTLE_UP_4));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_UP, ToolRects::STAND_UP));
    }
    else if (direction.y < 0) { // 玩家面向下方
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_DOWN_1, ToolRects::KETTLE_DOWN_1));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_DOWN_2, ToolRects::KETTLE_DOWN_2));
        frames.pushBack(SpriteFrame::create(ResPath::KETTLE_DOWN_3, ToolRects::KETTLE_DOWN_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_DOWN, ToolRects::STAND_DOWN));
    }

    // 创建动画
    auto animation = Animation::createWithSpriteFrames(frames, 0.1f);  // 每帧持续 0.1 秒
    auto animate = Animate::create(animation);

    // 动作序列：播放动画后，执行额外的逻辑
    auto sequence = Sequence::create(
        animate,
        CallFunc::create([=]() {
            }),
            nullptr
            );
    player->runAction(sequence);  // 播放动画

    // 减少水壶里的水
    if (waterLevel >= AMOUNT_OF_WATER_PER_USE) {
        waterLevel -= AMOUNT_OF_WATER_PER_USE;
    }
}