#include "CooperationScene.h"
#include "SimpleAudioEngine.h"
#include "../Constant/Constant.h"

USING_NS_CC;

Scene* Cooperation::createScene() {
    return Cooperation::create();
}

bool Cooperation::init() {
    if (!Scene::init()) {
        return false;
    }

    // 背景
    auto background = Sprite::create(ResPath::COOP_BACKGROUND);
    if (background) {
        background->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2));
        this->addChild(background, 0); // 背景的 z-order 最低
    }

    // 合作框
    auto coopPanel = Sprite::create(ResPath::COOP_PANEL);
    if (coopPanel) {
        coopPanel->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2));
        this->addChild(coopPanel, 1);
    }

    // 文字提示
    coopText = Label::createWithTTF(COOP_TEXT_CONTENT, ResPath::FONT_TTF, 24);
    if (coopText) {
        const Vec2 textPosition = Vec2(WINSIZE.width / 2, WINSIZE.height / 2); // 调整文字位置，使其位于屏幕中心
        coopText->setPosition(textPosition);
        this->addChild(coopText, 2);
    }

    // 返回项
    auto backItem = MenuItemImage::create(
        ResPath::BACK_BUTTON,                               // 返回按钮的普通状态图片
        ResPath::BACK_BUTTON,                               // 返回按钮的按下状态图片
        CC_CALLBACK_1(Cooperation::backCallBack, this));    // 点击回调函数
    if (backItem) {
        const float x = WINSIZE.width - backItem->getContentSize().width / 2 - BACK_BUTTON_PADDING_RIGHT;
        const float y = BACK_BUTTON_PADDING_BOTTOM + backItem->getContentSize().height / 2;
        backItem->setPosition(Vec2(x, y));
    }

    // 菜单容器
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 3);

    // 上下翻面的按钮
    auto upButton = MenuItemImage::create(
        ResPath::UP_ARROW,
        ResPath::UP_ARROW,
        CC_CALLBACK_1(Cooperation::onUpButtonClicked, this));
    auto downButton = MenuItemImage::create(
        ResPath::DOWN_ARROW,
        ResPath::DOWN_ARROW,
        CC_CALLBACK_1(Cooperation::onDownButtonClicked, this));

    // 按钮放置在右侧
    if (upButton && downButton) {
        upButton->setPosition(Vec2(WINSIZE.width - ARROW_BUTTON_PADDING, WINSIZE.height / 2 + UP_BUTTON_OFFSET_Y));
        downButton->setPosition(Vec2(WINSIZE.width - ARROW_BUTTON_PADDING, WINSIZE.height / 2 + DOWN_BUTTON_OFFSET_Y));
    }

    // 按钮菜单
    auto buttonMenu = Menu::create(upButton, downButton, NULL);
    if (buttonMenu) {
        buttonMenu->setPosition(Vec2::ZERO);
        this->addChild(buttonMenu, 4);
    }

    return true;
}

// 返回按钮回调函数
void Cooperation::backCallBack(Ref* pSender) {
    Director::getInstance()->popScene(); // 返回上一个场景
}

// 向上按钮回调函数
void Cooperation::onUpButtonClicked(Ref* pSender) {
    if (coopText) {
        auto moveBy = MoveBy::create(0.3f, Vec2(0, -MOVE_BY_DISTANCE)); // 向下移动指定像素
        coopText->runAction(moveBy);                                    // 执行动作
    }
}

// 向下按钮回调函数
void Cooperation::onDownButtonClicked(Ref* pSender) {
    if (coopText) {
        auto moveBy = MoveBy::create(0.3f, Vec2(0, MOVE_BY_DISTANCE));  // 向上移动指定像素
        coopText->runAction(moveBy);                                    // 执行动作
    }
}