#include "Festival.h"
#include "../Map/FarmMap.h"

// 静态工厂方法
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
void Festival::startEvent(DateManage* dateManage) {

    // 获取屏幕尺寸
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建文本并设置内容
    std::string message = "The festival " + eventName + " has started!";

    // 如果是节假日，修改消息内容
    if (holiday) {
        message = "It's a holiday! Enjoy your time off!";
    }
    else {
        message = "Join the community to celebrate the event!";
    }

    FarmMap* farmMap = FarmMap::getInstance();
    // 创建一个新的 Label 来显示消息
    auto label = cocos2d::Label::createWithTTF(message, "fonts/Marker Felt.ttf", 36);
    if (label) {
        // 设置位置为屏幕中央
        label->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        label->setTextColor(cocos2d::Color4B::WHITE);

        // 将 label 添加到场景中
        farmMap->addChild(label, 12);

        // 创建延迟 2 秒钟后移除文本的动作
        auto delay = cocos2d::DelayTime::create(2.0f);
        auto remove = cocos2d::CallFunc::create([label]() {
            label->removeFromParent();
            });

        // 组合动作并运行
        auto sequence = cocos2d::Sequence::create(delay, remove, nullptr);
        label->runAction(sequence);
    }
}

bool Festival::isHoliday() const {
    return holiday;
}

Festival::Festival()
{
}
