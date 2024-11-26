#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include <string>
#include <map>
#include "../Tool/Tool.h"

USING_NS_CC;

// �����
class Player : public cocos2d::Sprite {
public:
	// ����ģʽ��ȡ���ʵ��
	static Player* getInstance();

	// ��ʼ�����
	bool init();

	// ��������
	void setPlayerName(const std::string& name);

	// ��ȡ����
	std::string getPlayerName() const;

	// ��������ƶ��ķ���
	void moveByDirection(const cocos2d::Vec2& direction);

	// ֹͣ�ƶ�
	void stopMoving();

	// ��ȡ���������
	cocos2d::Vec2 getLastDirection() const;

	// ���õ�ǰ����
	void setCurrentTool(Tool* tool);

	// ʹ�õ�ǰ����
	void useCurrentTool();


private:
	// ����ʵ��
	static Player* instance;

	// ��ҵ�ǰ�ٶ�
	cocos2d::Vec2 velocity;

	// �������
	std::string name;

	//	����
	std::map<std::string, Animate*> animations;
	std::string currentAnimationName;

	// ��ҵ����ĳ���
	Vec2 lastDirection;

	// ��ǰ����
	Tool* currentTool;

	// ˽�й��캯������ֹ���ʵ������ȷ��Ψһ��
	Player();
	~Player();

	// ��ֹ�����͸�ֵ
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	// ����վ��֡(ȫ��)
	void Player::loadStandFrames();

	// ָ�������վ��֡
	void createStandFrame(const std::string& filename, const std::string& animationName);

	// �����ƶ�֡����������
	void createWalkAnimation(const std::string& baseFilename, const std::string& animationName, int frameCount);

	// ����վ������
	void setStandPose(const std::string& standPoseName);
};

#endif