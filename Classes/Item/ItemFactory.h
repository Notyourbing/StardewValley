#ifndef __ITEM_FACTORY_H__
#define __ITEM_FACTORY_H__

#include <string>
#include "Item.h"
#include "../Tool/Axe.h"
#include "../Tool/Pickaxe.h"
#include "../Tool/Hoe.h"
#include "../Tool/Scythe.h"
#include "../Tool/FishingRod.h"
#include "../Tool/Kettle.h"
#include "../Tool/Seed.h"
#include "../Tool/Fertilizer.h"
#include "../Food/Food.h"
#include "../Animal/AnimalItem.h"

// 物品工厂，负责造工具
class ItemFactory {
public:
    static Item* createItem(const std::string& itemName) {
        if (itemName == "Axe") {
            return Axe::create();
        }
        else if (itemName == "Pickaxe") {
            return Pickaxe::create();
        }
        else if (itemName == "Hoe") {
            return Hoe::create();
        }
        else if (itemName == "Scythe") {
            return Scythe::create();
        }
        else if (itemName == "FishingRod") {
            return FishingRod::create();
        }
        else if (itemName == "Kettle") {
            return Kettle::create();
        }
        else if (itemName == "AppleSeed") {
            return AppleSeed::create();
        }
        else if (itemName == "CornSeed") {
            return CornSeed::create();
        }
        else if (itemName == "CarrotSeed") {
            return CarrotSeed::create();
        }
        else if (itemName == "Fertilizer") {
            return Fertilizer::create();
        }
        else if (itemName == "Tuna") {
            return Food::create(TUNA);
        }
        else if (itemName == "Cow") {
            return CowItem::create();
        }
        else if (itemName == "Chicken") {
            return ChickenItem::create();
        }
        else if (itemName == "Sheep") {
            return SheepItem::create();
        }
        else if (itemName == "Pig") {
            return PigItem::create();
        }
        else {
            CCLOG("Unknown item name: %s", itemName.c_str());
            return nullptr;
        }
    }
};

#endif // __ITEM_FACTORY_H__
