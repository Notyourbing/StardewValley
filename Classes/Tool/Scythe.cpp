#include "Scythe.h"
#include "../Player/Player.h"
#include "../Constant/Constant.h"

USING_NS_CC;

Scythe* Scythe::create() {
    Scythe* scythe = new (std::nothrow) Scythe();
    if (scythe && scythe->init()) {
        scythe->autorelease();
        return scythe;
    }
    CC_SAFE_DELETE(scythe);
    return nullptr;
}

bool Scythe::init() {
    // 调用基类的初始化方法
    return Tool::init("scythe");
}

void Scythe::useTool() {
    // 获取玩家实例
    Player* player = Player::getInstance();
    // 创建动画帧
    Vector<SpriteFrame*> frames;

    Vec2 direction = player->getLastDirection();
    if (direction.x > 0) { // 玩家面向右侧
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_RIGHT_1, ToolRects::SCYTHE_RIGHT_1));
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_RIGHT_2, ToolRects::SCYTHE_RIGHT_2));
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_RIGHT_3, ToolRects::SCYTHE_RIGHT_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_RIGHT, ToolRects::STAND_RIGHT));
    }
    else if (direction.x < 0) { // 玩家面向左侧
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_LEFT_1, ToolRects::SCYTHE_LEFT_1));
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_LEFT_2, ToolRects::SCYTHE_LEFT_2));
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_LEFT_3, ToolRects::SCYTHE_LEFT_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_LEFT, ToolRects::STAND_LEFT));
    }
    else if (direction.y > 0) { // 玩家面向上方
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_UP_1, ToolRects::SCYTHE_UP_1));
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_UP_2, ToolRects::SCYTHE_UP_2));
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_UP_3, ToolRects::SCYTHE_UP_3));
        frames.pushBack(SpriteFrame::create(ResPath::STAND_UP, ToolRects::STAND_UP));
    }
    else if (direction.y < 0) { // 玩家面向下方
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_DOWN_1, ToolRects::SCYTHE_DOWN_1));
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_DOWN_2, ToolRects::SCYTHE_DOWN_2));
        frames.pushBack(SpriteFrame::create(ResPath::SCYTHE_DOWN_3, ToolRects::SCYTHE_DOWN_3));
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
