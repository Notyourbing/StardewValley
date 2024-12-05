#include "DateManage.h"
#include "../Constant/Constant.h"

DateManage* DateManage::instance = nullptr;  // 定义并初始化为 nullptr

// 私有构造函数，防止外部直接创建对象
DateManage::DateManage()  {}

DateManage::~DateManage() {
    if (instance != nullptr) {
        instance = nullptr;
    }
}

// 获取单例实例
DateManage* DateManage::getInstance() {
    if (instance == nullptr) {
        instance = new DateManage();  // 如果实例不存在，创建一个新的实例
        instance->init(1, 1);  // 默认初始化年份为1，日期为第 1 天
    }

    return instance;
}

// 初始化方法
bool DateManage::init(const int startYear, const int startDay) {
    currentYear = startYear;
    currentDay = startDay;

    return true;
}

std::string DateManage::getCurrentDate() const {
    int dayInSeason = (currentDay - 1) % DAYSINSEASON + 1; // 当前季节的第几天
    int seasonIndex = (currentDay - 1) / DAYSINSEASON % 4; // 季节索引

    std::stringstream dateStream;
    dateStream << SEASONNAME[seasonIndex] << " " << dayInSeason;

    return dateStream.str();
}

std::string DateManage::getCurrentSeason() const {
    int seasonIndex = ((currentDay - 1) / DAYSINSEASON) % 4;
    return SEASONNAME[seasonIndex];
}

int DateManage::getCurrentDayInSeason() const {
    return (currentDay - 1) % DAYSINSEASON + 1; // 当前季节的第几天
}

int DateManage::getCurrentDayInWeek() const {
    return (currentDay - 1) % DAYSINWEEK + 1; // 每周的哪一天
}

int DateManage::getDay() const{
    return currentDay;
}

void DateManage::advanceDay() {
    ++currentDay;
    if (currentDay > DAYSINYEAR) {
        currentDay = 1; // 新的一年
        ++currentYear;
    }
}

bool DateManage::isFestivalDay() const {
    // 节日出现在每个季节的特定日期
    int dayInSeason = getCurrentDayInSeason();
    if ((getCurrentSeason() == "Spring" && dayInSeason == 7) ||
        (getCurrentSeason() == "Summer" && dayInSeason == 15) ||
        (getCurrentSeason() == "Fall" && dayInSeason == 5) ||
        (getCurrentSeason() == "Winter" && dayInSeason == 25)) {
        return true;
    }
    return false;
}

/*std::string DateManage::getNextFestival()
{
    std::string res = "Today is " + getCurrentDate() + "!\n";
    if (isFestivalDay()) {
        int dayInSeason = getCurrentDay();
        if (getCurrentSeason() == "Spring" && dayInSeason == 7)
            res += "Celebrate the arrival of Spring with games, food, and fun!\n";
        else if (getCurrentSeason() == "Summer" && dayInSeason == 15)
            res += "The hot days of Summer are here! Time for the beach!\n";
        else if (getCurrentSeason() == "Fall" && dayInSeason == 5)
            res += "Let's picking up the falling leaves!\n";
        else if (getCurrentSeason() == "Winter" && dayInSeason == 25)
            res += "Merry Christmas and Happy Birthday to levi!\n";
    }
        
    //FarmMap* farmMap = FarmMap::getInstance();
    for (Festival* festival : farmMap->festivals) {
        std::string season, day, curSeason;
        std::istringstream stream(festival->getEventDate());
        stream >> season; // 读取季节
        stream >> day;    // 读取日期
        int date = std::stoi(day);

        std::istringstream streamCur(getCurrentDate());
        streamCur >> curSeason >> day;
        if (season == getCurrentSeason() && date > std::stoi(day))
            return festival->getEventName() + "is coming soon!";
        else if (season > getCurrentSeason())
            return festival->getEventName() + "is coming soon!";
    }
    return "waiting for next year..";
}*/

int DateManage::getSeasonIndex(const std::string& season) {
    auto it = SEASONINDEX.find(season);
        if (it != SEASONINDEX.end()) {
            return it->second;
        }
        else {
            return -1;
        }
}
int DateManage::getCurrentYear() const {
    return currentYear;
}
