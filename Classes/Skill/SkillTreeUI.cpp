#include "SkillTreeUI.h"
#include "SkillTree.h"
#include "../Constant/Constant.h"
#include "../Player/Player.h"
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

bool SkillTreeUI::init() {
    isOpen = false;
    if (!Layer::init()) {
        return false;
    }
    setupUI();
    return true;
}

void SkillTreeUI::setupUI() {
    // 获取屏幕尺寸
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 获取技能树实例
    auto skillTree = SkillTree::getInstance();

    // 设置背景图片
    auto bg = Sprite::create(ResPath::COOP_PANEL);
    float bgWidth = visibleSize.width / 2;  // 背景宽度占屏幕的一半
    float bgHeight = visibleSize.height / 2; // 背景高度占屏幕的一半
    bg->setScaleX(bgWidth / bg->getContentSize().width);  // 按比例缩放宽度
    bg->setScaleY(bgHeight / bg->getContentSize().height); // 按比例缩放高度
    bg->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y); // 背景放置在屏幕中心
    addChild(bg);

    // 设置内容的偏移量，确保从背景顶部开始
    int yOffset = bg->getPositionY() + bgHeight / 2 - 50; // 从背景顶部开始的偏移量

    // 遍历技能树，创建UI元素
    for (const auto& skillPair : skillTree->getAllSkills()) {
        const std::string& skillName = skillPair.first;
        Skill* skill = skillPair.second;

        // 技能名称标签
        auto skillLabel = Label::createWithTTF(skillName, ResPath::FONT_TTF, 24);
        skillLabel->setAnchorPoint(Vec2(0, 0.5)); // 左对齐
        skillLabel->setPosition(bg->getPositionX() - bgWidth / 2 + 50, yOffset); // 相对于背景位置
        addChild(skillLabel);

        // 计算技能的进度
        int currentLevel = skill->getCurrentLevel();
        int maxLevel = skill->getMaxLevel();

        // 获取每个级别所占宽度
        float levelWidth = bgWidth / 2 / maxLevel;

        // 横向显示每个级别
        for (int i = 0; i < currentLevel; ++i) {
            auto levelBlock = Sprite::create(ResPath::SKILL_BACKGROUND); // 背景块图片
            levelBlock->setAnchorPoint(Vec2(-5, 0.5));
            levelBlock->setPosition(bg->getPositionX() - bgWidth / 2 + (i * levelWidth), yOffset); // 水平排列
            addChild(levelBlock);

        }

        // 技能等级标签
        std::string levelText = StringUtils::format("Lv %d/%d", skill->getCurrentLevel(), skill->getMaxLevel());
        auto levelLabel = Label::createWithTTF(levelText, ResPath::FONT_TTF, 20);
        levelLabel->setPosition(bg->getPositionX() + bgWidth / 3, yOffset); // 技能等级标签居中
        addChild(levelLabel);

        yOffset -= 80; // 每行之间间隔80
        setVisible(false);
    }

    // 关闭按钮：放置在背景的右上角
    auto closeButton = MenuItemImage::create(ResPath::SKILL_CLOSE, ResPath::SKILL_CLOSE_ON,
        CC_CALLBACK_1(SkillTreeUI::closeCallback, this));
    closeButton->setPosition(bg->getPositionX() + bgWidth / 2 - 25, bg->getPositionY() + bgHeight / 2 - 25); // 调整关闭按钮位置
    auto menu = Menu::create(closeButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    addChild(menu);
}


void SkillTreeUI::closeCallback(cocos2d::Ref* sender) {
    Player::getInstance()->stopAllActions();
    Player::getInstance()->stopMoving();
    setVisible(false);
    isOpen = false;
}
