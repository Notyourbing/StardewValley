/****************************************************************
 * File Function: 实现节日类，继承CommunityEvent类并具体实现，作为游戏中节日庆典
 * Author:        韦瑾钰
 ****************************************************************/
#include "Festival.h"
#include "../Map/FarmMap.h"
#include "../Constant/Constant.h"

USING_NS_CC;

static std::vector<Festival*> festivals;  // 静态成员变量

// 静态方法
Festival* Festival::create(const std::string& name, const std::string& description, const std::string& date, bool isHoliday) {
    Festival* instance = new Festival();
    if (instance && instance->init(name, description, date, isHoliday)) {
        return instance;
    }
    delete instance;
    return nullptr;
}

// 初始化方法
bool Festival::init(const std::string& name, const std::string& description, const std::string& date, bool isHoliday) {
    // 调用父类的初始化
    if (!CommunityEvent::init(name, description, date)) {
        return false;
    }

    // 初始化节日特有的属性
    holiday = isHoliday;
    return true;
}

// 开始活动
void Festival::startEvent() {
    // 创建文本并设置内容
    std::string message = "The festival " + eventName + " has started!";

    // 如果是节假日，修改消息内容
    if (holiday) {
        message = "It's a holiday! Enjoy your time off in " + eventName + "!";
    }
    else {
        message = "Join the community to celebrate the " + eventName + "!";
    }

    FarmMap* farmMap = FarmMap::getInstance();
    // 创建一个新的 Label 来显示消息
    auto label = Label::createWithTTF(message, ResPath::FONT_TTF, 46);
    if (label) {
        // 设置位置为屏幕中央
        label->setPosition(Vec2(WINSIZE.width / 2 - farmMap->getPosition().x, WINSIZE.height / 2 - farmMap->getPosition().y));
        label->setTextColor(Color4B::WHITE);

        // 将 label 添加到场景中
        farmMap->addChild(label, 12);

        // 创建延迟 2 秒钟后移除文本的动作
        auto delay = DelayTime::create(2.0f);
        auto remove = CallFunc::create([label]() {
            label->removeFromParent();
            });

        // 组合动作并运行
        auto sequence = Sequence::create(delay, remove, nullptr);
        label->runAction(sequence);
    }
}

// 判断当前是否为节日
bool Festival::isHoliday() const {
    return holiday;
}