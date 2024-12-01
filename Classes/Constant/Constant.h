#ifndef __CONSTANT_H
#define __CONSTANT_H
#include "../Npc/Npc.h"

constexpr float MAP_MOVE_SPEED = 400.0f;
constexpr float PLAYER_MOVE_SPEED = 200.0f;
constexpr float interactionRange = 100.0f;  // 可调整的阈值，表示玩家与 NPC 之间的最大交互距离

constexpr int WIZARD_X = 300;
constexpr int WIZARD_Y = 300;
constexpr int CLEANER_X = 500;
constexpr int CLEANER_Y = 300;

constexpr int TALKING_BOX_WIDTH = 1283;
constexpr int TALKING_BOX_HEIGHT = 462;

constexpr int TALKING_BOX_X = 640;
constexpr int TALKING_BOX_Y = 200;

constexpr int LABEL_WIDTH = 720;
constexpr int LABEL_HEIGHT = 390;


const Npc WIZARD("Wizard Yuuu", "Fall 5",
	{ "Magic Essence", "Diamond" },
	{ "Milk" },
	{ "Get out of my way.", "It's nice to see you here.", "I like to spend time with you." },
	"npcImages/wizard.png");
const Npc CLEANER("Cleaner Levi", "Winter 25",
	{ "Milk", "Cleaning tools" },
	{ "Clay" },
	{ "...", "Ahh, hi.", "Come and have some black-tea with me." },
	"npcImages/cleaner.png");


#endif __CONSTANT_H
