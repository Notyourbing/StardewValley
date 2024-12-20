/****************************************************************
 * File Function: 技能树在场景中展示类，用于实现技能树的显示与更新
 * Author:        韦瑾钰 赵卓冰
 ****************************************************************/
#include "SkillTreeUI.h"
#include "SkillTree.h"
#include "../Constant/Constant.h"
#include "../Player/Player.h"
#include "../MyButton/MyButton.h"
#include "../Map/FarmMap.h"
USING_NS_CC;

bool SkillTreeUI::isOpen = false;

// 定义静态实例指针
SkillTreeUI* SkillTreeUI::instance = nullptr;

// 获取单例实例
SkillTreeUI* SkillTreeUI::getInstance() {
    if (!instance) {
        instance = new (std::nothrow) SkillTreeUI();
        if (instance && instance->init()) {
            instance->autorelease();
        }
        else {
            CC_SAFE_DELETE(instance);
        }
    }
    return instance;
}

// 初始化
bool SkillTreeUI::init() {
    isOpen = false;
    if (!Layer::init()) {
        return false;
    }
    setupUI();
    return true;
}

// 更新
void SkillTreeUI::updateUI()
{
    SkillTree* skillTree = SkillTree::getInstance();
    // 每5次升级
    skillTree->setSkillLevel("Agriculture", skillTree->getPlantingCount() / 5);
    skillTree->setSkillLevel("Fishing", skillTree->getFishingCount() / 5);
    skillTree->setSkillLevel("Mining", skillTree->getMiningCount() / 5);
    skillTree->setSkillLevel("Cooking", skillTree->getCookingCount() / 5);
    setupUI();
}

// 展示具体UI
void SkillTreeUI::setupUI() {
    // 获取技能树实例
    auto skillTree = SkillTree::getInstance();

    // 设置背景图片
    auto bg = Sprite::create(ResPath::COOP_PANEL);
    float bgWidth = WINSIZE.width / 2;  // 背景宽度占屏幕的一半
    float bgHeight = WINSIZE.height / 2; // 背景高度占屏幕的一半
    bg->setScaleX(bgWidth / bg->getContentSize().width);  // 按比例缩放宽度
    bg->setScaleY(bgHeight / bg->getContentSize().height); // 按比例缩放高度
    bg->setPosition(WINSIZE.width / 2, WINSIZE.height / 2); // 背景放置在屏幕中心
    addChild(bg);

    // 设置内容的偏移量，确保从背景顶部开始
    int yOffset = bg->getPositionY() + bgHeight / 2 - 50; // 从背景顶部开始的偏移量

    // 遍历技能树，创建UI元素
    for (const auto& skillPair : skillTree->getAllSkills()) {
        const std::string& skillName = skillPair.first;
        Skill* skill = skillPair.second;

        // 技能名称标签
        auto skillLabel = Label::createWithTTF(skillName, ResPath::FONT_TTF, 24);
        skillLabel->setTextColor(cocos2d::Color4B(0, 0, 0, 255));
        skillLabel->setAnchorPoint(Vec2(0, 0.5)); // 左对齐
        skillLabel->setPosition(bg->getPositionX() - bgWidth / 2 + 50, yOffset); // 相对于背景位置
        addChild(skillLabel);

        // 计算技能的进度
        int currentLevel = skill->getCurrentLevel();
        int maxLevel = skill->getMaxLevel();

        // 获取每个级别所占宽度
        float levelWidth = bgWidth / 2 / maxLevel;

        // 横向显示每个级别
        for (int i = 0; i < maxLevel; ++i) {
            auto levelBlock = Sprite::create(ResPath::SKILL_BACKGROUND); // 背景块图片
            levelBlock->setAnchorPoint(Vec2(-5, 0.5));
            levelBlock->setPosition(bg->getPositionX() - bgWidth / 2 + (i * levelWidth), yOffset); // 水平排列
            addChild(levelBlock);

        }

        for (int i = 0; i < currentLevel; ++i) {
            auto levelBlock = Sprite::create(ResPath::SKILL_FOREGROUND); // 前景块图片
            levelBlock->setAnchorPoint(Vec2(-5, 0.5));
            levelBlock->setPosition(bg->getPositionX() - bgWidth / 2 + (i * levelWidth), yOffset); // 水平排列
            addChild(levelBlock);

        }

        // 技能等级标签
        std::string levelText = StringUtils::format("Lv %d/%d", skill->getCurrentLevel(), skill->getMaxLevel());
        auto levelLabel = Label::createWithTTF(levelText, ResPath::FONT_TTF, 20);
        levelLabel->setTextColor(cocos2d::Color4B(0, 0, 0, 255));
        levelLabel->setPosition(bg->getPositionX() + bgWidth / 3, yOffset); // 技能等级标签居中
        addChild(levelLabel);

        yOffset -= 80; // 每行之间间隔80
        setVisible(false);
    }

}

// 关闭按钮的回调函数
void SkillTreeUI::closeCallback(EventListenerMouse* listener) {
    _eventDispatcher->removeEventListener(listener);
    Player::getInstance()->stopAllActions();
    Player::getInstance()->stopMoving();
    setVisible(false);
    isOpen = false;
    Player::getInstance()->setUseItemEnable(true);
}

// 打开UI界面
void SkillTreeUI::openSkillUI() {
    Player::getInstance()->setUseItemEnable(false);

    // 创建关闭按钮
    auto closeButton = MyButton::create(ResPath::SKILL_CLOSE, ResPath::SKILL_CLOSE_ON);
    closeButton->setPosition(Vec2(WINSIZE.width * 3 / 4 - 25, WINSIZE.height * 3 / 4 - 25));
    addChild(closeButton, 2);

    auto listener = EventListenerMouse::create();
    listener->onMouseDown = [=](Event* event) {
        auto mouseEvent = dynamic_cast<EventMouse*>(event);
        if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT && closeButton->isHover())
            closeCallback(listener);
        };
    if (this->getParent()) {
        // 添加到父节点Control对象的目的是为了降低该监听器接受事件的优先级，使得Player useItemEnable的锁生效
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this->getParent());
    }
}

// 析构函数
SkillTreeUI::~SkillTreeUI() {
    if (instance) {
        instance = nullptr;
    }
}
