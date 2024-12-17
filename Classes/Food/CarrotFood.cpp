#include "CarrotFood.h"
#include "../Constant/Constant.h"

// create方法：用于创建并返回初始化的Food对象
CarrotFood* CarrotFood::create() {
    CarrotFood* carrotFood = new (std::nothrow) CarrotFood();
    // 使用 item_info 初始化 Food 的状态
    if (carrotFood && carrotFood->init()) {
        carrotFood->autorelease();
        return carrotFood;
    }
    else {
        CC_SAFE_DELETE(carrotFood);
        return nullptr;
    }
}


// init方法：用于初始化Food对象的内部状态
bool CarrotFood::init() {
    return Food::init(CARROT_ITEM);
}