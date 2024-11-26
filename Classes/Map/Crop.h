#include<string>
#include "cocos2d.h"

USING_NS_CC;

const int UNCROPPED = 0;
const int GROWING = 1;
const int MATURITY = 2;
const int DEATH = 3;

// 定义的农作物种类
enum class CropType
{
	NONE,	// 空地
	POTATO, // 土豆
	CRON,   // 玉米
	CABBAGE,// 白菜
};

class Crop
{
public:
	virtual ~Crop() {};

	virtual void updateGrowth(int deltaTime) = 0;


	// 检查作物是否准备好收获
	//virtual bool canHarvest() const = 0;

	// 获取作物名称（由子类实现）

	// 标记作物是否已浇水
	void water();

	// 标记作物是否已施肥
	void fertilize();

	// 返回作物状态（成熟与否）
	int getCropState() const;

protected:
	// 作物成长的几个阶段：0表示未被种植，1表示成长中，2表示成熟，3表示死亡
	int growthStage = 0;
	// 表示已经种植的时间
	int growthTime = 0;
	bool watered = false;		// 是否浇水
	bool fertilized = false;	// 是否施肥
	bool isMature = false;		// 是否成熟
	bool isDisease = false;		// 是否遭受病害
};

class Potato : public Crop
{
public:
	Potato();
	void updateGrowth(int deltaTime) override;
	//bool canHarvest() const override;

private:
	int maturityTime = 3;
};

class Corn : public Crop
{
public:
	Corn();
	void updateGrowth(int deltaTime) override;
	//bool canHarvest() const override;

private:
	int maturityTime = 4;
};

class Cabbage : public Crop
{
public:
	Cabbage();
	void updateGrowth(int deltaTime) override;
	//bool canHarvest() const override;

private:
	int maturityTime = 5;
};