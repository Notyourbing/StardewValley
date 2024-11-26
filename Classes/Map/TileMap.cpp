#include "TileMap.h"


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
			//currentCrop = new Potato();
			break;
		case CropType::CRON:
			//currentCrop = new Corn();
			break;
		case CropType::CABBAGE:
			//currentCrop = new Cabbage();
			break;
		}
	}
	isWatered = false;  // ����ֲ��������Ҫ��ˮ
	isFertilized = false;  // ����ֲ��������Ҫʩ��
}

void Soil::updateCropGrowth(int deltaTime) {
	if (currentCrop) {
		currentCrop->updateGrowth(deltaTime);

		if (currentCrop->getCropState() == DEATH) {
			// ������������Ҫ���´���
			delete currentCrop;
			currentCrop = nullptr;
			health -= 20;  // �������������ؽ����½�
		}
	}
}

bool Soil::harvestCrop() {
	if (currentCrop && currentCrop->getCropState() == MATURITY) {
		// �ջ�����
		delete currentCrop;  // �ͷ�����ָ��
		currentCrop = nullptr;
		//����������
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

		// �滻Ϊ��׮
		auto stump = new TreeStump();
		stump->setPosition(this->getPosition());  // ������ǰλ��
		this->getParent()->addChild(stump);      // ����׮��ӵ�ͼ��
		this->removeFromParent();                // ɾ����
	}
}

void TreeStump::interact()
{
	if (!isCut) {
		isCut = true;
		//CCLOG("Tree Stump has been removed, turning into Soil.");

		// �滻Ϊ����
		//auto soil = new Soil();
		//soil->setPosition(this->getPosition());  // ������ǰλ��
		//this->getParent()->addChild(soil);      // ��������ӵ�ͼ��
		//this->removeFromParent();               // ɾ����׮
	}
}

void Flower::interact()
{
	if (!isCut) {
		isCut = true;
		//CCLOG("Flower has been removed, turning into Soil.");

		// �滻Ϊ����
		//auto soil = new Soil();
		//soil->setPosition(this->getPosition());  // ������ǰλ��
		//this->getParent()->addChild(soil);      // ��������ӵ�ͼ��
		//this->removeFromParent();               // ɾ����
	}
}