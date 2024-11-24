#include "TileMap.h"
#include "Crop.h"

USING_NS_CC;

void TileNode::setType(TileType newType)
{
	type = newType;
}

void Soil::plow()
{
	if (!isPlowed) {
		isPlowed = true;

	}
}

void Soil::plantCrop(CropType cropType)
{
	if (isPlowed && !currentCrop) {
		switch (cropType) {
		case CropType::POTATO:
			currentCrop = new Potato();
			break;
		case CropType::CRON:
			currentCrop = new Corn();
			break;
		case CropType::CABBAGE:
			currentCrop = new Cabbage();
			break;
		}
	}
	isWatered = false;  // 新种植的作物需要浇水
	isFertilized = false;  // 新种植的作物需要施肥
}

void Soil::updateCropGrowth(int deltaTime) {
	if (currentCrop) {
		currentCrop->updateGrowth(deltaTime);

		if (currentCrop->getCropState() == DEATH) {
			// 作物死亡后需要重新处理
			delete currentCrop;
			currentCrop = nullptr;
			health -= 20;  // 作物死亡后土地健康下降
		}
	}
}

bool Soil::harvestCrop() {
	if (currentCrop && currentCrop->getCropState() == MATURITY) {
		// 收获作物
		delete currentCrop;  // 释放作物指针
		currentCrop = nullptr;
		//添加其余操作
		return true;
	}
	return false;
}

void Soil::water()
{
	if (currentCrop && !isWatered) {
		isWatered = true;
		droughtTime = 0;
	}
}

void Soil::fertilize()
{
	if (currentCrop && isFertilized) {
		isFertilized = true;
	}
}

void Tree::interact()
{
	if (!isCut) {
		isCut = true;
		//CCLOG("Tree has been cut down, turning into Tree Stump.");

		// 替换为树桩
		auto stump = new TreeStump();
		stump->setPosition(this->getPosition());  // 保留当前位置
		this->getParent()->addChild(stump);      // 将树桩添加到图层
		this->removeFromParent();                // 删除树
	}
}

void TreeStump::interact()
{
	if (!isCut) {
		isCut = true;
		//CCLOG("Tree Stump has been removed, turning into Soil.");

		// 替换为土壤
		auto soil = new Soil();
		soil->setPosition(this->getPosition());  // 保留当前位置
		this->getParent()->addChild(soil);      // 将土壤添加到图层
		this->removeFromParent();               // 删除树桩
	}
}

void Flower::interact()
{
	if (!isCut) {
		isCut = true;
		//CCLOG("Flower has been removed, turning into Soil.");

		// 替换为土壤
		auto soil = new Soil();
		soil->setPosition(this->getPosition());  // 保留当前位置
		this->getParent()->addChild(soil);      // 将土壤添加到图层
		this->removeFromParent();               // 删除花
	}
}