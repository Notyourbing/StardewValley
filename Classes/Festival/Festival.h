/****************************************************************
 * File Function: 节日类，继承CommunityEvent类并具体实现，作为游戏中节日庆典
 * Author:        韦瑾钰
 ****************************************************************/
#ifndef __FESTIVAL_H__
#define __FESTIVAL_H__

#include "../CommunityEvent/CommunityEvent.h"

class Festival : public CommunityEvent {
public:
    // 创建方法
    static Festival* create(const std::string& name, const std::string& description, const std::string& date, bool isHoliday);

    // 初始化方法
    bool init(const std::string& name, const std::string& description, const std::string& date, bool isHoliday);

    // 重写事件开始逻辑
    void startEvent() override;  

    // 判断当前是否为节假日
    bool isHoliday() const;

protected:
    bool holiday;  // 是否为节假日

    Festival() {}; // 构造函数
};

#endif
