#include "Npc.h"
#include <iostream>
#include <algorithm>
#include <map>

// 构造函数，初始化 NPC 的名字、生日、亲密度、喜欢的礼物、讨厌的礼物、对话
Npc::Npc(std::string name, std::string birthday,
    std::vector<std::string> gifts,
    std::vector<std::string> dislikes,
    std::vector<std::string> dialogues)
    : name(name), birthday(birthday), friendshipLevel(0),
    gifts(gifts), dislikes(dislikes), dialogues(dialogues), playerRelation(RelationshipStatus::None) {
}

// 获取 NPC 的名字
std::string Npc::getName() const {
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
    std::cout << "你与 " << name << " 互动了！" << std::endl;
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
void Npc::printDialogue() const {
    std::cout << name << " 的对话：" << std::endl;

    if (friendshipLevel >= 80) {
        std::cout << "浪漫对话: " << dialogues[2] << std::endl;
    }
    else if (friendshipLevel >= 50) {
        std::cout << "友好对话: " << dialogues[1] << std::endl;
    }
    else {
        std::cout << "普通对话: " << dialogues[0] << std::endl;
    }
}

// 获取NPC与玩家的关系状态
RelationshipStatus Npc::getPlayerRelation() const {
    return playerRelation;
}

// 设置NPC与玩家的关系状态
void Npc::setPlayerRelation(RelationshipStatus status) {
    playerRelation = status;
}

// 设置NPC之间的关系
void Npc::setNpcRelation(const std::string& npcName, RelationshipStatus status) {
    npcRelations[npcName] = status;
}

// 获取NPC与另一NPC的关系
RelationshipStatus Npc::getNpcRelation(const std::string& npcName) const {
    auto it = npcRelations.find(npcName);
    if (it != npcRelations.end()) {
        return it->second;
    }
    return RelationshipStatus::None; // 默认没有关系
}

// 输出 NPC 的当前状态
void Npc::printStatus() const {
    std::cout << "NPC: " << name << std::endl;
    std::cout << "生日: " << birthday << std::endl;
    std::cout << "亲密度: " << friendshipLevel << std::endl;
    std::cout << "与玩家的关系: " << (playerRelation == RelationshipStatus::Romance ? "浪漫" :
        playerRelation == RelationshipStatus::Friendship ? "友谊" : "陌生") << std::endl;
    //std::cout << "喜欢的礼物: ";
    //for (const auto& gift : gifts) {
    //    std::cout << gift << " ";
    //}
    //std::cout << std::endl;
    //std::cout << "讨厌的礼物: ";
    //for (const auto& gift : dislikes) {
    //    std::cout << gift << " ";
    //}
    std::cout << std::endl;
}

// 询问NPC之间的关系
void Npc::askAboutNocRelation(const std::string& otherNpcName) const
{
    const RelationshipStatus otherRelation = getNpcRelation(otherNpcName);
    const RelationshipStatus playerRelation = getPlayerRelation();
    if (playerRelation == RelationshipStatus::None)
        return;

    if (otherRelation == RelationshipStatus::Romance) {
        std::cout << name << " 和 " << otherNpcName << " 关系很亲密！他们共享浪漫时刻。" << std::endl;
    }
    else if (otherRelation == RelationshipStatus::Friendship) {
        std::cout << name << " 和 " << otherNpcName << " 是朋友，他们的互动很愉快。" << std::endl;
    }
    else {
        std::cout << name << " 和 " << otherNpcName << " 关系陌生，他们互不干扰。" << std::endl;
    }
}
