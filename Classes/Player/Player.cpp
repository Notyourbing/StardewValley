#include "Player.h"
#include "SimpleAudioEngine.h"
#include "../Map/FarmMap.h"
#include "../Constant/Constant.h"
#include "../Control/Control.h"

USING_NS_CC;


// 初始化静态成员变量
Player* Player::instance = nullptr;

// 单例模式获取玩家实例
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

Player::~Player() {
    if (instance != nullptr) {
        instance = nullptr;
    }
}

// 初始化
bool Player::init() {
    if (!Sprite::initWithFile(ResPath::STAND_DOWN)) {
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

        // 检查目标位置是否是障碍物
        auto farmMap = FarmMap::getInstance();

        // 人在地图坐标中下一步会到达的位置
        // 这里的- velocity / PLAYER_MOVE_SPEED.0f * 10.0f是预测下一步的位置
        // velocity / PLAYER_MOVE_SPEED.0f是因为velocity的绝对值是PLAYER_MOVE_SPEED
        Vec2 playerSize1 = Vec2(0.0f, getContentSize().height * 1.0f);

        auto targetPosition = getPosition() - farmMap->getPosition() - playerSize1 * 0.5f + velocity / PLAYER_MOVE_SPEED * 10.0f; // 每帧移动的距离
        if (farmMap->isCollidable(targetPosition)) {
            velocity = Vec2::ZERO;
        }
        
        auto position = getPosition() + velocity * dt;
        // 边界检测，防止玩家移出屏幕
        position.x = std::max(playerSize.x / 2, std::min(position.x, visibleSize.width - playerSize.x / 2));
        position.y = std::max(playerSize.y / 2, std::min(position.y, visibleSize.height - playerSize.y / 2));
        setPosition(position);
        }, "playerMovement");

    return true;
}

// 设置玩家姓名
void Player::setPlayerName(const std::string& name) {
    this->name = name;
}

// 获取玩家姓名
std::string Player::getPlayerName() const {
    return name;
}

//根据移动方向播放动画并移动角色
void Player::moveByDirection(const Vec2& direction) {
    if (direction.lengthSquared() == 0) {
        return;
    }
    velocity = direction * PLAYER_MOVE_SPEED;

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

Vec2 Player::getLastDirection() const {
    return lastDirection;
}

// 加载全部站立帧的纹理
void Player::loadStandFrames() {
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    createStandFrame(ResPath::STAND_DOWN, "standDown");
    createStandFrame(ResPath::STAND_UP, "standUp");
    createStandFrame(ResPath::STAND_LEFT, "standLeft");
    createStandFrame(ResPath::STAND_RIGHT, "standRight");

}

//创建移动动画
void Player::createWalkAnimation(const std::string& baseFilename, const std::string& animationName, int frameCount) { 
    if (currentAnimationName == animationName) {
        return; // 如果当前已经在播放相同的动画，则无需重复播放
    }

    stopAllActions(); // 停止所有动作
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
        return;
    }

    Rect rect(0, 0, texture->getContentSize().width, texture->getContentSize().height);
    SpriteFrame* frame = SpriteFrame::createWithTexture(texture, rect);
    if (frame) {
        frameCache->addSpriteFrame(frame, animationName);
    }
    else {
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

// 获取当前物品名称
std::string Player::getCurrentItemName() const {
    return currentItem->getItemName();
}

// 使用当前工具
void Player::useCurrentItem() {
    if (currentItem) {
        // 使用工具
        currentItem->useItem();  // 触发工具的动画
        // 使用完成后将工具重新添加回玩家，并恢复玩家状态
        currentItem->runAction(Sequence::create(
            DelayTime::create(0.5f),  // 等待工具使用完成
            CallFunc::create([this]() {
                Control::updateMovement();
                }),
            nullptr
        ));

    }
}

// 设置当前工具
void Player::setCurrentItem(Item* item) {
    if (item) {
        currentItem = item;
    }
}
