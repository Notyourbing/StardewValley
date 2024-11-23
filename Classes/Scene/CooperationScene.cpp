#include "CooperationScene.h"

USING_NS_CC;

// 打印有用的报错信息
static void problemLoading(const char* filename) {
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in WelcomeScene.cpp\n");
}

// 创建场景
Scene* Cooperation::createScene() {
	return Cooperation::create();
}

// 初始化
bool Cooperation::init() {
	if (!Scene::init()) {
		return false;
	}

	// 获取界面尺寸
	auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 创建一个简单的标签来显示合作信息
	auto label = Label::createWithTTF("Contact us!", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr) {
		problemLoading("Error loading font\n");
		return false;
	}
	else {
		const Vec2 position(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
		label->setPosition(position);
		this->addChild(label, 2);
	}

	// 返回项
	auto backItem = MenuItemImage::create(
		"icon/backButton.png",
		"icon/backButton.png",
		CC_CALLBACK_1(Cooperation::backCallBack, this));
	if (backItem == nullptr ||
		backItem->getContentSize().width <= 0 ||
		backItem->getContentSize().height <= 0) {
		problemLoading("backItem wrong");
	}
	else {
		// 靠近右下角的位置
		const float rightPadding = 40;
		const float bottomPadding = 20;
		const float x = origin.x + visibleSize.width - backItem->getContentSize().width / 2 - rightPadding;
		const float y = origin.y + bottomPadding + backItem->getContentSize().height / 2;
		backItem->setPosition(Vec2(x, y));
	}

	// 创建菜单容器
	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);
	return true;
}

void Cooperation::backCallBack(Ref* pSender) {
	Director::getInstance()->popScene();
}