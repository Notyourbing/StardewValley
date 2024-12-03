#include "Tool.h"

class FishingRod : public Tool {
public:
	// 静态创建方法
	static FishingRod* create();

	// 初始化
	bool init();

    // 重载使用工具的函数，执行钓鱼的操作
    void useTool() override;
	void reelInRod();
	static bool isUsed;
};
