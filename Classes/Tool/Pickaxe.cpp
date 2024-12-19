#include "Pickaxe.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"

USING_NS_CC;

Pickaxe* Pickaxe::create() {
	Pickaxe* pickaxe = new(std::nothrow) Pickaxe();
	if (pickaxe && pickaxe->init()) {
		pickaxe->autorelease();
		return pickaxe;
	}
	CC_SAFE_DELETE(pickaxe);
	return nullptr;
}

bool Pickaxe::init() {
	// 调用基类的初始化方法
    return Tool::init({ "pickaxe", PICKAXE});
}

void Pickaxe::useItem() {
    // 获取玩家实例
    Player* player = Player::getInstance();
    // 创建动画帧
    Vector<SpriteFrame*> frames;

    const Vec2 direction = player->getLastDirection();
    if (direction.x > 0) { // 玩家面向右侧
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_RIGHT_1, ToolRects::PICKAXE_RIGHT_1));
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_RIGHT_2, ToolRects::PICKAXE_RIGHT_2));
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_RIGHT_3, ToolRects::PICKAXE_RIGHT_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_RIGHT, ToolRects::STAND_RIGHT));
    }
    else if (direction.x < 0) { // 玩家面向左侧
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_LEFT_1, ToolRects::PICKAXE_LEFT_1));
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_LEFT_2, ToolRects::PICKAXE_LEFT_2));
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_LEFT_3, ToolRects::PICKAXE_LEFT_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_LEFT, ToolRects::STAND_LEFT));
    }
    else if (direction.y > 0) { // 玩家面向上方
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_UP_1, ToolRects::PICKAXE_UP_1));
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_UP_2, ToolRects::PICKAXE_UP_2));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_UP, ToolRects::STAND_UP));
    }
    else if (direction.y < 0) { // 玩家面向下方
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_DOWN_1, ToolRects::PICKAXE_DOWN_1));
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_DOWN_2, ToolRects::PICKAXE_DOWN_2));
        frames.pushBack(SpriteFrame::create(ResPath::PICKAXE_DOWN_3, ToolRects::PICKAXE_DOWN_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_DOWN, ToolRects::STAND_DOWN));
    }

    // 创建动画
    auto animation = Animation::createWithSpriteFrames(frames, 0.1f);  // 每帧持续 0.1 秒
    auto animate = Animate::create(animation);

    // 动作序列：播放动画后，执行额外的逻辑
    auto sequence = Sequence::create(
        animate,
        CallFunc::create([=]() {
            // todo: 可以添加逻辑，比如检测是否命中目标
            }),
            nullptr
            );
    player->runAction(sequence);  // 播放动画
}