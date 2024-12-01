#ifndef __TOOL_H__
#define __TOOL_H__

#include "cocos2d.h"
#include "../Map/FarmMap.h"
#include <string>

// 工具类
class Tool : public cocos2d::Sprite {
public:
	// 静态创建方法
	static Tool* create(const std::string& name);

	// 初始化
	virtual bool init(const std::string& name);

	// 使用工具
	virtual void useTool();

	// 获取工具名称
	std::string getToolName() {
		return toolName;
	}
	// 工具名称
	std::string toolName;
protected:

};

#endif
