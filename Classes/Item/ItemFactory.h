/****************************************************************
 * File Function: 实现物品工厂类，工厂模式制造物品
 * Author:        赵卓冰 高鑫
 ****************************************************************/
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
#include "../Tool/Agrochemical.h"
#include "../Food/Food.h"
#include "../Animal/AnimalItem.h"

// 物品工厂，负责造工具
class ItemFactory {
public:
    static Item* createItem(const std::string& itemName) {
        if (itemName == "axe") {
            return Axe::create();
        }
        else if (itemName == "pickaxe") {
            return Pickaxe::create();
        }
        else if (itemName == "hoe") {
            return Hoe::create();
        }
        else if (itemName == "scythe") {
            return Scythe::create();
        }
        else if (itemName == "fishingRod") {
            return FishingRod::create();
        }
        else if (itemName == "kettle") {
            return Kettle::create();
        }
        else if (itemName == "dogbaneSeed") {
            return DogbaneSeed::create();
        }
        else if (itemName == "cornSeed") {
            return CornSeed::create();
        }
        else if (itemName == "carrotSeed") {
            return CarrotSeed::create();
        }
        else if (itemName == "agrochemical") {
            return Agrochemical::create();
        }
        else if (itemName == "fertilizer") {
            return Fertilizer::create();
        }
        else if (itemName == "cow") {
            return CowItem::create();
        }
        else if (itemName == "chicken") {
            return ChickenItem::create();
        }
        else if (itemName == "sheep") {
            return SheepItem::create();
        }
        else if (itemName == "pig") {
            return PigItem::create();
        }
        else if (itemName == "tuna") {
            return Food::create(TUNA);
        }
        else if (itemName == "anchovy") {
            return Food::create(ANCHOVY);
        }
        else if (itemName == "pufferFish") {
            return Food::create(PUFFER_FISH);
        }
        else {
            CCLOG("Unknown item name: %s", itemName.c_str());
            return nullptr;
        }
    }
};

#endif
