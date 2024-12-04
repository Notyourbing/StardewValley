#ifndef __DATAMANAGE_H__
#define __DATAMANAGE_H__

#include "cocos2d.h"
#include "../Festival/Festival.h"
#include "../Map/FarmMap.h"

class DateManage {
public:
    // 获取单例实例
    static DateManage* getInstance();

    // ?? 单例实例为什么会有create()方法，参考Player.h // check 已删除

    // 获取当前日期
    std::string getCurrentDate() const;
    std::string getCurrentSeason() const;
    int getCurrentDay() const;
    int getCurrentWeekday() const;
    int getCurrentYear() const;

    // 日期推进
    void advanceDay();

    // 判断是否是节日
    bool isFestivalDay() const;

    std::string getNextFestival();

    static DateManage* instance;  // 单例实例

    int getSeasonIndex(const std::string& season);

private:
    // 私有构造函数，防止外部直接创建对象
    DateManage();
    ~DateManage(); // 析构函数

    // 初始化方法
    bool init(int startYear, int startDay);

    // 存储日期、年份等信息
    int currentDay;
    int currentYear;

    static const int daysInSeason = 28;  // 每个季节的天数
    static const int daysInYear = 112;  // 每年的天数（4个季节，每季28天）
    static const int daysInWeek = 7;  // 一周7天
};

#endif
