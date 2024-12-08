#ifndef __DATAMANAGE_H__
#define __DATAMANAGE_H__

#include "cocos2d.h"
#include "../Festival/Festival.h"

class DateManage : public cocos2d::Node{
public:
    // 用于显示日期的标签
    cocos2d::Label* dateLabel;
    // 存在的节日
    std::vector<Festival*> festivals;

    // 获取单例实例
    static DateManage* getInstance();

    // 获取当前日期
    std::string getCurrentDate() const;
    std::string getCurrentSeason() const;

    // 获取当前季的第几天
    int getCurrentDayInSeason() const;

    // 获取当前周的第几天
    int getCurrentDayInWeek() const;

    // 获取当前的年份
    int getCurrentYear() const;

    // 获取总累计天数
    int getDay() const;

    // 日期推进
    void advanceDay();

    // 判断是否是节日
    bool isFestivalDay() const;

    //开始节日
    void checkFestivalEvent();

    static DateManage* instance;  // 单例实例

    // 获取季节的索引
    int getSeasonIndex(const std::string& season);

    //时间增加
    void updateDate();
private:
    // 私有构造函数，防止外部直接创建对象
    DateManage();
    ~DateManage();

    // 初始化方法
    bool init(const int startYear, const int startDay);

    // 存储日期、年份等信息
    int currentDay;
    int currentYear;
};

#endif
