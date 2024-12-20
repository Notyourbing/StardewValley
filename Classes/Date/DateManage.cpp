/****************************************************************
 * File Function: 实现日期管理类，用于显示并管理游戏中日期的记载与更迭
 * Author:        韦瑾钰 赵卓冰 高鑫
 ****************************************************************/
#include "DateManage.h"
#include "../Constant/Constant.h"
#include "../Player/Player.h"
#include "cocos2d.h"
DateManage* DateManage::instance = nullptr;  // 定义并初始化为 nullptr

// 私有构造函数，防止外部直接创建对象
DateManage::DateManage()  {}

// 析构函数
DateManage::~DateManage() {
    if (instance != nullptr) {
        instance = nullptr;
    }
}

// 获取单例实例
DateManage* DateManage::getInstance() {
    if (instance == nullptr) {
        instance = new (std::nothrow) DateManage();
        if (instance && instance->init(1, 1)) {
            instance->autorelease();
        }
        else {
            CC_SAFE_DELETE(instance);
        }
    }
    return instance;
}

// 初始化方法
bool DateManage::init(const int startYear, const int startDay) {
    //创建节日信息
    Festival* springFestival = Festival::create("Spring Festival", "Celebrate the arrival of Spring with games, food, and fun!", "Spring 7", true);
    if (springFestival) {
        festivals.push_back(springFestival);
    }

    Festival* summerFestival = Festival::create("Summer Festival", "The hot days of Summer are here! Time for the beach!", "Summer 15", false);
    if (summerFestival) {
        festivals.push_back(summerFestival);
    }

    Festival* fallFestival = Festival::create("Fall Festival", "Let's picking up the falling leaves!", "Fall 5", false);
    if (fallFestival) {
        festivals.push_back(fallFestival);
    }

    Festival* winterFestival = Festival::create("Winter Festival", "Merry Christmas and Happy Birthday to levi!", "Winter 25", false);
    if (winterFestival) {
        festivals.push_back(winterFestival);

    }
    currentYear = startYear;
    currentDay = startDay;

    // 日期标签
    dateLabel = cocos2d::Label::createWithTTF("", ResPath::FONT_TTF, 24);
    addChild(dateLabel);
    dateLabel->setPosition(cocos2d::Vec2(WINSIZE.width - 100, WINSIZE.height - 40));  // 右上角位置
    
    // 钱标签
    moneyLabel = cocos2d::Label::createWithTTF("", ResPath::FONT_TTF, 24);
    moneyLabel->setColor(Color3B::YELLOW);
    addChild(moneyLabel);
    moneyLabel->setPosition(cocos2d::Vec2(WINSIZE.width - 100, WINSIZE.height - 80));  // 右上角位置
    
    // 初始化天气为晴天
    currentWeater = Weather::Sunny;

    return true;
}

// 获取当前日期
std::string DateManage::getCurrentDate() const {
    int dayInSeason = (currentDay - 1) % DAYSINSEASON + 1; // 当前季节的第几天
    int seasonIndex = (currentDay - 1) / DAYSINSEASON % 4; // 季节索引

    std::stringstream dateStream;
    dateStream << SEASONNAME[seasonIndex] << " " << dayInSeason;

    return dateStream.str();
}

// 获取当前季节
std::string DateManage::getCurrentSeason() const {
    int seasonIndex = ((currentDay - 1) / DAYSINSEASON) % 4;
    return SEASONNAME[seasonIndex];
}

// 获取当前日期在当前季节中是第几天
int DateManage::getCurrentDayInSeason() const {
    return (currentDay - 1) % DAYSINSEASON + 1; // 当前季节的第几天
}

// 获取当前日期在星期中是第几天
int DateManage::getCurrentDayInWeek() const {
    return (currentDay - 1) % DAYSINWEEK + 1; // 每周的哪一天
}

// 获取当前天数
int DateManage::getDay() const{
    return currentDay;
}

// 当前日期增加一天
void DateManage::advanceDay() {
    ++currentDay;
    if (currentDay > DAYSINYEAR) {
        currentDay = 1; // 新的一年
        ++currentYear;
    }
}

// 判断当前是否为特殊节日
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

// 获取季节序号
int DateManage::getSeasonIndex(const std::string& season) {
    auto it = SEASONINDEX.find(season);
        if (it != SEASONINDEX.end()) {
            return it->second;
        }
        else {
            return -1;
        }
}

// 获取当前年份
int DateManage::getCurrentYear() const {
    return currentYear;
}

// 检查是否是节日，并触发节日活动
void DateManage::checkFestivalEvent() {
    auto dateManager = DateManage::getInstance();
    const std::string currentDate = dateManager->getCurrentDate();
    for (auto& festival : festivals) {
        if (festival->getEventDate() == currentDate) {
            // 当前日期与节日日期匹配，开始节日活动
            festival->startEvent();
            break;
        }
    }
}

// 增加日期
void DateManage::updateDate() {
    // 获取 DateManage 实例
    DateManage* dateManager = DateManage::getInstance();

    // 增加一天
    dateManager->advanceDay();

    // 获取当前的年份、季节和日期
    int year = dateManager->getCurrentYear();
    std::string season = dateManager->getCurrentSeason();
    int day = dateManager->getCurrentDayInSeason();

    // 更新日期字符串
    std::stringstream dateStream;
    dateStream << season << " " << day << " - Year " << year;

    // 更新Label
    dateLabel->setString(dateStream.str());

    // 更新money字符串
    Player* player = Player::getInstance();
    std::stringstream moneyStream;
    int money = player->getMoney();
    moneyStream << "Current Money: "<<money;
    moneyLabel->setString(moneyStream.str());

    checkFestivalEvent();

    // 更新天气
    updateCurrentWeather();
}

// 获取当前的天气
Weather DateManage::getCurrentWeather() const{
    return currentWeater;
}

// 更新每天的天气
void DateManage::updateCurrentWeather() {
    // 获取当前的天气
    std::string currentSeason = getCurrentSeason();

    // 每个天气发生的概率
    float sunnyProb = 0.6f;
    float lightRainProb = 0.2f;
    float heavyRainProb = (currentSeason == "Winter") ? 0.1f : 0.2f;

    // 生成随机数
    float randomValue = static_cast<float>(rand()) / RAND_MAX;

    // 根据随机数判断天气
    if (randomValue < sunnyProb) {
        currentWeater = Weather::Sunny;
    }
    else if (randomValue < sunnyProb + lightRainProb) {
        currentWeater = Weather::LightRain;
    }
    else if (randomValue < sunnyProb + lightRainProb + heavyRainProb) {
        currentWeater = Weather::HeavyRain;
    }
    else {
        currentWeater = Weather::Snowy;
    }
}