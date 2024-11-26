#include "Player.h"
#include "SimpleAudioEngine.h"
#include "../Tool/Axe.h"

USING_NS_CC;
using namespace CocosDenshion;

// �����Ƕ��� problemLoading ����
static void problemLoading(const char* filename) {
    CCLOG("Error while loading: %s", filename);
    printf("Error while loading: %s\n", filename);
}

// ��ʼ����̬��Ա����
Player* Player::instance = nullptr;

// ����ģʽ��ȡ���ʵ��
Player* Player::getInstance() {
    if (instance == nullptr) {
        instance = new (std::nothrow) Player();
        if (instance && instance->init()) {
            instance->autorelease();
        }
        else {
            CC_SAFE_DELETE(instance);
        }
    }
    return instance;
}

Player::Player()
    : velocity(Vec2::ZERO),
    name(""),
    currentAnimationName(""),
    lastDirection(Vec2::ZERO) {
}

Player::~Player() {}

// ��ʼ��
bool Player::init() {
    if (!Sprite::initWithFile("playerWalkImages/standDown.png")) {
        problemLoading("playerWalkImages/standDown.png");
        return false;
    }

    // ��ʼ�ٶ�Ϊ��
    velocity = Vec2::ZERO;

    // �������ߣ�Ĭ���Ǹ�ͷ����������ӵ�������
    currentTool = Axe::create();
    if (currentTool) {
        // ��ʼʱ���ع���
        currentTool->setVisible(false);
        currentTool->setAnchorPoint(Vec2(0, 0));
        // ������ʼ��Ϊ��ҵ��ӽڵ�
        addChild(currentTool);
        currentTool->setPosition(55, 45);

    }

    loadStandFrames();
    // ÿdtʱ�����һ��
    schedule([this](float dt) {
        // ��ȡ����ߴ����ҳߴ�
        const auto visibleSize = Director::getInstance()->getVisibleSize();

        const Vec2 playerSize(Player::getInstance()->getContentSize());

        auto position = getPosition() + velocity * dt;
        // �߽��⣬��ֹ����Ƴ���Ļ
        position.x = std::max(playerSize.x / 2, std::min(position.x, visibleSize.width - playerSize.x / 2));
        position.y = std::max(playerSize.y / 2, std::min(position.y, visibleSize.height - playerSize.y / 2));
        setPosition(position);
        }, "playerMovement");

    return true;
}

// �����������
void Player::setPlayerName(const std::string& name) {
    this->name = name;
}

// ��ȡ�������
std::string Player::getPlayerName() const {
    return name;
}

//�����ƶ����򲥷Ŷ������ƶ���ɫ
void Player::moveByDirection(const Vec2& direction) {
    if (direction.lengthSquared() == 0) {
        return;
    }
    velocity = direction * 200.0f;

    if (direction.x > 0) {
        createWalkAnimation("right/", "walkRight", 3);//���Ŷ���
        lastDirection = Vec2(1, 0); // ��¼����ƶ��ķ���
    }
    else if (direction.x < 0) {
        createWalkAnimation("left/", "walkLeft", 3);
        lastDirection = Vec2(-1, 0); // ��¼����ƶ��ķ���
    }
    else if (direction.y > 0) {
        createWalkAnimation("up/", "walkUp", 4);
        lastDirection = Vec2(0, 1); // ��¼����ƶ��ķ���
    }
    else if (direction.y < 0) {
        createWalkAnimation("down/", "walkDown", 4);
        lastDirection = Vec2(0, -1); // ��¼����ƶ��ķ���
    }
}

//�ڼ����ɿ���ֹͣ����
void Player::stopMoving() {
    velocity = Vec2::ZERO; // ֹͣ�ƶ�
    stopAllActions();

    // ��������ƶ��ķ�������վ������
    if (lastDirection.equals(Vec2(1, 0))) {
        setStandPose("standRight");
    }
    else if (lastDirection.equals(Vec2(-1, 0))) {
        setStandPose("standLeft");
    }
    else if (lastDirection.equals(Vec2(0, 1))) {
        setStandPose("standUp");
    }
    else if (lastDirection.equals(Vec2(0, -1))) {
        setStandPose("standDown");
    }
}

Vec2 Player::getLastDirection() const {
    return lastDirection;
}

// ����ȫ��վ��֡������
void Player::loadStandFrames() {
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();


    createStandFrame("playerWalkImages/standDown.png", "standDown");
    createStandFrame("playerWalkImages/standUp.png", "standUp");
    createStandFrame("playerWalkImages/standLeft.png", "standLeft");
    createStandFrame("playerWalkImages/standRight.png", "standRight");

}

//�����ƶ�����
void Player::createWalkAnimation(const std::string& baseFilename, const std::string& animationName, int frameCount) {
    //�Ƚ����ƶ�֡
    SpriteFrame* frame = nullptr;

    Vector<SpriteFrame*> frameVec;

    for (int i = 0; i < frameCount; ++i) {
        std::string filename = StringUtils::format("playerWalkImages/walk%s%d.png", baseFilename.c_str(), i);
        frame = SpriteFrame::create(filename, CCRectMake(0, 0, 70, 120));
        frameVec.pushBack(frame);
    }
    //���ƶ�֡��������
    Animation* animation = Animation::createWithSpriteFrames(frameVec);
    animation->setLoops(-1);
    animation->setDelayPerUnit(0.1f);

    CCAnimate* animate = CCAnimate::create(animation);

    Player::runAction(animate);
}

//����ĳһ������filename��������վ��֡
void Player::createStandFrame(const std::string& filename, const std::string& animationName) {
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

    Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(filename);
    if (!texture) {
        problemLoading(filename.c_str());
        return;
    }

    Rect rect(0, 0, texture->getContentSize().width, texture->getContentSize().height);
    SpriteFrame* frame = SpriteFrame::createWithTexture(texture, rect);
    if (frame) {
        frameCache->addSpriteFrame(frame, animationName);
    }
    else {
        problemLoading(("stand" + animationName).c_str());
    }
}

//����վ������
void Player::setStandPose(const std::string& standPoseName) {
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    SpriteFrame* frame = frameCache->getSpriteFrameByName(standPoseName);
    if (frame) {
        setSpriteFrame(frame);
    }
}

// ���õ�ǰ����
void Player::setCurrentTool(Tool* tool) {
    currentTool = tool;
}

// ʹ�õ�ǰ����
void Player::useCurrentTool() {
    if (currentTool) {
        // ����λ�ú�����λ����ͬ
        // currentTool->setPosition(getPosition());
        currentTool->setVisible(true);
        currentTool->useTool();

        // ʹ����ɺ����ع���
        currentTool->runAction(Sequence::create(
            DelayTime::create(0.5f), // �ȴ�����ʹ�����
            CallFunc::create([this]() {
                currentTool->setVisible(false);
                }),
            nullptr
        ));
    }
}