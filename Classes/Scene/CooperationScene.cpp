#include "CooperationScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

// ��ӡ���õı�����Ϣ
static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in WelcomeScene.cpp\n");
}

Scene* Cooperation::createScene() {
    return Cooperation::create();
}

bool Cooperation::init() {
    if (!Scene::init()) {
        return false;
    }

    // ��ȡ����ߴ�
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ��������
    std::string backgroundPath = "icon/coopBackground.png";
    auto background = Sprite::create(backgroundPath);
    if (background == nullptr) {
        problemLoading(backgroundPath.c_str());
        return false;
    }
    else {
        background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        // ȷ�������� z-order ���
        this->addChild(background, 0);
    }

    // ���������򱳾�
    std::string coopPanelPath = "icon/cooperationPanel.png";
    auto coopPanel = Sprite::create(coopPanelPath);
    coopPanel->setName("coopPanel");

    if (coopPanel == nullptr) {
        problemLoading(coopPanelPath.c_str());
        return false;
    }
    else {
        coopPanel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(coopPanel, 1);

        // ������ʾ��Ѱ�ң�
        coopText = Label::createWithTTF("Connecting to online services...", "fonts/Marker Felt.ttf", 24);  // ���������С
        if (coopText == nullptr) {
            problemLoading("Error loading font for coopText\n");
            return false;
        }
        else {
            // ��������λ�ã�ʹ��λ����Ļ����
            const Vec2 textPosition = Vec2(visibleSize.width / 2, visibleSize.height / 2);
            coopText->setPosition(textPosition);
            // ȷ�����ֵ� z-order ���ں�����
            this->addChild(coopText, 2);
        }
    }

    // ������
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
        // �������½ǵ�λ��
        const float rightPadding = 40;
        const float bottomPadding = 20;
        const float x = origin.x + visibleSize.width - backItem->getContentSize().width / 2 - rightPadding;
        const float y = origin.y + bottomPadding + backItem->getContentSize().height / 2;
        backItem->setPosition(Vec2(x, y));
        //this->addChild(backItem, 5);  // ȷ�� backItem �� z-order ���� coopPanel �� coopText
    }
    // �����˵�����
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 8);

    // ���·���İ�ť
    auto upButton = MenuItemImage::create(
        "icon/upArrow.png",  // ���ϼ�ͷͼ��
        "icon/upArrow.png",  // ���ϼ�ͷͼ��
        CC_CALLBACK_1(Cooperation::onUpButtonClicked, this));
    auto downButton = MenuItemImage::create(
        "icon/downArrow.png",  // ���¼�ͷͼ��
        "icon/downArrow.png",  // ���¼�ͷͼ��
        CC_CALLBACK_1(Cooperation::onDownButtonClicked, this));

    // ȷ����ťλ����ȷ���������Ҳ����
    const float buttonPadding = 40;
    upButton->setPosition(Vec2(visibleSize.width - buttonPadding, visibleSize.height / 2 + 50));
    downButton->setPosition(Vec2(visibleSize.width - buttonPadding, visibleSize.height / 2 - 50));

    auto buttonMenu = Menu::create(upButton, downButton, NULL);
    buttonMenu->setPosition(Vec2::ZERO);
    this->addChild(buttonMenu, 7);  // ȷ����ť�� z-order ���� backItem

    return true;
}

void Cooperation::backCallBack(Ref* pSender) {
    Director::getInstance()->popScene();
}

void Cooperation::onUpButtonClicked(Ref* pSender) {
    printf("Up button clicked\n");  // �����־
    if (coopText) {
        auto moveBy = MoveBy::create(0.3f, Vec2(0, -50)); // �����ƶ� 50 ����
        coopText->runAction(moveBy);
    }
}

void Cooperation::onDownButtonClicked(Ref* pSender) {
    printf("Down button clicked\n");  // �����־
    if (coopText) {
        auto moveBy = MoveBy::create(0.3f, Vec2(0, 50)); // �����ƶ� 50 ����
        coopText->runAction(moveBy);
    }
}