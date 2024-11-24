#include "Tool.h"

bool Tool::init(const std::string& name) {
	toolName = name;

	if (!Sprite::initWithFile("tools/" + toolName + ".png")) {
		return false;
	}

	return true;
}