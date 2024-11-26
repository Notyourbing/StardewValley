#include "Axe.h"
#include "../Player/Player.h"
USING_NS_CC;

Axe* Axe::create() {
	Axe* axe = new (std::nothrow) Axe();
	if (axe && axe->init()) {
		axe->autorelease();
		return axe;
	}
	CC_SAFE_DELETE(axe);
	return nullptr;
}

bool Axe::init() {
	// ���û���ĳ�ʼ������
	return Tool::init("axe");
}

void Axe::useTool() {
	// ���Ÿ�ͷʹ�ö���
	auto rotationAction = RotateBy::create(0.2f, 90); // ˳ʱ����ת��ʮ�ȣ���ʱ0.2��
	auto resetRotationAction = RotateBy::create(0.2f, -90); // �ظ���ʼ�Ƕ�
	
	// ��������
	auto sequence = Sequence::create(
		rotationAction,
		CallFunc::create([=]() {
			CCLOG("Using axe at player position (%f, %f)", getPositionX(), getPositionY());
			// todo ��������߼����������Ƿ�����Ŀ��
			}),
		resetRotationAction,
		nullptr
	);

	this->runAction(sequence);
}