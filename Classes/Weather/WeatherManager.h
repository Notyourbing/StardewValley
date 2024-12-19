#ifndef __WEATHER_MANAGER_H__
#define __WEATHER_MANAGER_H__

#include "cocos2d.h"
#include "../Date/DateManage.h"

// WeatherManager类：管理天气
class WeatherManager : public cocos2d::Node {
public:
    // 静态创建WeatherManager类对象 
    static WeatherManager* create();

    // 每日更新天气
    void updateWeather(Weather weather);

    // 移除当前天气系统
    void removeWeatherEffect();
private:
    // 构造函数
    WeatherManager();

    // 析构函数
    ~WeatherManager();
    
    // 天气粒子系统
    cocos2d::ParticleSystem* currentWeatherSystem;

    // 背景遮罩
    cocos2d::LayerColor* backgroundMask;
};


#endif 
