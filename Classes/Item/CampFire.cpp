/****************************************************************
 * File Function: ʵ�������࣬�̳�Item�࣬�������ʳ��
 * Author:        Τ���
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

// ��ʼ������������������ƺ�ͼƬ
bool CampFire::init(const ItemInfo& item_info) {
    itemName = item_info.name;
    itemImage = item_info.image;
    return Sprite::initWithFile(item_info.image);
}

// ��ȡ����
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

// ��������
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

// ʹ�����𣨿���ʳ�
void CampFire::useItem() {
    // ����������𣬾ͽ���ʳ�����
    auto skills = SkillTree::getInstance()->getAllSkills();
    int level = skills["Cooking"]->getCurrentLevel();
    float cookingTime = 6.0f / (level + 1);  // ������⿵ȼ��������ʱ�䣬�ȼ�Խ�ߣ�ʱ��Խ��

    Bag* bag = Bag::getInstance();
    auto item = bag->getSelectedItem();
    auto food = dynamic_cast<Food*>(item);
    if (food && food->getItemName().find("Cooked") == std::string::npos) {
        auto label = Label::createWithTTF("waiting..", ResPath::FONT_TTF, 24);
        label->setPosition(Player::getInstance()->getPosition() + Vec2(0, 100));  // ��ʾ������Ϸ�
        label->setTextColor(Color4B::WHITE);
        Player::getInstance()->getParent()->addChild(label);
        std::string cookedFood = item->getItemName();
        bag->removeItem(bag->getItemIndex(cookedFood));
        label->runAction(Sequence::create(
            FadeIn::create(0.5f),  // ����
            DelayTime::create(cookingTime),  // ��ʾ
            FadeOut::create(0.5f),  // ����
            CallFunc::create([this, bag, cookedFood]() {
                // ������ɺ�ִ�����ʳ��Ĳ���
                std::string newName = cookedFood + "Cooked";
                std::string newImage = "tools/" + newName + ".png";
                auto newFood = Food::create({ newName.c_str(), newImage.c_str() });
                if (newFood) {
                    bag->addItem(newFood);
                }
                }),  // ���ʳ�ﵽ����
            RemoveSelf::create(),
            nullptr
        ));
    }
}