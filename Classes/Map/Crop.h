#include<string>
#include "cocos2d.h"

USING_NS_CC;

const int UNCROPPED = 0;
const int GROWING = 1;
const int MATURITY = 2;
const int DEATH = 3;

// �����ũ��������
enum class CropType
{
	NONE,	// �յ�
	POTATO, // ����
	CRON,   // ����
	CABBAGE,// �ײ�
};

class Crop
{
public:
	virtual ~Crop() {};

	virtual void updateGrowth(int deltaTime) = 0;


	// ��������Ƿ�׼�����ջ�
	//virtual bool canHarvest() const = 0;

	// ��ȡ�������ƣ�������ʵ�֣�

	// ��������Ƿ��ѽ�ˮ
	void water();

	// ��������Ƿ���ʩ��
	void fertilize();

	// ��������״̬���������
	int getCropState() const;

protected:
	// ����ɳ��ļ����׶Σ�0��ʾδ����ֲ��1��ʾ�ɳ��У�2��ʾ���죬3��ʾ����
	int growthStage = 0;
	// ��ʾ�Ѿ���ֲ��ʱ��
	int growthTime = 0;
	bool watered = false;		// �Ƿ�ˮ
	bool fertilized = false;	// �Ƿ�ʩ��
	bool isMature = false;		// �Ƿ����
	bool isDisease = false;		// �Ƿ����ܲ���
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