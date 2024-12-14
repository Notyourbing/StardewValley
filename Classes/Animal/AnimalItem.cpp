#include "AnimalItem.h"
#include "../Map/FarmMap.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// AnimalItem类：初始化
bool AnimalItem::init(const ItemInfo& item_info) {
	itemName = (std::string)item_info.name;
	itemImage = (std::string)item_info.image;
	return Sprite::initWithFile(item_info.image);
}

// CowItem静态创建方法
CowItem* CowItem::create() {
	CowItem* cowItem = new(std::nothrow) CowItem();
	if (cowItem && cowItem->init()) {
		cowItem->autorelease();
		return cowItem;
	}
	CC_SAFE_DELETE(cowItem);
	return nullptr;
}

// 初始化
bool CowItem ::init() {
	// 调用基类的初始化方法
	return AnimalItem::init(COW_ITEM);
}

// 使用工具
void CowItem::useItem() {

}

// CowItem静态创建方法
SheepItem* SheepItem::create() {
	SheepItem* sheepItem = new(std::nothrow) SheepItem();
	if (sheepItem && sheepItem->init()) {
		sheepItem->autorelease();
		return sheepItem;
	}
	CC_SAFE_DELETE(sheepItem);
	return nullptr;
}

// 初始化
bool SheepItem::init() {
	// 调用基类的初始化方法
	return AnimalItem::init(SHEEP_ITEM);
}

// 使用工具
void SheepItem::useItem() {

}

// CowItem静态创建方法
ChickenItem* ChickenItem::create() {
	ChickenItem* chickenItem = new(std::nothrow) ChickenItem();
	if (chickenItem && chickenItem->init()) {
		chickenItem->autorelease();
		return chickenItem;
	}
	CC_SAFE_DELETE(chickenItem);
	return nullptr;
}

// 初始化
bool ChickenItem::init() {
	// 调用基类的初始化方法
	return AnimalItem::init(CHICKEN_ITEM);
}

// 使用工具
void ChickenItem::useItem() {

}

// CowItem静态创建方法
PigItem* PigItem::create() {
	PigItem* pigItem = new(std::nothrow) PigItem();
	if (pigItem && pigItem->init()) {
		pigItem->autorelease();
		return pigItem;
	}
	CC_SAFE_DELETE(pigItem);
	return nullptr;
}

// 初始化
bool PigItem::init() {
	// 调用基类的初始化方法
	return AnimalItem::init(PIG_ITEM);
}

// 使用工具
void PigItem::useItem() {

}