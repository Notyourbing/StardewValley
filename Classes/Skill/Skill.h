/****************************************************************
 * File Function: 技能类，作为PLayer拥有的属性
 * Author:        韦瑾钰
 ****************************************************************/
#ifndef __SKILL_H
#define __SKILL_H
#include <string>
#include <functional>

class Skill {
public:
    // 初始化函数
    bool init(const std::string& name, int maxLevel, std::function<void(int)> effect);

    // 创建技能
    static Skill* create(const std::string& name, int maxLevel, std::function<void(int)> effect);

    // 获取技能名称
    const std::string& getName() const;

    // 获取技能最大等级
    int getMaxLevel() const;

    // 获取技能当前等级
    int getCurrentLevel() const;

    // 设置技能等级
    bool setLevel(int level);

private:
    std::string name;                 // 技能名称
    int maxLevel;                     // 技能的最大等级
    int currentLevel;             // 当前技能等级
    std::function<void(int)> effect;  // 技能效果，传入当前等级
};

#endif __SKILL_H