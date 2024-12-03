#include "TileNode.h"


// 土壤的锄地
void Soil::hoe() {
	isHoed = true;
	this->updateGID(64);
}

// 土壤的浇水
void Soil::water() {
	if (isHoed ) {
		// 判断这个土壤位置是否有作物
		if (crop == nullptr) {
			this->updateGID(96);
		}
		// 更新土壤的状态
		waterLevel = 10;
		isWatered = true;
	}
}

// 土壤的施肥
void Soil::fertilize() {
	fertilizeLevel = 10;
	isFertilized = true;
}

// 土壤的交互功能的重载
void Soil::interact(std::string toolName) {
	
	if (toolName=="hoe") {						// 如果是锄头，那么进行锄地
		hoe();
	}
	else if (toolName == "kettle") {			// 如果是水壶，那么进行浇水
		water();
	}
	else if (toolName == "fertilizer") {		// 如果是肥料，那么进行施肥
		fertilize();
	}
	// 接下来完成各种种子的重建
}