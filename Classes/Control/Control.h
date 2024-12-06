#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "../Npc/Npc.h"
#include "../Scene/FarmScene.h"
#include "../DialogueBox/DialogueBox.h"
#include <set>

// 控制类， 控制人物的移动，地图的移动，人物和npc的交互
// 控制类不是单例的原因：可能会有多个场景，每一个场景一个控制类
class Control : public cocos2d::Node {
public:
	// 静态创建Control方法
	static Control* create();

	// 初始化
	bool init();

	// 根据按下的键来更新玩家和地图移动的方向；静态成员函数，可以全局访问
	static void updateMovement();

private:
	// 记录当前按下的键；静态成员变量，因为在updateMovement()中需要调用
	static std::set<cocos2d::EventKeyboard::KeyCode> keysPressed;

	// 初始化键盘监听器
	void initKeyboardListener();

	// 初始化鼠标监听器
	void initMouseListener();

	
};


#endif
