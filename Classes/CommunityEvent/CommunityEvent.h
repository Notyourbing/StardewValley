#ifndef __COMMUNITY_EVENT_H__
#define __COMMUNITY_EVENT_H__

#include <string>
#include "cocos2d.h"

class DateManage; // 前向声明 DateManage 类

class CommunityEvent {
public:

    virtual ~CommunityEvent() = default;

    // 公有方法：启动事件
    virtual void startEvent(DateManage* dateManage) = 0;

    // 公有方法：显示活动详情
    void displayEventDetails() const;

    // 获取事件名称
    std::string getEventName() const;

    // 获取事件描述
    std::string getEventDescription() const;

    // 获取事件日期
    std::string getEventDate() const;

protected:

    // 私有构造函数，防止外部直接创建对象
    CommunityEvent() = default;

    // 私有初始化方法
    bool init(const std::string& name, const std::string& description, const std::string& date);

    // 事件的成员变量
    std::string eventName;
    std::string eventDescription;
    std::string eventDate;
};

#endif // __COMMUNITY_EVENT_H__
