#ifndef __CONSTANT_H
#define __CONSTANT_H
#include "../Npc/Npc.h"

constexpr float MAP_MOVE_SPEED = 400.0f;
constexpr float PLAYER_MOVE_SPEED = 200.0f;

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
