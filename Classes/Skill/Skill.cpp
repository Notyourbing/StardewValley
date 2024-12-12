#include "Skill.h"

// 构造函数
Skill::Skill(const std::string& name, int maxLevel, std::function<void(int)> effect)
    : name(name), maxLevel(maxLevel), effect(effect) {
}

// 获取技能名称
const std::string& Skill::getName() const {
    return name;
}

// 获取技能最大等级
int Skill::getMaxLevel() const {
    return maxLevel;
}

// 获取技能当前等级
int Skill::getCurrentLevel() const {
    return currentLevel;
}

// 升级技能
bool Skill::levelUp() {
    if (currentLevel < maxLevel) {
        ++currentLevel;
        if (effect) {
            effect(currentLevel); // 执行技能效果
        }
        return true;
    }
    return false;
}
