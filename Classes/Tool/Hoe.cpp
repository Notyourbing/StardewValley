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
    // 获取玩家实例
    Player* player = Player::getInstance();
    // 创建动画帧
    Vector<SpriteFrame*> frames;

    Vec2 direction = player->getLastDirection();
    if (direction.x > 0) {
        frames.pushBack(SpriteFrame::create("tools/hoe/rightUseHoe1.png", Rect(0, 0, 128, 180)));
        frames.pushBack(SpriteFrame::create("tools/hoe/rightUseHoe2.png", Rect(0, 0, 169, 184)));
        frames.pushBack(SpriteFrame::create("tools/hoe/rightUseHoe3.png", Rect(0, 0, 206, 271)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standRight.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.x < 0) {
        frames.pushBack(SpriteFrame::create("tools/hoe/leftUseHoe1.png", Rect(0, 0, 128, 180)));
        frames.pushBack(SpriteFrame::create("tools/hoe/leftUseHoe2.png", Rect(0, 0, 169, 184)));
        frames.pushBack(SpriteFrame::create("tools/hoe/leftUseHoe3.png", Rect(0, 0, 206, 271)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standLeft.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.y > 0) {
        frames.pushBack(SpriteFrame::create("tools/hoe/upUseHoe1.png", Rect(0, 0, 89, 190)));
        frames.pushBack(SpriteFrame::create("tools/hoe/upUseHoe2.png", Rect(0, 0, 83, 190)));
        frames.pushBack(SpriteFrame::create("tools/hoe/upUseHoe3.png", Rect(0, 0, 97, 145)));
        frames.pushBack(SpriteFrame::create("playerWalkImages/standUp.png", Rect(0, 0, 70, 120)));
    }
    else if (direction.y < 0) {
        frames.pushBack(SpriteFrame::create("tools/hoe/downUseHoe1.png", Rect(0, 0, 70, 196)));
        frames.pushBack(SpriteFrame::create("tools/hoe/downUseHoe2.png", Rect(0, 0, 70, 195)));
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

	player->runAction(sequence);
}