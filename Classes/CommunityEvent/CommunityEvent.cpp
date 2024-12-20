/****************************************************************
 * File Function: 实现社区事件类，抽象基类，给出社区事件
 * Author:        韦瑾钰
 ****************************************************************/
#include "CommunityEvent.h"

// 初始化
bool CommunityEvent::init(const std::string& name, const std::string& description, const std::string& date) {
    // 初始化属性
    eventName = name;
    eventDescription = description;
    eventDate = date;
    return true;  // 如果初始化成功
}

// 开始事件
void CommunityEvent::startEvent() {

}

// 获取事件名称
std::string CommunityEvent::getEventName() const {
    return eventName;
}

// 获取事件描述
std::string CommunityEvent::getEventDescription() const {
    return eventDescription;
}

// 获取事件日期
std::string CommunityEvent::getEventDate() const {
    return eventDate;
}
