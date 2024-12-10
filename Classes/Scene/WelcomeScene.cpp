#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include "CooperationScene.h"
#include "NewGameScene.h"
#include "FarmScene.h"
#include "../Constant/Constant.h"
#include "../SaveManage/SaveManage.h"

USING_NS_CC;

Scene* Welcome::createScene() {
    return Welcome::create();
}

bool Welcome::init() {
    // 检查是否初始化父类
    if (!Scene::init()) {
        return false;
    }

    // 背景图片
    auto background = Sprite::create(ResPath::BACKGROUND_IMAGE);
    if (background) {
        const float x = WINSIZE.width / 2;
        const float y = WINSIZE.height / 2;
        background->setPosition(Vec2(x, y));
    }
    this->addChild(background, -1);     // 将背景添加到场景中


    // 新游戏项
    auto newGameItem = MenuItemImage::create(ResPath::NEW_GAME_ITEM, ResPath::NEW_GAME_ON_ITEM,
        CC_CALLBACK_1(Welcome::menuNewGameCallback, this));
    if (newGameItem) {
        const float x = -1.5 * (newGameItem->getContentSize().width + MENU_ITEM_INTERVAL);
        newGameItem->setPosition(Vec2(x, 0.0f));
    }

    // 加载游戏项
    auto loadGameItem = MenuItemImage::create(ResPath::LOAD_GAME_ITEM, ResPath::LOAD_GAME_ON_ITEM,
        CC_CALLBACK_1(Welcome::menuLoadGameCallback, this));
    if (loadGameItem) {
        const float x = -0.5 * (loadGameItem->getContentSize().width + MENU_ITEM_INTERVAL);
        loadGameItem->setPosition(Vec2(x, 0.0f));
    }

    // 合作项
    auto cooperationItem = MenuItemImage::create(ResPath::COOPERATION_ITEM, ResPath::COOPERATION_ON_ITEM,
        CC_CALLBACK_1(Welcome::menuCooperationCallback, this));
    if (cooperationItem) {
        const float x = 0.5 * (cooperationItem->getContentSize().width + MENU_ITEM_INTERVAL);
        cooperationItem->setPosition(Vec2(x, 0.0f));
    }

    // 退出项
    auto closeItem = MenuItemImage::create(ResPath::EXIT_ITEM, ResPath::EXIT_ON_ITEM,
        CC_CALLBACK_1(Welcome::menuExitCallback, this));
    if (closeItem) {
        const float x = 1.5 * (closeItem->getContentSize().width + MENU_ITEM_INTERVAL);
        closeItem->setPosition(Vec2(x, 0.0f));
    }

    // 创建菜单容器
    auto menu = Menu::create(closeItem, NULL);
    menu->addChild(newGameItem);
    menu->addChild(loadGameItem);
    menu->addChild(cooperationItem);
    const float menuX = WINSIZE.width / 2;
    const float menuY = WINSIZE.height / 6;
    menu->setPosition(Vec2(menuX, menuY));
    this->addChild(menu, 1);

    // 欢迎标签
    auto label = Label::createWithTTF("Welcome!", ResPath::FONT_TTF, 24);
    if (label) {
        label->setPosition(Vec2( + WINSIZE.width / 2,
            WINSIZE.height - label->getContentSize().height));
        this->addChild(label, 1);
    }

    // 创建标题
    auto sprite = Sprite::create(ResPath::TITLE);
    if (sprite) {
        sprite->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 3 * 2));
        this->addChild(sprite, 0);
    }

    return true;
}

// 新游戏项回调函数
void Welcome::menuNewGameCallback(cocos2d::Ref* pSender) {
    auto newGameScene = NewGame::createScene();
    auto transition = TransitionFade::create(0.5f, newGameScene, PURPUL); // 0.5秒，淡入紫色背景
    Director::getInstance()->pushScene(transition);
}

// 加载游戏项回调函数
void Welcome::menuLoadGameCallback(cocos2d::Ref* pSender) {
    // 加载存档数据
    SaveManage::getInstance()->loadGameData();

    // 创建农场场景
    auto farmScene = Farm::createScene();
    auto transition = TransitionFade::create(0.5f, farmScene, cocos2d::Color3B::WHITE); // 0.5秒，淡入白色背景
    Director::getInstance()->pushScene(transition);
}

// 合作项回调函数
void Welcome::menuCooperationCallback(Ref* pSender) {
    auto cooperationScene = Cooperation::createScene();
    auto transition = TransitionFade::create(0.5f, cooperationScene, PURPUL); // 0.5秒，淡入紫色背景
    Director::getInstance()->pushScene(transition);
}

// 关闭引用项回调函数
void Welcome::menuExitCallback(Ref* pSender) {
    // 关闭应用程序
    Director::getInstance()->end();
}
