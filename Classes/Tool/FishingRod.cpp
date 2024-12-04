#include "FishingRod.h"
#include "../Player/Player.h"
#include "../Scene/FarmScene.h" 
#include "cocos2d.h"
#include "cocos/editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

bool FishingRod::isUsed = false;

FishingRod* FishingRod::create() {
	FishingRod* fishingRod = new (std::nothrow) FishingRod();
	if (fishingRod && fishingRod->init()) {
		fishingRod->autorelease();
		return fishingRod;
	}
	CC_SAFE_DELETE(fishingRod);
	return nullptr;
}

bool FishingRod::init()
{
    // 调用基类的初始化方法
    return Tool::init("fishingRod");
}

void FishingRod::useTool()
{
    // 获取玩家实例
    Player* player = Player::getInstance();
    // 创建动画帧
    Vector<SpriteFrame*> frames;

    Vec2 direction = player->getLastDirection();

    // 创建扔出鱼竿的动画
    frames.pushBack(SpriteFrame::create(ResPath::FISHING_OUT_1, ToolRects::FISHING_OUT_1));
    frames.pushBack(SpriteFrame::create(ResPath::FISHING_OUT_2, ToolRects::FISHING_OUT_2));
    frames.pushBack(SpriteFrame::create(ResPath::FISHING_OUT_3, ToolRects::FISHING_OUT_3));
    frames.pushBack(SpriteFrame::create(ResPath::FISHING_OUT_4, ToolRects::FISHING_OUT_4));

    // 创建动画
    auto animation = Animation::createWithSpriteFrames(frames, 0.1f);  // 每帧持续 0.1 秒
    auto animate = Animate::create(animation);

    // 动作序列：播放动画后，执行额外的逻辑
    auto sequence = Sequence::create(
        animate,
        CallFunc::create([=]() {
            // 创建动画帧
            Vector<SpriteFrame*> framesWaiting;

            Vec2 direction = player->getLastDirection();

            // 创建扔出鱼竿的动画
            framesWaiting.pushBack(SpriteFrame::create(ResPath::FISHING_WAITING_1, ToolRects::FISHING_WAITING_1));
            framesWaiting.pushBack(SpriteFrame::create(ResPath::FISHING_WAITING_2, ToolRects::FISHING_WAITING_2));

            auto animationWaiting = Animation::createWithSpriteFrames(framesWaiting, 0.5f);
            animationWaiting->setLoops(-1);
            auto animateWait = Animate::create(animationWaiting);

            player->runAction(animateWait);
            }),

            nullptr
            );

    if (isUsed == true) {
        player->stopAllActions(); // 停止浮动动画
        this->reelInRod();      // 播放收回动画
        isUsed = false;
    }
    else {
        player->runAction(sequence);
        isUsed = true;
    }
}

void FishingRod::reelInRod()
{
    // 获取玩家实例
    Player* player = Player::getInstance();
    // 创建动画帧
    Vector<SpriteFrame*> frames;

    Vec2 direction = player->getLastDirection();
    frames.pushBack(SpriteFrame::create(ResPath::FISHING_IN_1, ToolRects::FISHING_IN_1));
    frames.pushBack(SpriteFrame::create(ResPath::FISHING_IN_2, ToolRects::FISHING_IN_2));
    frames.pushBack(SpriteFrame::create(ResPath::STAND_RIGHT, ToolRects::STAND_RIGHT));

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
