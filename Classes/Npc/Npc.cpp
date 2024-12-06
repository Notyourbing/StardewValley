#include "Npc.h"
#include <iostream>

USING_NS_CC;

// 静态创建函数
Npc* Npc::create(const NpcInfo& npc_info) {
    Npc* npc = new (std::nothrow) Npc;
    if (npc && npc->init(npc_info)) {
        npc->autorelease();
        return npc;
    }
    CC_SAFE_DELETE(npc);
    return nullptr;
}

bool Npc::init(const NpcInfo& npc_info) {
    if (!Sprite::initWithFile(npc_info.image)) {
        return false;
    }
    name = npc_info.name;
    birthday = npc_info.birthdate;
    friendshipLevel = npc_info.friendshipLevel;
    gifts = npc_info.gifts;
    dislikes = npc_info.dislikes;
    dialogues = npc_info.dialogues;
    image = npc_info.image;

    return true;
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
}

// 与 NPC 互动
void Npc::interactWithPlayer() {
    increaseFriendship(5);
    printDialogue();  // 互动后打印当前的对话
}

// 给 NPC 送礼物
std::string Npc::giveGift(const std::string& gift) {
    std::string str = "you sent " + name + " " + gift + ".\n";

    if (likesGift(gift)) {
        str += name + " likes it very much.";
        increaseFriendship(10);
    }
    else if (dislikesGift(gift)) {
        str += name + " doesn't like it.";
        decreaseFriendship(10);
    }
    else {
        str += name + " said nothing about it.";
    }
    return str;
}

// 判断 NPC 是否喜欢某个礼物
bool Npc::likesGift(const std::string& gift) const {
    for (std::string item : gifts) {
        if (item == gift)
            return true;
    }
    return false;
}

// 判断 NPC 是否讨厌某个礼物
bool Npc::dislikesGift(const std::string& gift) const {
    for (std::string item : dislikes) {
        if (item == gift)
            return true;
    }
    return false;
}

// 增加 NPC 的亲密度
void Npc::increaseFriendship(const int amount) {
    friendshipLevel += amount;
    if (friendshipLevel > 100) {
        friendshipLevel = 100;
    }
}

// 减少 NPC 的亲密度
void Npc::decreaseFriendship(const int amount) {
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
RelationshipStatus Npc::getPlayerRelation() {
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
    return playerRelation;
}

// 设置NPC与玩家的关系状态
void Npc::setPlayerRelation(RelationshipStatus status) {
    playerRelation = status;
}

// 输出 NPC 的当前状态
std::string Npc::printStatus() const {
    std::string res = "friendshipLevel with " + name + ":  " + std::to_string(friendshipLevel);
    if (friendshipLevel >= 80)
        res += "\nRomance";
    else if (friendshipLevel >= 50)
        res += "\nFriend";
    else
        res += "\nNone";
    return res;
}