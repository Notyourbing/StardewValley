/****************************************************************
 * File Function: 实现篝火类，继承Item类，用于烹饪食物
 * Author:        韦瑾钰
 ****************************************************************/
#include "CampFire.h"
#include "cocos2d.h"
#include "../Food/Food.h" 
#include "../Bag/Bag.h"
#include "../Skill/SkillTree.h"
#include "../Player/Player.h"

USING_NS_CC;

CampFire* CampFire::instance = nullptr;
bool CampFire::status = false;

// 初始化篝火：设置篝火的名称和图片
bool CampFire::init(const ItemInfo& item_info) {
    itemName = item_info.name;
    itemImage = item_info.image;
    return Sprite::initWithFile(item_info.image);
}

// 获取单例
CampFire* CampFire::getInstance() {
    if (instance == nullptr) {
        instance = new (std::nothrow) CampFire();
        if (instance && instance->init(CAMPFIRE)) {
            instance->setPosition(cocos2d::Vec2(CAMPFIRE_X, CAMPFIRE_Y));
            instance->autorelease();
        }
        else {
            CC_SAFE_DELETE(instance);
        }
    }
    return instance;
}

// 创建方法
CampFire* CampFire::create(const ItemInfo& item_info) {
    CampFire* campFire = new (std::nothrow) CampFire();

    if (campFire && campFire->init(item_info)) {
        campFire->autorelease();
        return campFire;
    }
    else {
        CC_SAFE_DELETE(campFire);
        return nullptr;
    }
}

// 使用篝火（烤熟食物）
void CampFire::useItem() {
    // 如果靠近篝火，就进行食物烹饪
    auto skills = SkillTree::getInstance()->getAllSkills();
    int level = skills["Cooking"]->getCurrentLevel();
    float cookingTime = 6.0f / (level + 1);  // 根据烹饪等级调整烹饪时间，等级越高，时间越短

    Bag* bag = Bag::getInstance();
    auto item = bag->getSelectedItem();
    auto food = dynamic_cast<Food*>(item);
    if (food && food->getItemName().find("Cooked") == std::string::npos) {
        auto label = Label::createWithTTF("waiting..", ResPath::FONT_TTF, 24);
        label->setPosition(Player::getInstance()->getPosition() + Vec2(0, 100));  // 显示在玩家上方
        label->setTextColor(Color4B::WHITE);
        Player::getInstance()->getParent()->addChild(label);
        std::string cookedFood = item->getItemName();
        bag->removeItem(bag->getItemIndex(cookedFood));
        label->runAction(Sequence::create(
            FadeIn::create(0.5f),  // 淡入
            DelayTime::create(cookingTime),  // 显示
            FadeOut::create(0.5f),  // 淡出
            CallFunc::create([this, bag, cookedFood]() {
                // 动画完成后执行添加食物的操作
                std::string newName = cookedFood + "Cooked";
                std::string newImage = "tools/" + newName + ".png";
                auto newFood = Food::create({ newName.c_str(), newImage.c_str() });
                if (newFood) {
                    bag->addItem(newFood);
                }
                }),  // 添加食物到背包
            RemoveSelf::create(),
            nullptr
        ));
    }
}