#include "Tool.h"

USING_NS_CC;

Tool* Tool::create(const std::string& name) {
	Tool* tool = new (std::nothrow) Tool();
	if (tool && tool->init(name)) {
		tool->autorelease();
		return tool;
	}
	CC_SAFE_DELETE(tool);
	return nullptr;
}

void Tool::useTool() {}

bool Tool::init(const std::string& name) {
	toolName = name;
	if (!Sprite::initWithFile("tools/" + toolName + ".png")) {
		return false;
	}

	return true;
}