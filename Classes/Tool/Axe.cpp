#include "Axe.h"
#include "../Player/Player.h"

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

void Axe::useTool() {
    // 获取玩家实例
    Player* player = Player::getInstance();

    // 创建动画帧
    Vector<SpriteFrame*> frames;

    Vec2 direction = player->getLastDirection();
    if (direction.x > 0) {
        frames.pushBack(SpriteFrame::create("tools/rightUseAxe1.png", Rect(0, 0, 100, 183)));
        frames.pushBack(SpriteFrame::create("tools/rightUseAxe2.png", Rect(0, 0, 201, 183)));
        frames.pushBack(SpriteFrame::create("tools/rightUseAxe3.png", Rect(0, 0, 165, 164)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standRight.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.x < 0) {
        frames.pushBack(SpriteFrame::create("tools/leftUseAxe1.png", Rect(0, 0, 100, 183)));
        frames.pushBack(SpriteFrame::create("tools/leftUseAxe2.png", Rect(0, 0, 201, 183)));
        frames.pushBack(SpriteFrame::create("tools/leftUseAxe3.png", Rect(0, 0, 165, 164)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standLeft.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.y > 0) {
        frames.pushBack(SpriteFrame::create("tools/upUseAxe1.png", Rect(0, 0, 85, 200)));
        frames.pushBack(SpriteFrame::create("tools/upUseAxe2.png", Rect(0, 0, 81, 127)));
        frames.pushBack(SpriteFrame::create("tools/upUseAxe3.png", Rect(0, 0, 75, 145)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standUp.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.y < 0) {
        frames.pushBack(SpriteFrame::create("tools/downUseAxe1.png", Rect(0, 0, 74, 185)));
        frames.pushBack(SpriteFrame::create("tools/downUseAxe2.png", Rect(0, 0, 75, 127)));
        frames.pushBack(SpriteFrame::create("tools/downUseAxe3.png", Rect(0, 0, 77, 109)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standDown.png", Rect(0, 0, 70, 120)));
    }

    // 创建动画
    auto animation = Animation::createWithSpriteFrames(frames, 0.1f);  // 每帧持续 0.1 秒
    auto animate = Animate::create(animation);

    // 动作序列：播放动画后，执行额外的逻辑
    auto sequence = Sequence::create(
        animate,
        CallFunc::create([=]() {
            CCLOG("Using axe at player position (%f, %f)", getPositionX(), getPositionY());
            // todo: 可以添加逻辑，比如检测是否命中目标
            }),
        nullptr
    );
    player->runAction(sequence);  // 播放动画
}
