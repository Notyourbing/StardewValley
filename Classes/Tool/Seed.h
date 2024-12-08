#ifndef __SEED_H__
#define __SEED_H__

#include "Tool.h"
#include "cocos2d.h"
#include <string>

enum class SeedType {
	AppleSeed,
	CornSeed,
	CarrotSeed
};

// Seed类：继承自工具类，表示物品中的苹果种子
class Seed : public Tool {
private:
	std::string seedName;
public:
	// 初始化种子
	bool init(const SeedType& seedType);

	// 使用工具
	void useItem() override;
};

// AppleSeed类：继承自Seed类，表示苹果种子
class AppleSeed :public Seed {
public:
	// 静态创建方法
	static AppleSeed* create();
};

// CornSeed类：继承自Seed类，表示玉米种子
class CornSeed : public Seed {
public:
	// 静态创建方法
	static CornSeed* create();
};

// CarrotSeed类：继承自Seed类，表示胡萝卜种子
class CarrotSeed :public Seed {
public:
	// 静态创建方法
	static CarrotSeed* create();
};

#endif
