#ifndef __FARMMAP_H__
#define __FARMMAP_H__

#include "cocos2d.h"
#include "../Npc/Npc.h"
#include <string>
class FarmMap : public cocos2d::Node {
public:
	// ��ȡ����ʵ��
	static FarmMap* getInstance();

	// ��ʼ����ͼ
	bool init(const std::string& tmxFile);

	//���ͼ����npc
	bool npcInit(const Vec2& position, Npc* npc);

	// ���µ�ͼλ��
	void moveMapByDirection(const cocos2d::Vec2 &direction);
	
	// ��ȡ��ͼ��С
	cocos2d::Size getMapSize() const;

private:
	// ���캯������������˽�л�
	FarmMap();
	~FarmMap();

	// ���ÿ�������͸�ֵ����
	FarmMap(const FarmMap&) = delete;
	FarmMap& operator=(const FarmMap&) = delete;

	// ��Ƭ��ͼ����
	cocos2d::TMXTiledMap* map = nullptr;

	// ��ͼ��ǰ��ƫ��λ��
	cocos2d::Vec2 currentPosition; 

	// ��ͼ��ƫ���ٶ�
	cocos2d::Vec2 velocity;

	// ����ʵ��
	static FarmMap* instance;
};


#endif
