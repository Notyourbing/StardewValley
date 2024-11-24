#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include <string>
#include <map>

// 玩家类
class Player : public cocos2d::Sprite {
public:
	// 单例模式获取玩家实例
	static Player* getInstance();

	// 初始化玩家
	bool init();

	// 设置玩家移动的方向
	void moveByDirection(const cocos2d::Vec2& direction);

	// 设置名字
	void setPlayerName(const std::string& name);

	// 获取名字
	std::string getPlayerName() const;

	//停止移动
	void stopMoving();

private:
	// 玩家当前速度
	cocos2d::Vec2 velocity;

	// 玩家名字
	std::string name;

	// 单例实例
	static Player* instance;

	// 私有构造函数，防止多次实例化，确保唯一性
	Player();
	~Player();

	// 禁止拷贝和赋值
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	//动画
	std::map<std::string, cocos2d::Animate*> animations;
	std::string currentAnimationName;
	cocos2d::Vec2 lastDirection;

	void loadAnimations();
	void createWalkFrames(const std::string& baseFilename, const std::string& animationName, int frameCount);
	void createStandFrame(const std::string& filename, const std::string& animationName);
	void playAnimation(const std::string& animationName);
	void setStandPose(const std::string& standPoseName);
};

#endif