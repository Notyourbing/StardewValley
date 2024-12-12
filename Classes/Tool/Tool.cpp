#include "Tool.h"
#include "../Map/FarmMap.h"


USING_NS_CC;


bool Tool::init(const ItemInfo& item_info) {
	itemName = (std::string)item_info.name;
	itemImage = (std::string)item_info.image;
	return Sprite::initWithFile(item_info.image);
}