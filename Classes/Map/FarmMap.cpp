#include "FarmMap.h"

USING_NS_CC;

// ��ʼ����̬ʵ��
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

    // ����������ļ���,���ص�ͼ
    if (!tmxFile.empty()) {
        map = TMXTiledMap::create(tmxFile);
        if (!map) {
            return false;
        }
        this->addChild(map);
        schedule([this](float dt) {
            auto position = getPosition() + velocity * dt;
            // ��ȡ����ߴ�
            const auto visibleSize = Director::getInstance()->getVisibleSize();
            // max��֤���ڵ����½磬 min��֤С�ڵ����Ͻ�
            position.x = std::max(visibleSize.width - getMapSize().width, std::min(position.x, 0.0f));
            position.y = std::max(visibleSize.height - getMapSize().height, std::min(position.y, 0.0f));

            setPosition(position);
            }, "farm_map");
    }

    return true;
}

bool FarmMap::npcInit(const Vec2& position, Npc* npc)
{
    npc->setPosition(position);
    this->addChild(npc, 5);

    return true;
}

void FarmMap::moveMapByDirection(const Vec2& direction) {
    velocity = direction * 200.f;
}

Size FarmMap::getMapSize() const {
    return map->getContentSize();
}

