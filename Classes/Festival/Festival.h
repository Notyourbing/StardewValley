#ifndef __FESTIVAL_H__
#define __FESTIVAL_H__

#include "../CommunityEvent/CommunityEvent.h"

class Festival : public CommunityEvent {
public:
    static Festival* create(const std::string& name, const std::string& description, const std::string& date, bool isHoliday);

    // 初始化方法
    bool init(const std::string& name, const std::string& description, const std::string& date, bool isHoliday);

    // 重写事件开始逻辑
    void startEvent() override;  

    bool isHoliday() const;

protected:
    bool holiday;  // 是否为节假日

    Festival();
};

#endif
