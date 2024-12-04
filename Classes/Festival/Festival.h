#ifndef __FESTIVAL_H__
#define __FESTIVAL_H__

#include "../CommunityEvent/CommunityEvent.h"
//#include "../DateManage/DateManage.h"

class Festival : public CommunityEvent {
public:
    static Festival* create(const std::string& name, const std::string& description, const std::string& date, bool isHoliday);

    // 初始化方法
    bool init(const std::string& name, const std::string& description, const std::string& date, bool isHoliday);

    // ?? 重写为什么不加override, 父类为什么不是虚函数 // check 已更改
    void startEvent(DateManage* dateManager) override;  // 重写事件开始逻辑

    bool isHoliday() const;

protected:
    bool holiday;  // 是否为节假日

    Festival();
};

#endif
