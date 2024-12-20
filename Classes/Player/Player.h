/****************************************************************
 * File Function: 实现游戏中的玩家类，通过wasd控制玩家鼠标控制玩家
 *                和地图交互
 * Author:        赵卓冰 高鑫
 ****************************************************************/
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

	// 设置人物最后朝向
	void setLastDirection(const cocos2d::Vec2& direction);

	// 设置当前物品
	void setCurrentItem(Item* item);

	// 使用当前物品
	void useCurrentItem();

	// 获取人当前的速度
	cocos2d::Vec2 getVelocity() {
		return velocity;
	}

	// 获得当前物品名称
	std::string getCurrentItemName() const;

	// 设置站立动作
	void setStandPose(const std::string& standPoseName);

	// 设置能否使用当前物品
	void setUseItemEnable(const bool enable);

	// 获取能否使用当前物品
	bool getUseItemEnable();

	// 增加金币
	void addMoney(int money);

	// 获取当前金币数量
	int getMoney() const;

	//声望相关get和set
	int getPopularity() const { return popularity; }
	bool setPopularity(int value) { return popularity = value; }

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
	
	// 当前物品
	Item* currentItem;

	// 能否使用物品
	bool useItemEnable;

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

	// 声望
	int popularity;

	// 金币数
	int playerMoney;
};

#endif