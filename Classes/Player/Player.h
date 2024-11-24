#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include <string>

class Player : public cocos2d::Sprite {
public:
	// 单例模式获取玩家实例
	static Player* getInstance();

	// 初始化玩家
	virtual bool init();

	// 设置玩家移动的方向
	void moveByDirection(const cocos2d::Vec2& direction);

	// 停止玩家移动
	void stopMoving();

	// 设置名字
	void setPlayerName(const std::string& name);

	// 获取名字
	std::string getPlayerName() const;

private:
	// 私有构造函数
	Player();
	virtual ~Player();

	// 禁止拷贝和赋值
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	// 玩家当前速度
	cocos2d::Vec2 velocity;

	// 玩家名字
	std::string name;

	// 单例实例
	static Player* instance;
};

#endif