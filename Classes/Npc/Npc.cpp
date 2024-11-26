#include "Npc.h"
#include <iostream>
#include <algorithm>
#include <map>

// ��ʼ����̬��Ա����
Npc* Npc::instance = nullptr;

Npc* Npc::getInstance()
{
    if (instance == nullptr) {
        instance = new (std::nothrow) Npc();
        if (instance && instance->init()) {
            instance->autorelease();
        }
        else {
            CC_SAFE_DELETE(instance);
        }
    }
    return instance;
}

// ���캯������ʼ�� NPC �����֡����ա����ܶȡ�ϲ����������������Ի�
Npc::Npc(const std::string& name, const std::string& birthdate,
    const std::vector<std::string>& favoriteGifts,
    const std::vector<std::string>& dislikedGifts,
    const std::vector<std::string>& dialogues,
    const std::string& imagePath,
    const Vec2& initPosition)
    : name(name), friendshipLevel(0), playerRelation(RelationshipStatus::None),position(initPosition) {

    // ����NPC�ľ���ͼ��
    sprite = Sprite::create(imagePath);  // ���� std::string ���͵�ͼ��·��
    if (sprite) {
        sprite->setPosition(position);  // ����Ĭ��λ��
        this->addChild(sprite, 5);  // ���������Ϊ�ýڵ���ӽڵ�
    }
    else {
        CCLOG("error!no npc sprite found!\n");
    }
}

Npc::Npc()
{
}

// ��ȡ NPC ������
std::string Npc::getNpcName() const {
    return name;
}

// ��ȡ NPC ������
std::string Npc::getBirthday() const {
    return birthday;
}

// ��ȡ NPC �����ܶ�
int Npc::getFriendshipLevel() const {
    return friendshipLevel;
}

// ���� NPC �����ܶ�
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

    // �������ܶȵ�������ҵĹ�ϵ
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

// �� NPC ����
void Npc::interactWithPlayer() {
    std::cout << "���� " << name << " �����ˣ�" << std::endl;
    increaseFriendship(5);
    printDialogue();  // �������ӡ��ǰ�ĶԻ�
}

// �� NPC ������
void Npc::giveGift(const std::string& gift) {
    std::cout << "���͸� " << name << " " << gift << "��" << std::endl;

    if (likesGift(gift)) {
        std::cout << name << " ��ϲ��������" << std::endl;
        increaseFriendship(10);
    }
    else if (dislikesGift(gift)) {
        std::cout << name << " ����ϲ��������" << std::endl;
        decreaseFriendship(5);
    }
    else {
        std::cout << name << " ���������û���ر�ĸо���" << std::endl;
    }
}

// �ж� NPC �Ƿ�ϲ��ĳ������
bool Npc::likesGift(const std::string& gift) const {
    return std::find(gifts.begin(), gifts.end(), gift) != gifts.end();
}

// �ж� NPC �Ƿ�����ĳ������
bool Npc::dislikesGift(const std::string& gift) const {
    return std::find(dislikes.begin(), dislikes.end(), gift) != dislikes.end();
}

// ���� NPC �����ܶ�
void Npc::increaseFriendship(int amount) {
    friendshipLevel += amount;
    if (friendshipLevel > 100) {
        friendshipLevel = 100;
    }
}

// ���� NPC �����ܶ�
void Npc::decreaseFriendship(int amount) {
    friendshipLevel -= amount;
    if (friendshipLevel < 0) {
        friendshipLevel = 0;
    }
}

// ��ȡ NPC ������ϲ��������
std::vector<std::string> Npc::getGifts() const {
    return gifts;
}

// ��ȡ NPC ���������������
std::vector<std::string> Npc::getDislikes() const {
    return dislikes;
}

// ���� NPC ��ϲ��������
void Npc::setGifts(const std::vector<std::string>& giftList) {
    gifts = giftList;
}

// ���� NPC �����������
void Npc::setDislikes(const std::vector<std::string>& dislikeList) {
    dislikes = dislikeList;
}

// ��ȡ NPC �ĶԻ�
void Npc::printDialogue() const {
    std::cout << name << " �ĶԻ���" << std::endl;

    if (friendshipLevel >= 80) {
        std::cout << "�����Ի�: " << dialogues[2] << std::endl;
    }
    else if (friendshipLevel >= 50) {
        std::cout << "�ѺöԻ�: " << dialogues[1] << std::endl;
    }
    else {
        std::cout << "��ͨ�Ի�: " << dialogues[0] << std::endl;
    }
}

// ��ȡNPC����ҵĹ�ϵ״̬
RelationshipStatus Npc::getPlayerRelation() const {
    return playerRelation;
}

// ����NPC����ҵĹ�ϵ״̬
void Npc::setPlayerRelation(RelationshipStatus status) {
    playerRelation = status;
}

// ����NPC֮��Ĺ�ϵ
void Npc::setNpcRelation(const std::string& npcName, RelationshipStatus status) {
    npcRelations[npcName] = status;
}

// ��ȡNPC����һNPC�Ĺ�ϵ
RelationshipStatus Npc::getNpcRelation(const std::string& npcName) const {
    auto it = npcRelations.find(npcName);
    if (it != npcRelations.end()) {
        return it->second;
    }
    return RelationshipStatus::None; // Ĭ��û�й�ϵ
}

// ��� NPC �ĵ�ǰ״̬
void Npc::printStatus() const {
    std::cout << "NPC: " << name << std::endl;
    std::cout << "����: " << birthday << std::endl;
    std::cout << "���ܶ�: " << friendshipLevel << std::endl;
    std::cout << "����ҵĹ�ϵ: " << (playerRelation == RelationshipStatus::Romance ? "����" :
        playerRelation == RelationshipStatus::Friendship ? "����" : "İ��") << std::endl;
    //std::cout << "ϲ��������: ";
    //for (const auto& gift : gifts) {
    //    std::cout << gift << " ";
    //}
    //std::cout << std::endl;
    //std::cout << "���������: ";
    //for (const auto& gift : dislikes) {
    //    std::cout << gift << " ";
    //}
    std::cout << std::endl;
}

// ѯ��NPC֮��Ĺ�ϵ
void Npc::askAboutNocRelation(const std::string& otherNpcName) const
{
    const RelationshipStatus otherRelation = getNpcRelation(otherNpcName);
    const RelationshipStatus playerRelation = getPlayerRelation();
    if (playerRelation == RelationshipStatus::None)
        return;

    if (otherRelation == RelationshipStatus::Romance) {
        std::cout << name << " �� " << otherNpcName << " ��ϵ�����ܣ����ǹ�������ʱ�̡�" << std::endl;
    }
    else if (otherRelation == RelationshipStatus::Friendship) {
        std::cout << name << " �� " << otherNpcName << " �����ѣ����ǵĻ�������졣" << std::endl;
    }
    else {
        std::cout << name << " �� " << otherNpcName << " ��ϵİ�������ǻ������š�" << std::endl;
    }
}
