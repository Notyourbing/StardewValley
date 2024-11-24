#ifndef __TOOL_H__
#define __TOOL_H__

#include "cocos2d.h"
#include <string>

class Tool : public cocos2d::Sprite {
public:
	// 初始化工具
	virtual bool init(const std::string& name);

	// 使用工具
	virtual void useTool();

	// 获取工具名称
	std::string getToolName() const {
		return toolName;
	}

protected:
	std::string toolName;
};

#endif
