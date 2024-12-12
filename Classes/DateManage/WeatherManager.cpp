#include "WeatherManager.h"
#include "../Constant/Constant.h"

USING_NS_CC;


WeatherManager::WeatherManager()
    : currentWeatherSystem(nullptr), backgroundMask(nullptr) {
}

WeatherManager::~WeatherManager() {
    removeWeatherEffect();
}

WeatherManager* WeatherManager::create() {
    WeatherManager* weatherManger = new WeatherManager();
    if (weatherManger && weatherManger->init()) {
        weatherManger->autorelease();
        return weatherManger;
    }
    CC_SAFE_DELETE(weatherManger);
    return nullptr;
}

// 每日更新天气
void WeatherManager::updateWeather(Weather weather) {
    removeWeatherEffect();  // 移除现有的天气效果

    // 移除现有的天气粒子系统
    if (currentWeatherSystem) {
        removeChild(currentWeatherSystem);
        currentWeatherSystem = nullptr;
    }

    // 根据天气选择不同的粒子系统
    switch (weather) {
    case Weather::Sunny:
        // 晴天：可以使用光点效果或简单的晴天背景
        currentWeatherSystem = ParticleSun::create();
        currentWeatherSystem->setPosition(WINSIZE.width - SUN_OFFSET, WINSIZE.height - SUN_OFFSET); // 右上角
        currentWeatherSystem->setStartColor(Color4F(1.0f, 0.9f, 0.5f, 1.0f));	// 太阳的颜色
        currentWeatherSystem->setEndColor(Color4F(1.0f, 0.8f, 0.3f, 0.8f));		// 太阳渐变的颜色
        currentWeatherSystem->setSpeed(0);										// 无风
        currentWeatherSystem->setLife(0);										// 不需要生死周期，只是装饰效果

        // 删除背景遮罩
        if (backgroundMask) {
            removeChild(backgroundMask);
            backgroundMask = nullptr;
        }
        break;

    case Weather::LightRain:
        // 小雨：设置小雨的粒子系统
        currentWeatherSystem = ParticleRain::create();
        currentWeatherSystem->setPosition(WINSIZE.width / 2, WINSIZE.height);	// 屏幕中心
        currentWeatherSystem->setStartColor(Color4F(0.4f, 0.4f, 1.0f, 1.0f));	// 浅蓝色雨滴
        currentWeatherSystem->setEndColor(Color4F(0.2f, 0.2f, 0.8f, 0.8f));		// 雨滴渐变
        currentWeatherSystem->setSpeed(500);									// 雨滴速度
        currentWeatherSystem->setSpeedVar(50);									// 增加一些速度的随机性
        currentWeatherSystem->setStartSize(10.0f);								// 增加雨滴的大小
        currentWeatherSystem->setEndSize(5.0f);									// 渐小

        // 添加背景遮罩
        if (!backgroundMask) {
            backgroundMask = LayerColor::create(Color4B(0, 0, 0, 32));			// 半透明黑色
            addChild(backgroundMask, 99);									// 添加到场景，层级低于粒子效果
        }
        break;

    case Weather::HeavyRain:
        // 大雨：设置更大的速度和更多的雨滴

        currentWeatherSystem = ParticleRain::create();
        currentWeatherSystem->setPosition(WINSIZE.width / 2, WINSIZE.height);	// 屏幕中心
        currentWeatherSystem->setStartColor(Color4F(0.4f, 0.4f, 1.0f, 1.0f));	// 蓝色雨滴
        currentWeatherSystem->setEndColor(Color4F(0.2f, 0.2f, 0.8f, 0.8f));		// 渐变
        currentWeatherSystem->setTotalParticles(600);							// 增加粒子的数量，更多的雨滴
        currentWeatherSystem->setSpeed(800);									// 增加速度
        currentWeatherSystem->setSpeedVar(100);									// 增加速度的随机性
        currentWeatherSystem->setStartSize(15.0f);								// 更大的雨滴
        currentWeatherSystem->setEndSize(10.0f);								// 渐小
        // 添加背景遮罩
        if (!backgroundMask) {
            backgroundMask = LayerColor::create(Color4B(0, 0, 0, 64));			// 更深的半透明黑色
            addChild(backgroundMask, 99);									// 添加到场景，层级低于粒子效果
        }
        break;

    case Weather::Snowy:
        // 雪天：雪花的粒子系统
        currentWeatherSystem = ParticleSnow::create();
        currentWeatherSystem->setPosition(WINSIZE.width / 2, WINSIZE.height);	// 屏幕中心
        currentWeatherSystem->setStartColor(Color4F(1.0f, 1.0f, 1.0f, 1.0f));	// 白色雪花
        currentWeatherSystem->setEndColor(Color4F(0.8f, 0.8f, 0.8f, 0.8f));		// 渐变为透明
        currentWeatherSystem->setSpeed(100);									// 轻柔的雪花速度
        currentWeatherSystem->setSpeedVar(20);									// 稍微有点随机性
        currentWeatherSystem->setStartSize(10.0f);								// 中等大小雪花
        currentWeatherSystem->setEndSize(5.0f);									// 渐小
        break;
    }

    // 添加粒子系统到场景
    if (currentWeatherSystem) {
        addChild(currentWeatherSystem, 100);
    }
}

// 移除当前天气效果
void WeatherManager::removeWeatherEffect() {
    if (currentWeatherSystem) {
        removeChild(currentWeatherSystem);
        currentWeatherSystem = nullptr;
    }

    if (backgroundMask) {
        removeChild(backgroundMask);
        backgroundMask = nullptr;
    }
}