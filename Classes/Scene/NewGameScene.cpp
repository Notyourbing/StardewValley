#include "NewGameScene.h"
#include "../Player/Player.h"
#include "FarmScene.h"

USING_NS_CC;

// ��ӡ���õı�����Ϣ
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

	// ��ȡ��Ļ��С��ԭ��
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ��������
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

	// ���������򱳾�
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

	// ��������򱳾���
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

	// ���������ǩ
	const std::string fontPath = "fonts/Marker Felt.ttf";
	auto titleLabel = Label::createWithTTF("Please Enter Your Name (English or Number).", fontPath, 36);
	if (titleLabel == nullptr) {
		problemLoading(fontPath.c_str());
		return false;
	}
	titleLabel->setTextColor(Color4B::BLUE);
	titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 150));
	this->addChild(titleLabel, 3);

	// ���������
	nameInput = ui::TextField::create("Enter Here!", fontPath, 30);
	if (nameInput == nullptr) {
		problemLoading("nameInput create wrong");
		return false;
	}
	nameInput->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 80));
	nameInput->setMaxLength(10); // �������ֳ���
	nameInput->setMaxLengthEnabled(true);
	nameInput->setTextColor(Color4B::WHITE);
	this->addChild(nameInput, 3);

	// ����OK��ť
	const std::string okButtonPath = "icon/okButton.png";
	auto okButton = ui::Button::create(okButtonPath, okButtonPath);
	okButton->setPosition(Vec2(origin.x + visibleSize.width * 0.7, origin.y + visibleSize.height * 0.3));
	okButton->addClickEventListener(CC_CALLBACK_1(NewGame::onOKButtonClicked, this));
	this->addChild(okButton, 3);

	// ������
	const std::string backButtonPath = "icon/backButton.png";
	auto backItem = MenuItemImage::create(backButtonPath, backButtonPath, CC_CALLBACK_1(NewGame::backCallBack, this));
	if (backItem == nullptr ||
		backItem->getContentSize().width <= 0 ||
		backItem->getContentSize().height <= 0) {
		problemLoading("backItem wrong");
	}
	else {
		// �������½ǵ�λ��
		const float rightPadding = 40;
		const float bottomPadding = 20;
		const float x = origin.x + visibleSize.width - backItem->getContentSize().width / 2 - rightPadding;
		const float y = origin.y + bottomPadding + backItem->getContentSize().height / 2;
		backItem->setPosition(Vec2(x, y));
	}

	// �����˵�����
	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);

	return true;
}

void NewGame::onOKButtonClicked(Ref* pSender) {
	// ��ȡ���������
	std::string playerName = nameInput->getString();
	
	// �������Ϊ�գ�����ΪĬ������
	if (playerName.empty()) {
		playerName = "Kuanye";
	}

	// ���������õ�Player������
	Player::getInstance()->setPlayerName(playerName);

	// ����FramScene
	auto framScene = Farm::create();
	Director::getInstance()->replaceScene(framScene);
}

void NewGame::backCallBack(Ref* pSender) {
	Director::getInstance()->popScene();
}