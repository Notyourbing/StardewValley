#include "Player.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

// 这里是定义 problemLoading 函数
static void problemLoading(const char* filename) {
    CCLOG("Error while loading: %s", filename);
    printf("Error while loading: %s\n", filename);
}
// 初始化静态成员变量
Player* Player::instance = nullptr;

Player::Player()
    : velocity(Vec2::ZERO),
    name(""),
    currentAnimationName(""),
    lastDirection(Vec2::ZERO) {
}

Player::~Player() {}

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

bool Player::init() {
    if (!Sprite::initWithFile("playerWalkImages/standDown.png")) {
        problemLoading("playerWalkImages/standDown.png");
        return false;
    }

    // 初始速度为零
    velocity = Vec2::ZERO;
    loadStandFrames();
    // 每dt时间调用一次
    schedule([this](float dt) {
        // 获取界面尺寸和玩家尺寸
        const auto visibleSize = Director::getInstance()->getVisibleSize();

        const Vec2 playerSize(Player::getInstance()->getContentSize());

        auto position = getPosition() + velocity * dt;
        // 边界检测，防止玩家移出屏幕
        position.x = std::max(playerSize.x / 2, std::min(position.x, visibleSize.width - playerSize.x / 2));
        position.y = std::max(playerSize.y / 2, std::min(position.y, visibleSize.height - playerSize.y / 2));
        setPosition(position);
        }, "playerMovement");

    return true;
}

//根据移动方向播放动画并移动角色
void Player::moveByDirection(const Vec2& direction) {
    if (direction.lengthSquared() == 0) {
        return;
    }
    velocity = direction * 200.0f;

    if (direction.x > 0) {
        createWalkAnimation("right/", "walkRight", 3);//播放动画
        lastDirection = Vec2(1, 0); // 记录最后移动的方向
    }
    else if (direction.x < 0) {
        createWalkAnimation("left/", "walkLeft", 3);
        lastDirection = Vec2(-1, 0); // 记录最后移动的方向
    }
    else if (direction.y > 0) {
        createWalkAnimation("up/", "walkUp", 4);
        lastDirection = Vec2(0, 1); // 记录最后移动的方向
    }
    else if (direction.y < 0) {
        createWalkAnimation("down/", "walkDown", 4);
        lastDirection = Vec2(0, -1); // 记录最后移动的方向
    }
}

//在键盘松开后停止动作
void Player::stopMoving() {
    velocity = Vec2::ZERO; // 停止移动
    stopAllActions();

    // 根据最后移动的方向设置站立姿势
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

void Player::setPlayerName(const std::string& name) {
    this->name = name;
}

std::string Player::getPlayerName() const {
    return name;
}
// 加载全部站立帧的纹理
void Player::loadStandFrames() {
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();


    createStandFrame("playerWalkImages/standDown.png", "standDown");
    createStandFrame("playerWalkImages/standUp.png", "standUp");
    createStandFrame("playerWalkImages/standLeft.png", "standLeft");
    createStandFrame("playerWalkImages/standRight.png", "standRight");

}

//创建移动动画
void Player::createWalkAnimation(const std::string& baseFilename, const std::string& animationName, int frameCount) {
    //先建立移动帧
    SpriteFrame* frame = nullptr;

    Vector<SpriteFrame*> frameVec;

    for (int i = 0; i < frameCount; ++i) {
        std::string filename = StringUtils::format("playerWalkImages/walk%s%d.png", baseFilename.c_str(), i);
        frame = SpriteFrame::create(filename, CCRectMake(0, 0, 70, 120));
        frameVec.pushBack(frame);
    }
    //用移动帧创建动画
    Animation* animation = Animation::createWithSpriteFrames(frameVec);
    animation->setLoops(-1);
    animation->setDelayPerUnit(0.1f);

    CCAnimate* animate = CCAnimate::create(animation);

    Player::runAction(animate);
}

//加载某一方向（用filename决定）的站立帧
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

//设置站立动作
void Player::setStandPose(const std::string& standPoseName) {
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    SpriteFrame* frame = frameCache->getSpriteFrameByName(standPoseName);
    if (frame) {
        setSpriteFrame(frame);
    }
}