#include "CommunityEvent.h"

bool CommunityEvent::init(const std::string& name, const std::string& description, const std::string& date) {
    // 初始化属性
    eventName = name;
    eventDescription = description;
    eventDate = date;
    return true;  // 如果初始化成功
}

void CommunityEvent::startEvent(DateManage* dateManage) {
    // 事件开始时的逻辑，显示活动详情
    displayEventDetails();
}

void CommunityEvent::displayEventDetails() const {
    CCLOG("Event: %s\n", eventName);
    CCLOG("Description: %s\n", eventDescription);
    CCLOG("Date: %s\n", eventDate);
}

std::string CommunityEvent::getEventName() const {
    return eventName;
}

std::string CommunityEvent::getEventDescription() const {
    return eventDescription;
}

std::string CommunityEvent::getEventDate() const {
    return eventDate;
}
