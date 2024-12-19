#include "Seed.h"
#include "cocos2d.h"

USING_NS_CC;


bool Seed::init(const SeedType& seedType) {
    // 对于不同的种类进行初始化
    switch (seedType){ 
    case SeedType::DogbaneSeed:
        seedName = "dogbaneSeed";
        return Tool::init({ "dogbaneSeed", DOGBANE_SEED});
        break;
    case SeedType::CornSeed:
        seedName = "cornSeed";
        return Tool::init({ "cornSeed", CORN_SEED});
        break;
    case SeedType::CarrotSeed:
        seedName = "carrotSeed";
        return Tool::init({ "carrotSeed", CARROT_SEED});
        break;
    }
   
}

void Seed::useItem() {
    return;
}

DogbaneSeed* DogbaneSeed::create() {
    DogbaneSeed* seed = new (std::nothrow) DogbaneSeed();
    if (seed && seed->init(SeedType::DogbaneSeed)) {
        seed->autorelease();
        return seed;
    }
    CC_SAFE_DELETE(seed);
    return nullptr;
}

CornSeed* CornSeed::create() {
    CornSeed* seed = new (std::nothrow) CornSeed();
    if (seed && seed->init(SeedType::CornSeed)) {
        seed->autorelease();
        return seed;
    }
    CC_SAFE_DELETE(seed);
    return nullptr;
}

CarrotSeed* CarrotSeed::create() {
    CarrotSeed* seed = new (std::nothrow) CarrotSeed();
    if (seed && seed->init(SeedType::CarrotSeed)) {
        seed->autorelease();
        return seed;
    }
    CC_SAFE_DELETE(seed);
    return nullptr;
}
