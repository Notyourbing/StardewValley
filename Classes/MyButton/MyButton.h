/****************************************************************
 * File Function: 实现自定义按钮类，实现悬浮按钮
 * Author:        赵卓冰
 ****************************************************************/
#ifndef __HOVERBUTTON_H__
#define __HOVERBUTTON_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>

class MyButton : public cocos2d::ui::Button {
public:
	static MyButton* create(const std::string& normalImage, const std::string& hoverImage);
	bool isHover();

private:
	bool init(const std::string& normalImage, const std::string& hoverImage);

	std::string normal; // 正常状态下按钮图片路径
	std::string hover;  // 鼠标悬浮状态下按钮图片路径

	cocos2d::EventListenerMouse* mouseListener;

	// 鼠标移动事件的处理函数
	void onMouseMove(cocos2d::Event* event);

	bool hoverState;
};

#endif
