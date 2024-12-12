#ifndef __WEATHER_H__
#define __WEATHER_H__

#include "cocos2d.h"
#include "../DateManage/DateManage.h"

// 前向声明 FarmScene 类
class Farm;

class WeatherManager : public cocos2d::Node {
public:
    static WeatherManager* create(Farm* farmScene);
    bool init(Farm* farmScene);

    // 设置当前天气
    void updateWeather(Weather weather);

private:
    Farm* farmScene; // FarmScene 引用
    cocos2d::ParticleSystemQuad* currentWeatherSystem; // 当前天气的粒子系统
    cocos2d::LayerColor* backgroundMask; // 背景遮罩
};

#endif 
