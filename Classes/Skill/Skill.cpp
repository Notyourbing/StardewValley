#include "Skill.h"

bool Skill::init(const std::string& name, int maxLevel, std::function<void(int)> effect)
{
    this->name = name;
    this->maxLevel = maxLevel;
    this->effect = effect;
    this->currentLevel = 0;

    if (name.empty() || maxLevel <= 0) {
        return false; 
    }

    return true; // 初始化成功
}

Skill* Skill::create(const std::string& name, int maxLevel, std::function<void(int)> effect) {
    Skill* skill = new Skill();  // 创建新的 Skill 实例
    if (skill && skill->init(name, maxLevel, effect)) {  // 调用 init 方法进行初始化
        return skill;  // 初始化成功，返回实例
    }
    else {
        delete skill;  // 如果初始化失败，删除实例并返回 nullptr
        return nullptr;
    }
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

bool Skill::setLevel(int level)
{
    if (level >= 0 && level <= maxLevel) {
        currentLevel = level;
        return true;
    }
    else if (level > maxLevel) {
        currentLevel = maxLevel;
        return true;
    }
    return false;
}
