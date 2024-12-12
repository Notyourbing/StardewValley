#ifndef __WEATHER_MANAGER_H__
#define __WEATHER_MANAGER_H__

#include "cocos2d.h"
#include "DateManage.h"

class WeatherManager : public cocos2d::Node {
public:
    static WeatherManager* create();

    // 每日更新天气
    void updateWeather(Weather weather);
    void removeWeatherEffect();

private:
    WeatherManager();
    ~WeatherManager();

    cocos2d::ParticleSystem* currentWeatherSystem;
    cocos2d::LayerColor* backgroundMask;
};


#endif 
