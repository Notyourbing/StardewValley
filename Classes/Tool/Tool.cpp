#include "Tool.h"
#include "../Map/FarmMap.h"


USING_NS_CC;


bool Tool::init(const std::string& name) {
	itemName = name;
	return Sprite::initWithFile("tools/" + name + ".png");
}


//void Tool::useItem() {
//	
//}