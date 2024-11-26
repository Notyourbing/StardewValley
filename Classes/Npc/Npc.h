#ifndef NPC_H
#define NPC_H

#include "cocos2d.h"
#include <string>
#include <vector>
#include <map>
using namespace cocos2d;

enum class RelationshipStatus {
    None,       // İ��
    Friendship, // ����
    Romance     // ����
};

class Npc : public cocos2d::Node {
private:
    std::string name;                   // NPC������
    Sprite* sprite;                     // NPC��ͼ����Ϊ���飩
    std::string birthday;               // NPC������
    int friendshipLevel;                // NPC����ҵ����ܶȣ�0-100��
    std::vector<std::string> gifts;     // NPCϲ��������
    std::vector<std::string> dislikes;  // NPC���������
    std::vector<std::string> dialogues; // NPC�ĶԻ��б�
    RelationshipStatus playerRelation;  // ����ҵĹ�ϵ��None, Friendship, Romance��
    std::map<std::string, RelationshipStatus> npcRelations; // NPC֮��Ĺ�ϵ
    Vec2 position;

public:
    // ����ʵ��
    static Npc* instance;
    // ����ģʽ��Npcʵ��
    static Npc* getInstance();
    // ���캯��
    Npc(const std::string& name, const std::string& birthdate,
        const std::vector<std::string>& favoriteGifts,
        const std::vector<std::string>& dislikedGifts,
        const std::vector<std::string>& dialogues,
        const std::string& imagePath,
        const Vec2& initPosition);
    Npc();

    // ��ȡNPC������
    std::string getNpcName() const;

    // ��ȡNPC������
    std::string getBirthday() const;

    // ��ȡNPC�����ܶ�
    int getFriendshipLevel() const;

    // ����NPC�����ܶ�
    void setFriendshipLevel(int level);

    // ��NPC����
    void interactWithPlayer();

    // ��NPC������
    void giveGift(const std::string& gift);

    // �ж�NPC�Ƿ�ϲ��ĳ������
    bool likesGift(const std::string& gift) const;

    // �ж�NPC�Ƿ�����ĳ������
    bool dislikesGift(const std::string& gift) const;

    // ����NPC�����ܶ�
    void increaseFriendship(int amount);

    // ����NPC�����ܶ�
    void decreaseFriendship(int amount);

    // ��ȡNPC������ϲ��������
    std::vector<std::string> getGifts() const;

    // ��ȡNPC���������������
    std::vector<std::string> getDislikes() const;

    // ����NPC��ϲ��������
    void setGifts(const std::vector<std::string>& giftList);

    // ����NPC�����������
    void setDislikes(const std::vector<std::string>& dislikeList);

    // ��ȡNPC�ĶԻ�
    void printDialogue() const;

    // ��ȡNPC����ҵĹ�ϵ״̬
    RelationshipStatus getPlayerRelation() const;

    // ��������ҵĹ�ϵ
    void setPlayerRelation(RelationshipStatus status);

    // ����NPC֮��Ĺ�ϵ
    void setNpcRelation(const std::string& npcName, RelationshipStatus status);

    // ��ȡNPC����һNPC�Ĺ�ϵ
    RelationshipStatus getNpcRelation(const std::string& npcName) const;

    // ���NPC�ĵ�ǰ״̬
    void printStatus() const;

    // ѯ��NPC֮��Ĺ�ϵ
    void askAboutNocRelation(const std::string& otherNpcName) const;
};

#endif // NPC_H