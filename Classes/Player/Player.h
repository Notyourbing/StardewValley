#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include <string>
#include <map>
#include "../Tool/Tool.h"

USING_NS_CC;

// 玩家类
class Player : public cocos2d::Sprite {
public:
	// 单例模式获取玩家实例
	static Player* getInstance();

	// 初始化玩家
	bool init();

	// 设置名字
	void setPlayerName(const std::string& name);

	// 获取名字
	std::string getPlayerName() const;

	// 设置玩家移动的方向
	void moveByDirection(const cocos2d::Vec2& direction);

	// 停止移动
	void stopMoving();

	// 获取人物最后朝向
	cocos2d::Vec2 getLastDirection() const;

	// 设置当前工具
	void setCurrentTool(Tool* tool);

	// 使用当前工具
	void useCurrentTool();

	// 获取人当前的速度
	cocos2d::Vec2 getVelocity() {
		return velocity;
	}


	// 设置站立动作
	void setStandPose(const std::string& standPoseName);
private:
	// 单例实例
	static Player* instance;

	// 玩家当前速度
	cocos2d::Vec2 velocity;

	// 玩家名字
	std::string name;

	//	动画
	std::map<std::string, Animate*> animations;
	std::string currentAnimationName;

	// 玩家的最后的朝向
	Vec2 lastDirection;

	// 当前工具
	Tool* currentTool;

	// 私有构造函数，防止多次实例化，确保唯一性
	Player();
	~Player();

	// 禁止拷贝和赋值
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	// 加载站立帧(全部)
	void Player::loadStandFrames();

	// 指定方向的站立帧
	void createStandFrame(const std::string& filename, const std::string& animationName);

	// 加载移动帧并创建动画
	void createWalkAnimation(const std::string& baseFilename, const std::string& animationName, int frameCount);
};

#endif