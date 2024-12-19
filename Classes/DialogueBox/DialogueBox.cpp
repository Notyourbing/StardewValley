#include "DialogueBox.h"
#include "../DateManage/DateManage.h"
#include "../Skill/SkillTree.h"
#include "../Item/StoneItem.h"
#include "../Npc/NoticeBoard.h"
#include "../Map/BeachMap.h"

USING_NS_CC;

bool DialogueBox::isDialogueVisible = false;

DialogueBox* DialogueBox::create(Npc* npc) {
    DialogueBox* ret = new DialogueBox();
    if (ret && ret->init(npc)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

DialogueBox* DialogueBox::create()
{
    DialogueBox* ret = new DialogueBox();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool DialogueBox::init(Npc* npc) {
    if (!Node::init()) {
        return false;
    }

    this->npc = npc;
    // 创建对话框背景
    dialogueBackground = Sprite::create(DIALOGUE_BACKGROUND);
    if (!dialogueBackground) {
        return false;
    }
    dialogueBackground->setContentSize(Size(TALKING_BOX_WIDTH, TALKING_BOX_HEIGHT)); // 设置对话框大小
    dialogueBackground->setPosition(Vec2(TALKING_BOX_X, TALKING_BOX_Y));  // 设置对话框位置

    // 创建并显示NPC的对话内容
    dialogueLabel = Label::createWithTTF(npc->printDialogue(), ResPath::FONT_TTF, 44);
    // 设置文字框
    dialogueLabel->setDimensions(LABEL_WIDTH, LABEL_HEIGHT);
    dialogueLabel->setPosition(Vec2(dialogueBackground->getPositionX() - 240, dialogueBackground->getPositionY()));
    dialogueLabel->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
    dialogueLabel->setTextColor(Color4B::WHITE);

    // NPC立绘
    std::string npcImageName = "npcImages/" + npc->getNpcName() + "Talk.png";
    npcTalkImage = Sprite::create(npcImageName);
    npcTalkImage->setPosition(Vec2(dialogueBackground->getPositionX() + 365, dialogueBackground->getPositionY() + 40));

    // NPC名字
    nameLabel = Label::createWithTTF(npc->getNpcName(), ResPath::FONT_TTF, 40);
    nameLabel->setPosition(Vec2(dialogueBackground->getPositionX() + 360, dialogueBackground->getPositionY() - 140));
    nameLabel->setTextColor(Color4B::WHITE);

    return true;
}

bool DialogueBox::init()
{
    if (!Node::init()) {
        return false;
    }

    NoticeBoard* board = NoticeBoard::create();

    // 创建对话框背景
    dialogueBackground = Sprite::create(DIALOGUE_BACKGROUND);
    if (!dialogueBackground) {
        return false;
    }
    dialogueBackground->setContentSize(Size(TALKING_BOX_WIDTH, TALKING_BOX_HEIGHT)); // 设置对话框大小
    dialogueBackground->setPosition(Vec2(TALKING_BOX_X, TALKING_BOX_Y));  // 设置对话框位置

    // 创建并显示对话内容
    dialogueLabel = Label::createWithTTF(board->printDialogue(), ResPath::FONT_TTF, 44);
    // 设置文字框
    dialogueLabel->setDimensions(LABEL_WIDTH, LABEL_HEIGHT);
    dialogueLabel->setPosition(Vec2(dialogueBackground->getPositionX() - 240, dialogueBackground->getPositionY()));
    dialogueLabel->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
    dialogueLabel->setTextColor(Color4B::WHITE);
    return true;
}

void DialogueBox::showInitialDialogue() {
    // 标记对话框已显示
    setDialogueVisible(true);

    this->addChild(dialogueBackground);
    this->addChild(dialogueLabel);
    this->addChild(npcTalkImage);
    this->addChild(nameLabel);

    // 创建鼠标事件监听器
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = [listener, this](Event* event) {
        auto mouseEvent = dynamic_cast<EventMouse*>(event);
        if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT && getDialogueVisible()) {
            // 显示选项按钮
            showDialogueOptions(listener);
        }
        };
    // 添加鼠标事件监听器到事件分发器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


void DialogueBox::showBoardDialogue() {
    setDialogueVisible(true);
    this->addChild(dialogueBackground);
    this->addChild(dialogueLabel);

    // 创建鼠标事件监听器
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = [listener, this](Event* event) {
        auto mouseEvent = dynamic_cast<EventMouse*>(event);
        if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT && getDialogueVisible()) {
            Bag* bag = Bag::getInstance();
            if (!NoticeBoard::getTaskStatus()) {
                if (bag->checkItemIn("stone") && bag->getItemQuantity(bag->getItemIndex("stone")) >= 3) {
                    auto optionButton = ui::Button::create();
                    optionButton->setTitleText("SUBMIT");
                    optionButton->setTitleFontSize(30);
                    optionButton->setTitleColor(Color3B::WHITE);
                    optionButton->setPosition(Vec2(400, 200));
                    optionButton->addClickEventListener([this, optionButton, listener, bag](Ref* sender) {
                        for (int i = 0; i < 3; i++)
                            bag->removeItem(bag->getItemIndex("stone"));
                        NoticeBoard::create()->completeTask();
                        optionButton->setVisible(false);
                        closeDialogue(listener);
                        //给出房子
                        auto building = Sprite::create(BUILDING.image);
                        building->setPosition(Vec2(BOARD_X, BOARD_Y));
                        BeachMap::getInstance()->addChild(building);
                        });
                    this->addChild(optionButton);
                }
                else
                    closeDialogue(listener);
            }
            else
                closeDialogue(listener);
        }
        };
    // 添加鼠标事件监听器到事件分发器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this->getParent());
}

void DialogueBox::showDialogueOptions(EventListenerMouse* lastListener) {
    dialogueLabel->setVisible(false);
    _eventDispatcher->removeEventListener(lastListener);
    auto listener = EventListenerMouse::create();
    // 创建选项按钮
    // 选项文本内容
    for (size_t i = 0; i < options.size(); ++i) {
        auto optionButton = ui::Button::create();
        optionButton->setTitleText(options[i]);
        optionButton->setTitleFontSize(30);
        optionButton->setTitleColor(Color3B::WHITE);
        optionButton->setPosition(Vec2(300, 300 - (i * 60)));
        optionButtons.push_back(optionButton); // 添加到按钮容器
        optionButton->addClickEventListener([this, i](Ref* sender) {
            updateDialogueAfterOptionSelected(i);
            });
        this->addChild(optionButton);
    }
}

void DialogueBox::updateDialogueAfterOptionSelected(int optionIndex) {
    // 隐藏所有选项按钮
    for (auto button : optionButtons) {
        button->setVisible(false);
    }
    // 创建键盘事件监听器
    auto listenerKey = EventListenerKeyboard::create();
    // 重新创建鼠标事件监听器
    auto listener = EventListenerMouse::create();

    // 更新对话框内容
    std::string newDialogue;
    Bag* bag = Bag::getInstance();
    switch (optionIndex) {
        case 0:
            newDialogue = npc->printStatus();
            break;
        case 1:
            if (npc->getTaskStatus()) {
                newDialogue = "\nYou have done all your work. I don't have any new task for you, at least for now.";
                break;
            }
            newDialogue = npc->getTask();
            // 每一npc有特殊任务
            // wizard
            if (npc->getNpcName() == "Wizard Yuuu" && bag->checkItemIn("tuna")) {
                npc->setTaskStatus(true);
                Player::getInstance()->setPopularity(Player::getInstance()->getPopularity() + 10);
                newDialogue += "\nOops! My cat stole a tuna from you.Your popularity increased to " + std::to_string(Player::getInstance()->getPopularity());
                newDialogue += "\nI will give you some stones as reward.";
                bag->removeItem(bag->getItemIndex("tuna"));
                for (int i = 0; i < rand() % 7 + 3; i++)
                    bag->addItem(StoneItem::create(STONE_ITEM));
            }
            // cleaner
            if (npc->getNpcName() == "Cleaner Levi" && NoticeBoard::getTaskStatus()) {
                npc->setTaskStatus(true);
                Player::getInstance()->setPopularity(Player::getInstance()->getPopularity() + 10);
                newDialogue += " Thanks for your contribution to the reconstruction of Paradi island.Your popularity increased to " + std::to_string(Player::getInstance()->getPopularity());
                newDialogue += "\nI will give you some tunas as reward.";
                for (int i = 0; i < rand() % 7 + 3; i++)
                    bag->addItem(Food::create(TUNA));
            }
            break;
        case 2:
            newDialogue = "Upcoming festival: " + getNextFestival();
            break;
        case 3:
            newDialogue = "(press Q to sent gift, Left Click to leave...)";
            listenerKey->onKeyPressed = [this, listenerKey](EventKeyboard::KeyCode keyCode, Event* event) {
                Bag* bag = Bag::getInstance();
                std::string gift = bag->getSelectedItem()->getItemName();
                if (keyCode == EventKeyboard::KeyCode::KEY_Q && bag->getSelectedIndex() >= 6 && bag->getSelectedItem()) {
                    giftBox(gift, listenerKey);
                    bag->removeItem(bag->getSelectedIndex());
                }
                };
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this->getParent());
            break;
        default:
            break;
    }

    // 更新对话框中的文字
    dialogueLabel->setString(newDialogue);
    dialogueLabel->setVisible(true);

    listener->onMouseDown = [=](Event* event) {
        auto mouseEvent = dynamic_cast<EventMouse*>(event);
        if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
            closeDialogue(listener);
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this->getParent());
    
}

void DialogueBox::giftBox(std::string giftName, EventListenerKeyboard* lastListener)
{
    _eventDispatcher->removeEventListener(lastListener);
    // 更新对话框内容
    std::string newDialogue = npc->giveGift(giftName);
    
    npc->interactWithPlayer();
    // 更新对话框中的文字
    dialogueLabel->setString(newDialogue);
    dialogueLabel->setVisible(true);
}

void DialogueBox::closeDialogue(EventListenerMouse* lastListener) {
    _eventDispatcher->removeEventListener(lastListener);
    this->removeFromParent();  // 移除对话框
    setDialogueVisible(false);

}

// 获取节日
std::string DialogueBox::getNextFestival() {

    // 获取日期单例
    DateManage* dateManager = DateManage::getInstance();

    std::string res = "Today is " + dateManager->getCurrentDate() + "!\n";
    if (dateManager->isFestivalDay()) {
        int dayInSeason = dateManager->getCurrentDayInSeason();
        if (dateManager->getCurrentSeason() == "Spring" && dayInSeason == 7)
            res += SPRING_CONVERSATION;
        else if (dateManager->getCurrentSeason() == "Summer" && dayInSeason == 15)
            res += SUMMER_CONVERSATION;
        else if (dateManager->getCurrentSeason() == "Fall" && dayInSeason == 5)
            res += FALL_CONVERSATION;
        else if (dateManager->getCurrentSeason() == "Winter" && dayInSeason == 25)
            res += WINTER_CONVERSATION;
    }

    FarmMap* farmMap = FarmMap::getInstance();
    DateManage* dateManage = DateManage::getInstance();
    for (Festival* festival : dateManage->festivals) {
        std::string season, day, curSeason;
        std::istringstream stream(festival->getEventDate());
        stream >> season; // 读取季节
        stream >> day;    // 读取日期
        int date = std::stoi(day);

        std::istringstream streamCur(dateManager->getCurrentDate());
        streamCur >> curSeason >> day;
        if (season == dateManager->getCurrentSeason() && date > std::stoi(day))
            return festival->getEventName() + "is coming soon!";
        else if (season > dateManager->getCurrentSeason())
            return festival->getEventName() + "is coming soon!";
    }
    return "waiting for next year..";
}

