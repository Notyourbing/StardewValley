#include "CooperationScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

// 打印有用的报错信息
static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in WelcomeScene.cpp\n");
}

Scene* Cooperation::createScene() {
    return Cooperation::create();
}

bool Cooperation::init() {
    if (!Scene::init()) {
        return false;
    }

    // 获取界面尺寸
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建背景
    std::string backgroundPath = "icon/coopBackground.png";
    auto background = Sprite::create(backgroundPath);
    if (background == nullptr) {
        problemLoading(backgroundPath.c_str());
        return false;
    }
    else {
        background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        // 确保背景的 z-order 最低
        this->addChild(background, 0);
    }

    // 创建合作框背景
    std::string coopPanelPath = "icon/cooperationPanel.png";
    auto coopPanel = Sprite::create(coopPanelPath);
    coopPanel->setName("coopPanel");

    if (coopPanel == nullptr) {
        problemLoading(coopPanelPath.c_str());
        return false;
    }
    else {
        coopPanel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(coopPanel, 1);

        // 文字提示（寻找）
        coopText = Label::createWithTTF("Connecting to online services...", "fonts/Marker Felt.ttf", 24);  // 调整字体大小
        if (coopText == nullptr) {
            problemLoading("Error loading font for coopText\n");
            return false;
        }
        else {
            // 调整文字位置，使其位于屏幕中心
            const Vec2 textPosition = Vec2(visibleSize.width / 2, visibleSize.height / 2);
            coopText->setPosition(textPosition);
            // 确保文字的 z-order 高于合作框
            this->addChild(coopText, 2);
        }
    }

    // 返回项
    auto backItem = MenuItemImage::create(
        "icon/backButton.png",
        "icon/backButton.png",
        CC_CALLBACK_1(Cooperation::backCallBack, this));
    if (backItem == nullptr ||
        backItem->getContentSize().width <= 0 ||
        backItem->getContentSize().height <= 0) {
        problemLoading("backItem wrong");
    }
    else {
        // 靠近右下角的位置
        const float rightPadding = 40;
        const float bottomPadding = 20;
        const float x = origin.x + visibleSize.width - backItem->getContentSize().width / 2 - rightPadding;
        const float y = origin.y + bottomPadding + backItem->getContentSize().height / 2;
        backItem->setPosition(Vec2(x, y));
        //this->addChild(backItem, 5);  // 确保 backItem 的 z-order 高于 coopPanel 和 coopText
    }
    // 创建菜单容器
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 8);

    // 上下翻面的按钮
    auto upButton = MenuItemImage::create(
        "icon/upArrow.png",  // 向上箭头图标
        "icon/upArrow.png",  // 向上箭头图标
        CC_CALLBACK_1(Cooperation::onUpButtonClicked, this));
    auto downButton = MenuItemImage::create(
        "icon/downArrow.png",  // 向下箭头图标
        "icon/downArrow.png",  // 向下箭头图标
        CC_CALLBACK_1(Cooperation::onDownButtonClicked, this));

    // 确保按钮位置正确，放置在右侧面板
    const float buttonPadding = 40;
    upButton->setPosition(Vec2(visibleSize.width - buttonPadding, visibleSize.height / 2 + 50));
    downButton->setPosition(Vec2(visibleSize.width - buttonPadding, visibleSize.height / 2 - 50));

    auto buttonMenu = Menu::create(upButton, downButton, NULL);
    buttonMenu->setPosition(Vec2::ZERO);
    this->addChild(buttonMenu, 7);  // 确保按钮的 z-order 高于 backItem

    return true;
}

void Cooperation::backCallBack(Ref* pSender) {
    Director::getInstance()->popScene();
}

void Cooperation::onUpButtonClicked(Ref* pSender) {
    printf("Up button clicked\n");  // 添加日志
    if (coopText) {
        auto moveBy = MoveBy::create(0.3f, Vec2(0, -50)); // 向下移动 50 像素
        coopText->runAction(moveBy);
    }
}

void Cooperation::onDownButtonClicked(Ref* pSender) {
    printf("Down button clicked\n");  // 添加日志
    if (coopText) {
        auto moveBy = MoveBy::create(0.3f, Vec2(0, 50)); // 向上移动 50 像素
        coopText->runAction(moveBy);
    }
}