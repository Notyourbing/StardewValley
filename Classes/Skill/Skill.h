#pragma once
#include <string>
#include <functional>

class Skill {
public:
    // 构造函数
    Skill(const std::string& name, int maxLevel, std::function<void(int)> effect);

    // 获取技能名称
    const std::string& getName() const;

    // 获取技能最大等级
    int getMaxLevel() const;

    // 获取技能当前等级
    int getCurrentLevel() const;

    // 升级技能
    bool levelUp();

private:
    std::string name;                 // 技能名称
    int maxLevel;                     // 技能的最大等级
    int currentLevel = 0;             // 当前技能等级
    std::function<void(int)> effect;  // 技能效果，传入当前等级
};
