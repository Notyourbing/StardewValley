#include "Player.h"

USING_NS_CC;

// 初始化静态成员变量
Player* Player::instance = nullptr;

Player::Player() : velocity(Vec2::ZERO), name("") {}

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
	if (!Sprite::initWithFile("playerImage/downStill.png")) {
		return false;
	}

	// 初始速度为零
	velocity = Vec2::ZERO;

	schedule([this](float dt) {
			auto position = getPosition();
			setPosition(position + velocity * dt);

			// 获取界面尺寸
			auto visibleSize = Director::getInstance()->getVisibleSize();
			const Vec2 origin = Director::getInstance()->getVisibleOrigin();
			// 边界检测，防止玩家移出屏幕
			position = getPosition();
			position.x = std::max(origin.x, std::min(position.x, origin.x + visibleSize.width));
			position.y = std::max(origin.y, std::min(position.y, origin.y + visibleSize.height));
			setPosition(position);
		}, "player_movement");

	return true;
}

void Player::moveByDirection(const Vec2& direction) {
	velocity = direction * 200.0f;
}

void Player::stopMoving() {
	velocity = Vec2::ZERO; // 停止移动
}

void Player::setName(const std::string& name) {
	this->name = name;
}

std::string Player::getPlayerName() const {
	return name;
}