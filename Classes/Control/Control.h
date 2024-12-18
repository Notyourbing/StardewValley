#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "../Npc/Npc.h"
#include "../Scene/FarmScene.h"
#include "../DialogueBox/DialogueBox.h"
#include "../Map/SceneMap.h"
#include <set>

// 控制类， 控制人物的移动，地图的移动，人物和npc的交互
// 控制类不是单例的原因：有多个地图，每一个地图对应一个控制类
class Control : public cocos2d::Node {
public:
	// 静态创建Control方法
	static Control* create(SceneMap* sceneMap);

	// 初始化
	bool init(SceneMap* sceneMap);

	// 根据按下的键来更新玩家和地图移动的方向
	void updateMovement();

	// 构造函数和析构函数
	Control();
	~Control();
private:
	// 记录当前按下的键
	std::set<cocos2d::EventKeyboard::KeyCode> keysPressed;

	// 受控制的地图
	SceneMap* sceneMap;

	// 初始化键盘监听器
	void initKeyboardListener();

	// 初始化鼠标监听器
	void initMouseListener();
};
#endif
