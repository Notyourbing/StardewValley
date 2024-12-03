#include "ui/CocosGUI.h"
#include "FarmScene.h"
#include "../Map/FarmMap.h"
#include "../Npc/Npc.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "../Tool/PickAxe.h"
#include "../Tool/Axe.h"

USING_NS_CC;

Scene* Farm::createScene() {
	return Farm::create();
}

bool Farm::init() {
	if (!Scene::init()) {
		return false;
	}

	// 创建显示日期的标签
	dateLabel = Label::createWithTTF("", ResPath::FONT_TTF, 24);
	if (dateLabel) {
		dateLabel->setPosition(Vec2(WINSIZE.width - 100, WINSIZE.height - 40));  // 右上角位置
		this->addChild(dateLabel, 5);
	}

	// ??定时器
	// 启动一个定时器，每秒调用一次 updateDate 方法
	schedule([this](float deltaTime) {
		updateDate();
		}, 1.0f, "update_date_key");

	auto farmMap = FarmMap::getInstance();
	if (!farmMap->init("Maps/farmSpring11_28/farmMap.tmx")) {
		return false;
	}

	const auto farmMapSize = farmMap->getMapSize();
	farmMap->setPosition(WINSIZE.width / 2 -farmMapSize.width / 2, WINSIZE.height / 2 -farmMapSize.height / 2);
	this->addChild(farmMap, 0);

	// 创建 NPC 示例
	Npc* wizard = new Npc(WIZARD);
	Npc* cleaner = new Npc(CLEANER);
	cleaner->increaseFriendship(90); // 亲密度90
	npcs.push_back(cleaner);
	npcs.push_back(wizard);
	farmMap->npcInit(Vec2(WIZARD_X, WIZARD_Y), wizard);
	farmMap->npcInit(Vec2(CLEANER_X, CLEANER_Y), cleaner);
	isDialogueVisible = false;

	// 玩家
	auto player = Player::getInstance();
	player->setPosition(WINSIZE.width / 2, WINSIZE.height / 2); // 玩家初始位置在屏幕中央
	this->addChild(player, 3);

	// 玩家名字
	auto nameLabel = Label::createWithTTF(player->getPlayerName() + "'s farm", "fonts/Marker Felt.ttf", 24);
	if (nameLabel) {
		nameLabel->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height - 50));
		this->addChild(nameLabel, 4);
	}

	// 背包
	Bag* bag = Bag::getInstance();
	this->addChild(bag, 4);

	createFestivals();

	// 初始化键盘监听器
	initKeyboardListener();

	// 初始化鼠标监听器
	initMouseListener();

	return true;
}

void Farm::updateMovement() {
	Vec2 direction = Vec2::ZERO;

	// 检查按键集合，根据按下的键计算方向
	if (keysPressed.count(EventKeyboard::KeyCode::KEY_W)) { // 上
		direction.y = 1;
	} 
	else if (keysPressed.count(EventKeyboard::KeyCode::KEY_S)) { // 下
		direction.y = -1;
	}
	if (keysPressed.count(EventKeyboard::KeyCode::KEY_A)) { // 左
		direction.x = -1;
	}
	else if (keysPressed.count(EventKeyboard::KeyCode::KEY_D)) { // 右
		direction.x = 1;
	}

	// 归一化方向，避免斜方向移动速度过快
	if (direction != Vec2::ZERO) {
		direction.normalize();
	}

	// 更新玩家和地图的移动方向
	auto player = Player::getInstance();
	auto farmMap = FarmMap::getInstance();
	auto farmDirection = -direction;
	farmMap->moveMapByDirection(farmDirection);
	player->moveByDirection(direction);
}

// 显示初始对话框
void Farm::showInitialDialogue(Npc* npc) {
	// 标记对话框已显示
	isDialogueVisible = true;

	// 创建对话框背景
	auto dialogueBackground = Sprite::create("npcImages/dialogueBox.png");
	if (!dialogueBackground) {
		return;
	}

	// 创建并显示NPC的对话内容
	auto label = Label::createWithTTF(npc->printDialogue(), "fonts/Marker Felt.ttf", 44);
	dialogueBackground->setContentSize(Size(TALKING_BOX_WIDTH, TALKING_BOX_HEIGHT)); // 设置对话框大小
	dialogueBackground->setPosition(Vec2(TALKING_BOX_X, TALKING_BOX_Y));  // 设置对话框位置
	this->addChild(dialogueBackground, 10);

	// 设置文字框
	label->setDimensions(LABEL_WIDTH, LABEL_HEIGHT);
	label->setPosition(Vec2(dialogueBackground->getPositionX() - 240, dialogueBackground->getPositionY()));
	label->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
	label->setTextColor(Color4B::WHITE);
	this->addChild(label, 11);

	// NPC立绘
	std::string npcImageName = "npcImages/" + npc->getNpcName() + "Talk.png";
	auto npcTalkImage = Sprite::create(npcImageName);
	if (npcTalkImage) {
		npcTalkImage->setPosition(Vec2(dialogueBackground->getPositionX() + 365, dialogueBackground->getPositionY() + 40));
		this->addChild(npcTalkImage, 11);
	}

	// NPC名字
	auto nameLabel = Label::createWithTTF(npc->getNpcName(), ResPath::FONT_TTF, 40);
	nameLabel->setPosition(Vec2(dialogueBackground->getPositionX() + 360, dialogueBackground->getPositionY() - 140));
	nameLabel->setTextColor(Color4B::WHITE);
	this->addChild(nameLabel, 11);

	// 创建鼠标事件监听器
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = [=](Event* event) {
		auto mouseEvent = dynamic_cast<EventMouse*>(event);
		if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT && isDialogueVisible) {
			// 显示选项按钮
			showDialogueOptions(npc, dialogueBackground, label, npcTalkImage, nameLabel, listener);
		}
		};
	// 添加鼠标事件监听器到事件分发器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Farm::showDialogueOptions(Npc* npc, Sprite* dialogueBackground, Label* label, Sprite* npcTalkImage, Label* nameLabel, EventListenerMouse* lastListener) {
	_eventDispatcher->removeEventListener(lastListener);
	// 清除原始的对话文本
	label->setVisible(false);

	// 选项文本内容
	std::vector<std::string> options = { "Relationship between us", "Any tasks?", "Community Celebrations", "I have a gift for you" };
	const float optionY = dialogueBackground->getPositionY() + 120;  // 选项显示位置

	// 创建选项按钮
	for (int i = 0; i < options.size(); ++i) {
		auto optionButton = ui::Button::create();  // 创建按钮
		optionButton->setTitleText(options[i]);
		optionButton->setTitleFontSize(30);
		optionButton->setTitleColor(Color3B::WHITE);  // 设置文字颜色为白色
		optionButton->setPosition(Vec2(dialogueBackground->getPositionX() - 240, optionY - (i * 60)));  // 设置按钮位置

		// 为每个按钮添加点击事件
		optionButton->addClickEventListener([=](Ref* sender) {
			updateDialogueAfterOptionSelected(npc, optionButtons, i, dialogueBackground, label, npcTalkImage, nameLabel);
			});

		optionButtons.push_back(optionButton);
		this->addChild(optionButton, 12);  // 将按钮添加到场景中
	}
}

void Farm::updateDialogueAfterOptionSelected(Npc* npc, std::vector<ui::Button*> optionButtons, int optionIndex, Sprite* dialogueBackground, Label* label, Sprite* npcTalkImage, Label* nameLabel) {
	// 隐藏所有选项按钮
	for (auto button : optionButtons) {
		button->setTitleText("");
		button->setVisible(false);
	}
	std::string newDialogue;
	DateManage* dateManage = DateManage::getInstance();
	// 根据选择的选项更新对话框内容
	switch (optionIndex) {
		case 0:
			newDialogue = npc->printStatus();
			break;
		case 1:
			newDialogue = "Not yet";
			break;
		case 2:
			newDialogue = dateManage->getNextFestival();
			break;
		case 3:
			//选择礼物，给出gift
			newDialogue = npc->giveGift("Milk");
			npc->interactWithPlayer();
			break;
		default:
			break;
	}

	label->setString(newDialogue);
	label->setVisible(true);  // 显示新的对话内容

	// 重新创建鼠标事件监听器
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = [=](Event* event) {
		auto mouseEvent = dynamic_cast<EventMouse*>(event);
		if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
			closeDialogue(dialogueBackground, label, npcTalkImage, nameLabel, listener);
		};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Farm::closeDialogue(Sprite* dialogueBackground, Label* label, Sprite* npcTalkImage, Label* nameLabel, EventListenerMouse* lastListener) {
	_eventDispatcher->removeEventListener(lastListener);
	dialogueBackground->setVisible(false);
	label->setVisible(false);
	npcTalkImage->setVisible(false);
	nameLabel->setVisible(false);
	isDialogueVisible = false;
}

void Farm::initKeyboardListener() {
	// 创建键盘事件监听器
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode >= EventKeyboard::KeyCode::KEY_1 && keyCode <= EventKeyboard::KeyCode::KEY_9) {
			const int index = static_cast<int>(keyCode) - static_cast<int>(EventKeyboard::KeyCode::KEY_1);
			Bag::getInstance()->selectTool(index);
		}
		keysPressed.insert(keyCode);
		updateMovement(); // 根据当前按下的键计算方向
		};

	// 松开键时从 keysPressed 移除
	listener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
		keysPressed.erase(keyCode);
		// 停止玩家移动
		Player::getInstance()->stopMoving();
		updateMovement(); // 更新方向
		};

	// 添加监听器到事件分发器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Farm::initMouseListener()
{
	// 创建鼠标事件监听器
	auto listener = EventListenerMouse::create();

	listener->onMouseDown = [this](Event* event) {
		auto mouseEvent = dynamic_cast<EventMouse*>(event);
		Player* player = Player::getInstance();
		FarmMap* farmMap = FarmMap::getInstance();
		if (mouseEvent && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			if (isDialogueVisible == false) {
				Player::getInstance()->useCurrentTool();
				Vec2 playerPosition = player->getPosition();
				farmMap->interactWithFarmMap();
			}
		}
		else if (static_cast<EventMouse*>(event)->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
			for (auto npc : npcs) {
				// 计算玩家与NPC的距离
				Player* player = Player::getInstance();
				FarmMap* farmMap = FarmMap::getInstance();
				const float distance = player->getPosition().distance(npc->sprite->getPosition() + farmMap->getPosition());
				// 设定一个合适的距离阈值
				const float interactionRange = 100.0f;  // 可调整的阈值，表示玩家与 NPC 之间的最大交互距离
				if (distance < interactionRange && isDialogueVisible == false) {
					showInitialDialogue(npc);
				}
			}
		}
		};
	
	// 添加鼠标事件监听器到事件分发器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// 创建节日庆典事件
void Farm::createFestivals() {
	FarmMap* farmMap = FarmMap::getInstance();
	Festival* springFestival = Festival::create("Spring Festival", "Celebrate the arrival of Spring with games, food, and fun!", "Spring 7", true);
	if (springFestival) {
		farmMap->festivals.push_back(springFestival);
	}

	Festival* summerFestival = Festival::create("Summer Festival", "The hot days of Summer are here! Time for the beach!", "Summer 15", false);
	if (summerFestival) {
		farmMap->festivals.push_back(summerFestival);
	}

	Festival* fallFestival = Festival::create("Fall Festival", "Let's picking up the falling leaves!", "Fall 5", false);
	if (fallFestival) {
		farmMap->festivals.push_back(fallFestival);
	}

	Festival* winterFestival = Festival::create("Winter Festival", "Merry Christmas and Happy Birthday to levi!", "Winter 25", false);
	if (winterFestival) {
		farmMap->festivals.push_back(winterFestival);
	}
}

// 检查是否是节日，并触发节日活动
void Farm::checkFestivalEvent() {
	auto dateManager = DateManage::getInstance();
	std::string currentDate = dateManager->getCurrentDate();
	FarmMap* farmMap = FarmMap::getInstance();
	for (auto& festival : farmMap->festivals) {
		if (festival->getEventDate() == currentDate) {
			// 当前日期与节日日期匹配，开始节日活动
			festival->startEvent(dateManager);
			break;
		}
	}
}

void Farm::updateDate() {
	// 获取 DateManage 实例
	DateManage* dateManager = DateManage::getInstance();

	// 增加一天
	dateManager->advanceDay();

	// 获取当前的年份、季节和日期
	int year = dateManager->getCurrentYear();
	std::string season = dateManager->getCurrentSeason();
	int day = dateManager->getCurrentDay();

	// 更新日期字符串
	std::stringstream dateStream;
	dateStream << season << " " << day << " - Year " << year;

	// 更新 Label
	dateLabel->setString(dateStream.str());

	checkFestivalEvent();
}
