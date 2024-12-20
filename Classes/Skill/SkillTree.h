#ifndef __SKILLTREE_H__
#define __SKILLTREE_H__

#include "Skill.h"
#include <unordered_map>
#include <vector>
#include <string>
#include "cocos2d.h"

class SkillTree : public cocos2d::Node{
public:
    // 获取全局唯一实例
    static SkillTree* getInstance();

    // 初始化技能树
    bool init();

    // 添加技能
    void addSkill(const std::string& name, Skill* skill);

    // 设置技能等级
    bool setSkillLevel(const std::string& name, const int level);

    // 获取技能
    Skill* getSkill(const std::string& name) const;

    // 获取所有技能的方法
    const std::map<std::string, Skill*>& getAllSkills() const;

    //种植次数的get和update
    void updatePlantingCount(int count);
    int getPlantingCount() { return plantingCount; }

    //钓鱼次数的get和update
    void updateFishingCount(int count);
    int getFishingCount() { return fishingCount; }

    //采矿次数的get和update
    void updateMiningCount(int count);
    int getMiningCount() { return miningCount; }

    //烹饪次数的get和update
    void updateCookingCount(int count);
    int getCookingCount() { return cookingCount; }

private:
    // 构造函数私有化，禁止外部直接创建
    SkillTree() = default;

    // 析构函数
    ~SkillTree();

    // 静态实例
    static SkillTree* instance;

    // 技能存储
    std::map<std::string, Skill*> skills;

    // 种植次数，用于npc特殊任务
    static int plantingCount;

    // 钓鱼次数
    static int fishingCount;

    // 采矿次数
    static int miningCount;

    // 烹饪次数
    static int cookingCount;
};
#endif __SKILLTREE_H__