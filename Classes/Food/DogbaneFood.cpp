#include "DogbaneFood.h"
#include "../Constant/Constant.h"

// create方法：用于创建并返回初始化的Food对象
DogbaneFood* DogbaneFood::create() {
    DogbaneFood* dogbaneFood = new (std::nothrow) DogbaneFood();
    // 使用 item_info 初始化 Food 的状态
    if (dogbaneFood && dogbaneFood->init()) {
        dogbaneFood->autorelease();
        return dogbaneFood;
    }
    else {
        CC_SAFE_DELETE(dogbaneFood);
        return nullptr;
    }
}


// init方法：用于初始化Food对象的内部状态
bool DogbaneFood::init() {
    return Food::init(DOGBANE_ITEM);
}