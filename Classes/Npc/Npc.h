#ifndef NPC_H
#define NPC_H

#include "cocos2d.h"
#include <string>
#include <vector>
#include <map>
using namespace cocos2d;

enum class RelationshipStatus {
    None,       // 陌生
    Friendship, // 友谊
    Romance     // 浪漫
};

class Npc : public cocos2d::Node {
private:
    std::string name;                   // NPC的名字
    std::string birthday;               // NPC的生日
    int friendshipLevel;                // NPC与玩家的亲密度（0-100）
    std::vector<std::string> gifts;     // NPC喜欢的礼物
    std::vector<std::string> dislikes;  // NPC讨厌的礼物
    std::vector<std::string> dialogues; // NPC的对话列表
    std::string image;
    RelationshipStatus playerRelation;  // 与玩家的关系（None, Friendship, Romance）

    // 对话框相关成员
    Sprite* dialogueBox;                // 对话框背景
    Label* dialogueLabel;               // 对话框中的文本标签
    bool isDialogueVisible;             // 用于标记对话框是否显示

public:

    Sprite* sprite;                     // NPC的图像（作为精灵）
    // 构造函数
    Npc(const std::string& name, const std::string& birthdate,
        const std::vector<std::string>& favoriteGifts,
        const std::vector<std::string>& dislikedGifts,
        const std::vector<std::string>& dialogues,
        const std::string& imagePath);
    // 创建精灵的构造函数
    Npc(const Npc& other);
    Npc();

    // 获取NPC的名字
    std::string getNpcName() const;

    // 获取NPC的生日
    std::string getBirthday() const;

    // 获取NPC的亲密度
    int getFriendshipLevel() const;

    // 设置NPC的亲密度
    void setFriendshipLevel(int level);

    // 与NPC互动
    void interactWithPlayer();

    // 给NPC送礼物
    std::string giveGift(const std::string& gift);

    // 判断NPC是否喜欢某个礼物
    bool likesGift(const std::string& gift) const;

    // 判断NPC是否讨厌某个礼物
    bool dislikesGift(const std::string& gift) const;

    // 增加NPC的亲密度
    void increaseFriendship(int amount);

    // 减少NPC的亲密度
    void decreaseFriendship(int amount);

    // 获取NPC的所有喜欢的礼物
    std::vector<std::string> getGifts() const;

    // 获取NPC的所有讨厌的礼物
    std::vector<std::string> getDislikes() const;

    // 设置NPC的喜欢的礼物
    void setGifts(const std::vector<std::string>& giftList);

    // 设置NPC的讨厌的礼物
    void setDislikes(const std::vector<std::string>& dislikeList);

    // 获取NPC的对话
    std::string printDialogue() const;

    // 获取NPC与玩家的关系状态
    RelationshipStatus getPlayerRelation();

    // 设置与玩家的关系
    void setPlayerRelation(RelationshipStatus status);

    // 输出NPC的当前状态
    std::string printStatus() const;
};

#endif // NPC_H