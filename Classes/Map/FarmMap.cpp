#include "FarmMap.h"

USING_NS_CC;

// 初始化静态实例
FarmMap* FarmMap::instance = nullptr;

FarmMap::FarmMap() : velocity(Vec2::ZERO) {}

FarmMap::~FarmMap() {}

FarmMap* FarmMap::getInstance() {
    if (!instance) {
        instance = new (std::nothrow) FarmMap();
        if (instance) {
            instance->autorelease();
        }
        else {
            CC_SAFE_DELETE(instance);
        }
    }
    return instance;
}

bool FarmMap::init(const std::string& tmxFile) {
    if (!Node::init()) {
        return false;
    }

    velocity = Vec2::ZERO;

    // 如果传入了文件名,加载地图
    if (!tmxFile.empty()) {
        map = TMXTiledMap::create(tmxFile);
        if (!map) {
            return false;
        }
        this->addChild(map);
        schedule([this](float dt) {
            auto position = getPosition() + velocity * dt;
            // 获取界面尺寸
            const auto visibleSize = Director::getInstance()->getVisibleSize();
            // max保证大于等于下界， min保证小于等于上界
            position.x = std::max(visibleSize.width - getMapSize().width, std::min(position.x, 0.0f));
            position.y = std::max(visibleSize.height - getMapSize().height, std::min(position.y, 0.0f));

            setPosition(position);
            }, "farm_map");
    }

    return true;
}

void FarmMap::moveMapByDirection(const Vec2& direction) {
    velocity = direction * 200.f;
}

Size FarmMap::getMapSize() const {
    return map->getContentSize();
}
