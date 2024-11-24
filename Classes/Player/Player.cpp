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
		}, "player_movement");

	return true;
}

void Player::moveByDirection(const Vec2& direction) {
	velocity = direction * 200.0f;
}


void Player::setPlayerName(const std::string& name) {
	this->name = name;
}

std::string Player::getPlayerName() const {
	return name;
}