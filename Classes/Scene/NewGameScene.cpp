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
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 创建背景
	const std::string backgroundPath = "icon/coopBackground.png";
	auto background = Sprite::create(backgroundPath);
	if (background == nullptr) {
		problemLoading(backgroundPath.c_str());
		return false;
	}
	else {
		background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(background, 0);
	}

	// 创建合作框背景
	const std::string coopPanelPath = "icon/cooperationPanel.png";
	auto coopPanel = Sprite::create(coopPanelPath);
	if (coopPanel == nullptr) {
		problemLoading(coopPanelPath.c_str());
		return false;
	}
	else {
		coopPanel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(coopPanel, 1);
	}

	// 创建输入框背景条
	const std::string nameBarPath = "icon/nameBar.png";
	auto nameBar = Sprite::create(nameBarPath);
	if (nameBar == nullptr) {
		problemLoading(nameBarPath.c_str());
		return false;
	}
	else {
		nameBar->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 80));
		this->addChild(nameBar, 2);
	}

	// 创建标题标签
	const std::string fontPath = "fonts/Marker Felt.ttf";
	auto titleLabel = Label::createWithTTF("Please Enter Your Name (English or Number).", fontPath, 36);
	if (titleLabel == nullptr) {
		problemLoading(fontPath.c_str());
		return false;
	}
	titleLabel->setTextColor(Color4B::BLUE);
	titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 150));
	this->addChild(titleLabel, 3);

	// 创建输入框
	nameInput = ui::TextField::create("Enter Here!", fontPath, 30);
	if (nameInput == nullptr) {
		problemLoading("nameInput create wrong");
		return false;
	}
	nameInput->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 80));
	nameInput->setMaxLength(10); // 限制名字长度
	nameInput->setMaxLengthEnabled(true);
	nameInput->setTextColor(Color4B::WHITE);
	this->addChild(nameInput, 3);

	// 创建OK按钮
	const std::string okButtonPath = "icon/okButton.png";
	auto okButton = ui::Button::create(okButtonPath, okButtonPath);
	okButton->setPosition(Vec2(origin.x + visibleSize.width * 0.7, origin.y + visibleSize.height * 0.3));
	okButton->addClickEventListener(CC_CALLBACK_1(NewGame::onOKButtonClicked, this));
	this->addChild(okButton, 3);

	// 返回项
	const std::string backButtonPath = "icon/backButton.png";
	auto backItem = MenuItemImage::create(backButtonPath, backButtonPath, CC_CALLBACK_1(NewGame::backCallBack, this));
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
	this->addChild(menu, 3);

	return true;
}

void NewGame::onOKButtonClicked(Ref* pSender) {
	// 获取输入的名字
	std::string playerName = nameInput->getString();
	
	// 如果名字为空，设置为默认名字
	if (playerName.empty()) {
		playerName = "Kuanye";
	}

	// 将名字设置到Player单例中
	Player::getInstance()->setPlayerName(playerName);

	// 进入FramScene
	auto framScene = Farm::create();
	Director::getInstance()->replaceScene(framScene);
}

void NewGame::backCallBack(Ref* pSender) {
	Director::getInstance()->popScene();
}