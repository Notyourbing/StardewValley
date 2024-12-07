#include "Tool.h"

// 镰刀类
class Scythe : public Tool {
public:
	// 静态创建方法
	static Scythe* create();

	// 初始化
	bool init();

	// 使用工具
	void useItem() override;
};