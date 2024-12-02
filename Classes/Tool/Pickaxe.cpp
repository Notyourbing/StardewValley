#include "PickAxe.h"
#include "../Player/Player.h"

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
	return Tool::init("pickaxe");
}

void Pickaxe::useTool() {
    // 获取玩家实例
    Player* player = Player::getInstance();
    // 创建动画帧
    Vector<SpriteFrame*> frames;

    Vec2 direction = player->getLastDirection();
    if (direction.x > 0) {
        frames.pushBack(SpriteFrame::create("tools/pickaxe/rightUsePickaxe1.png", Rect(0, 0, 131, 198)));
        frames.pushBack(SpriteFrame::create("tools/pickaxe/rightUsePickaxe2.png", Rect(0, 0, 95, 193)));
        frames.pushBack(SpriteFrame::create("tools/pickaxe/rightUsePickaxe3.png", Rect(0, 0, 267, 183)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standRight.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.x < 0) {
        frames.pushBack(SpriteFrame::create("tools/pickaxe/leftUsePickaxe1.png", Rect(0, 0, 131, 198)));
        frames.pushBack(SpriteFrame::create("tools/pickaxe/leftUsePickaxe2.png", Rect(0, 0, 95, 193)));
        frames.pushBack(SpriteFrame::create("tools/pickaxe/leftUsePickaxe3.png", Rect(0, 0, 267, 183)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standLeft.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.y > 0) {
        frames.pushBack(SpriteFrame::create("tools/pickaxe/upUsePickaxe1.png", Rect(0, 0, 98, 261)));
        frames.pushBack(SpriteFrame::create("tools/pickaxe/upUsePickaxe2.png", Rect(0, 0, 93, 146)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standUp.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.y < 0) {
        frames.pushBack(SpriteFrame::create("tools/pickaxe/downUsePickaxe1.png", Rect(0, 0, 86, 270)));
        frames.pushBack(SpriteFrame::create("tools/pickaxe/downUsePickaxe2.png", Rect(0, 0, 81, 203)));
        frames.pushBack(SpriteFrame::create("tools/pickaxe/downUsePickaxe3.png", Rect(0, 0, 63, 132)));
        frames.pushBack(SpriteFrame::create("tools/pickaxe/downUsePickaxe3.png", Rect(0, 0, 69, 131)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standDown.png", Rect(0, 0, 70, 120)));
    }

    // 创建动画
    auto animation = Animation::createWithSpriteFrames(frames, 0.1f);  // 每帧持续 0.1 秒
    auto animate = Animate::create(animation);

    // 动作序列：播放动画后，执行额外的逻辑
    auto sequence = Sequence::create(
        animate,
        CallFunc::create([=]() {
            //CCLOG("Using axe at player position (%f, %f)", getPositionX(), getPositionY());
            // todo: 可以添加逻辑，比如检测是否命中目标
            }),
            nullptr
            );
    player->runAction(sequence);  // 播放动画
}