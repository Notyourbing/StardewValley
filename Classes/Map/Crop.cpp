#include "Crop.h"

USING_NS_CC;

void Crop::water()
{
	watered = true;
}

void Crop::fertilize()
{
	fertilized = true;
}

int Crop::getCropState() const
{
	return growthStage;
}

Corn::Corn()
{
	// �չ��캯���������Ѿ����г�ʼ����

}


void Corn::updateGrowth(int deltaTime)
{
	
}