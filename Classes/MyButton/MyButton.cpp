#include "MyButton.h"

USING_NS_CC;

MyButton* MyButton::create(const std::string& normalImage, const std::string& hoverImage) {
	MyButton* button = new (std::nothrow) MyButton();
	if (button && button->init(normalImage, hoverImage)) {
		button->autorelease();
		return button;
	}
	CC_SAFE_DELETE(button);
	return nullptr;
}

bool MyButton::init(const std::string& normalImage, const std::string& hoverImage) {
	if (!Button::init(normalImage)) {
		return false;
	}
	hoverState = false;
	normal = normalImage;
	hover = hoverImage;

	mouseListener = EventListenerMouse::create();

	mouseListener->onMouseMove = CC_CALLBACK_1(MyButton::onMouseMove, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}

void MyButton::onMouseMove(Event* event) {
	const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
	const Vec2 mousePos = mouseEvent->getLocationInView();
	Rect buttonRect = this->getBoundingBox();

	// 判断鼠标是否在按钮范围内
	if (mouseEvent && buttonRect.containsPoint(this->getParent()->convertToNodeSpace(mousePos))) {
		this->loadTextureNormal(hover); // 鼠标悬浮时切换为hover图片
		hoverState = true;
	}
	else {
		this->loadTextureNormal(normal); // 鼠标离开时切换回normal图片
		hoverState = false;
	}
}

bool MyButton::isHover() {
	return hoverState;
}


