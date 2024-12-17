#pragma once
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

    // 升级技能
    bool levelUpSkill(const std::string& name);

    // 获取技能
    Skill* getSkill(const std::string& name) const;

    // 获取所有技能的方法
    const std::map<std::string, Skill*>& getAllSkills() const;

private:
    // 构造函数私有化，禁止外部直接创建
    SkillTree() = default;

    // 析构函数
    ~SkillTree();

    // 静态实例
    static SkillTree* instance;

    // 技能存储
    std::map<std::string, Skill*> skills;
};
