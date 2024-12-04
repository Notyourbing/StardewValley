#include "DateManage.h"

// 私有构造函数，防止外部直接创建对象
DateManage::DateManage() : currentYear(0), currentDay(0) {
    // 初始化
}

DateManage* DateManage::instance = nullptr;  // 定义并初始化为 nullptr

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
bool DateManage::init(int startYear, int startDay) {
    currentYear = startYear;
    currentDay = startDay;
    return true;
}

std::string DateManage::getCurrentDate() const {
    int dayOfYear = currentDay % daysInYear;
    int dayInSeason = dayOfYear % daysInSeason + 1; // 当前季节的第几天
    int seasonIndex = dayOfYear / daysInSeason;
    std::string seasonNames[] = { "Spring", "Summer", "Fall", "Winter" };

    std::stringstream dateStream;
    dateStream << seasonNames[seasonIndex] << " " << dayInSeason;

    return dateStream.str();
}

std::string DateManage::getCurrentSeason() const {
    int seasonIndex = (currentDay / daysInSeason) % 4;
    std::string seasonNames[] = { "Spring", "Summer", "Fall", "Winter" };
    return seasonNames[seasonIndex];
}

int DateManage::getCurrentDay() const {
    return currentDay % daysInSeason + 1; // 当前季节的第几天
}

int DateManage::getCurrentWeekday() const {
    return currentDay % daysInWeek; // 每周的哪一天
}

int DateManage::getDay() const{
    return currentDay;
}

void DateManage::advanceDay() {
    currentDay++;
    if (currentDay >= daysInYear) {
        currentDay = 0; // 新的一年
        currentYear++;
    }
}

bool DateManage::isFestivalDay() const {
    // 节日出现在每个季节的特定日期
    int dayInSeason = getCurrentDay();
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
    // 映射季节字符串到整数
    static std::map<std::string, int> seasonMap = {
        {"Spring", 0},
        {"Summer", 1},
        {"Fall", 2},
        {"Winter", 3}
    };

    // 查找并返回季节的索引
    auto it = seasonMap.find(season);
    if (it != seasonMap.end()) {
        return it->second;
    }
    return -1; // 如果季节无效，返回 -1
}
int DateManage::getCurrentYear() const {
    return currentYear;
}
