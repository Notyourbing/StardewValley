#include "NewGameScene.h"
#include "../Player/Player.h"
#include "FarmScene.h"

USING_NS_CC;

// 打印有用的报错信息
static void problemLoading(const char* filename) {
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in WelcomeScene.cpp\n");
}

Scene* NewGame::createScene() {
	return NewGame::create();
}

bool NewGame::init() {
	if (!Scene::init()) {
		return false;
	}

	// 获取屏幕大小和原点
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto titleLabel = Label::createWithTTF("Enter Player Name", "fonts/Marker Felt.ttf", 36);
	titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 100));
	this->addChild(titleLabel, 1);

	// 创建输入框
	nameInput = ui::TextField::create("Enter Name", "fonts/Marker Felt.ttf", 30);
	nameInput->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 50));
	nameInput->setMaxLength(15); // 限制名字长度
	nameInput->setMaxLengthEnabled(true);
	nameInput->setTextColor(Color4B::WHITE);
	nameInput->setCursorEnabled(true); // 显示光标
	this->addChild(nameInput, 1);

	// 创建OK按钮
	auto okButton = ui::Button::create("icon/okButton.png", "icon/okButton.png");
	okButton->setPosition(Vec2(origin.x + visibleSize.width * 0.7, origin.y + visibleSize.height * 0.3));
	okButton->addClickEventListener(CC_CALLBACK_1(NewGame::onOKButtonClicked, this));
	this->addChild(okButton, 1);


	// 返回项
	auto backItem = MenuItemImage::create(
		"icon/backButton.png",
		"icon/backButton.png",
		CC_CALLBACK_1(NewGame::backCallBack, this));
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

void NewGame::onOKButtonClicked(Ref* pSender) {
	// 获取输入的名字
	std::string playerName = nameInput->getString();
	
	// 如果名字为空，设置为默认名字
	if (playerName.empty()) {
		playerName = "kuanye";
	}

	// 将名字设置到Player单例中
	Player::getInstance()->setName(playerName);

	// 进入FramScene
	auto framScene = Farm::create();
	Director::getInstance()->replaceScene(framScene);
}

void NewGame::backCallBack(Ref* pSender) {
	Director::getInstance()->popScene();
}