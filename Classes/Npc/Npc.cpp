#include "Npc.h"
#include <iostream>
#include <map>

// 构造函数，初始化 NPC 的名字、生日、亲密度、喜欢的礼物、讨厌的礼物、对话
Npc::Npc(const std::string& name, const std::string& birthdate,
    const std::vector<std::string>& favoriteGifts,
    const std::vector<std::string>& dislikedGifts,
    const std::vector<std::string>& dialogues,
    const std::string& imagePath)
    : name(name), friendshipLevel(0), playerRelation(RelationshipStatus::None), dialogues(dialogues) {

    // 加载NPC的精灵图像
    sprite = Sprite::create(imagePath);  // 接收 std::string 类型的图像路径
}

Npc::Npc()
{
}

// 获取 NPC 的名字
std::string Npc::getNpcName() const {
    return name;
}

// 获取 NPC 的生日
std::string Npc::getBirthday() const {
    return birthday;
}

// 获取 NPC 的亲密度
int Npc::getFriendshipLevel() const {
    return friendshipLevel;
}

// 设置 NPC 的亲密度
void Npc::setFriendshipLevel(int level) {
    if (level < 0) {
        friendshipLevel = 0;
    }
    else if (level > 100) {
        friendshipLevel = 100;
    }
    else {
        friendshipLevel = level;
    }

    // 根据亲密度调整与玩家的关系
    if (friendshipLevel >= 80) {
        playerRelation = RelationshipStatus::Romance;
    }
    else if (friendshipLevel >= 50) {
        playerRelation = RelationshipStatus::Friendship;
    }
    else {
        playerRelation = RelationshipStatus::None;
    }
}

// 与 NPC 互动
void Npc::interactWithPlayer() {
    increaseFriendship(5);
    printDialogue();  // 互动后打印当前的对话
}

// 给 NPC 送礼物
void Npc::giveGift(const std::string& gift) {
    std::cout << "你送给 " << name << " " << gift << "。" << std::endl;

    if (likesGift(gift)) {
        std::cout << name << " 很喜欢这个礼物！" << std::endl;
        increaseFriendship(10);
    }
    else if (dislikesGift(gift)) {
        std::cout << name << " 并不喜欢这个礼物。" << std::endl;
        decreaseFriendship(5);
    }
    else {
        std::cout << name << " 对这个礼物没有特别的感觉。" << std::endl;
    }
}

// 判断 NPC 是否喜欢某个礼物
bool Npc::likesGift(const std::string& gift) const {
    return std::find(gifts.begin(), gifts.end(), gift) != gifts.end();
}

// 判断 NPC 是否讨厌某个礼物
bool Npc::dislikesGift(const std::string& gift) const {
    return std::find(dislikes.begin(), dislikes.end(), gift) != dislikes.end();
}

// 增加 NPC 的亲密度
void Npc::increaseFriendship(int amount) {
    friendshipLevel += amount;
    if (friendshipLevel > 100) {
        friendshipLevel = 100;
    }
}

// 减少 NPC 的亲密度
void Npc::decreaseFriendship(int amount) {
    friendshipLevel -= amount;
    if (friendshipLevel < 0) {
        friendshipLevel = 0;
    }
}

// 获取 NPC 的所有喜欢的礼物
std::vector<std::string> Npc::getGifts() const {
    return gifts;
}

// 获取 NPC 的所有讨厌的礼物
std::vector<std::string> Npc::getDislikes() const {
    return dislikes;
}

// 设置 NPC 的喜欢的礼物
void Npc::setGifts(const std::vector<std::string>& giftList) {
    gifts = giftList;
}

// 设置 NPC 的讨厌的礼物
void Npc::setDislikes(const std::vector<std::string>& dislikeList) {
    dislikes = dislikeList;
}

// 获取 NPC 的对话
std::string Npc::printDialogue() const {
    if (friendshipLevel >= 80) {
        return dialogues[2];
    }
    else if (friendshipLevel >= 50) {
        return dialogues[1];
    }
    else {
        return dialogues[0];
    }

    return "";
}

// 获取NPC与玩家的关系状态
RelationshipStatus Npc::getPlayerRelation() const {
    return playerRelation;
}

// 设置NPC与玩家的关系状态
void Npc::setPlayerRelation(RelationshipStatus status) {
    playerRelation = status;
}

// 输出 NPC 的当前状态
void Npc::printStatus() const {
    std::cout << "NPC: " << name << std::endl;
    std::cout << "生日: " << birthday << std::endl;
    std::cout << "亲密度: " << friendshipLevel << std::endl;
    std::cout << "与玩家的关系: " << (playerRelation == RelationshipStatus::Romance ? "浪漫" :
        playerRelation == RelationshipStatus::Friendship ? "友谊" : "陌生") << std::endl;
    std::cout << std::endl;
}