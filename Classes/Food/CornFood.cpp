#include "CornFood.h"
#include "../Constant/Constant.h"

// create方法：用于创建并返回初始化的Food对象
CornFood* CornFood::create() {
    CornFood* cornFood = new (std::nothrow) CornFood();
    // 使用 item_info 初始化 Food 的状态
    if (cornFood && cornFood->init()) {
        cornFood->autorelease();
        return cornFood;
    }
    else {
        CC_SAFE_DELETE(cornFood);
        return nullptr;
    }
}


// init方法：用于初始化Food对象的内部状态
bool CornFood::init() {
    return Food::init(CORN_ITEM);
}