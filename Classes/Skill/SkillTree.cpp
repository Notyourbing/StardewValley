#include "SkillTree.h"

USING_NS_CC;

// 定义静态实例指针
SkillTree* SkillTree::instance = nullptr;

// 获取单例实例
SkillTree* SkillTree::getInstance() {
    if (!instance) {
        instance = new (std::nothrow) SkillTree();
        if (instance && instance->init()) {
            instance->autorelease();
        }
        else {
            CC_SAFE_DELETE(instance);
        }
    }
    return instance;
}

// 初始化技能树
bool SkillTree::init() {
    addSkill("Mining", new Skill("Mining", 5, [](int level) {}));

    addSkill("Fishing", new Skill("Fishing", 5, [](int level) {}));

    addSkill("Agriculture", new Skill("Agriculture", 5, [](int level) {}));

    addSkill("Cooking", new Skill("Cooking", 5, [](int level) {}));

    // test 测试技能显示,后续无误后删掉
    SkillTree::getInstance()->levelUpSkill("Fishing");
    SkillTree::getInstance()->levelUpSkill("Fishing");
    SkillTree::getInstance()->levelUpSkill("Mining");
    SkillTree::getInstance()->levelUpSkill("Fishing");
    SkillTree::getInstance()->levelUpSkill("Agriculture");
    SkillTree::getInstance()->levelUpSkill("Agriculture");
    SkillTree::getInstance()->levelUpSkill("Agriculture");
    SkillTree::getInstance()->levelUpSkill("Agriculture");
    SkillTree::getInstance()->levelUpSkill("Agriculture");

    return true; // 返回初始化成功
}

// 添加技能
void SkillTree::addSkill(const std::string& name, Skill* skill) {
    skills[name] = skill;
}

// 升级技能
bool SkillTree::levelUpSkill(const std::string& name) {
    // 升级技能
    return skills[name]->levelUp();
}

// 获取技能
Skill* SkillTree::getSkill(const std::string& name) const {
    if (skills.count(name)) {
        return skills.at(name);
    }
    return nullptr;
}

const std::map<std::string, Skill*>& SkillTree::getAllSkills() const {
    return skills;
}

SkillTree::~SkillTree() {
    if (instance) {
        instance = nullptr;
    }
}