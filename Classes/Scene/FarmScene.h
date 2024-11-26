#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__

#include "cocos2d.h"
#include "../Player/Player.h"
#include "./Map/TileMap.h"

class Farm : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Farm);

private:
	// ��¼��ǰ���µļ�
	std::set<cocos2d::EventKeyboard::KeyCode> keysPressed;

	bool isCollidingWithTile(const Vec2& position) const;

	// ��ʼ����ͼͼ��
	void initLayers();

	// ��ʼ����Ƭ�ڵ�
	void initTileNodes();

	// ������Ƭ�ڵ�
	std::shared_ptr<TileNode> createTileNode(const std::string& layerName, const cocos2d::Vec2& position);


	// ��ʼ�����̼�����
	void initKeyboardListener();

	// ���ݰ��µļ���������Һ͵�ͼ�ƶ��ķ���
	void updateMovement();

<<<<<<< HEAD
	Vec2 worldToTileCoord(const Vec2& worldPosition) const;

	// ��ͼ����
	cocos2d::TMXTiledMap* tmxMap;
	// ������
	cocos2d::TMXLayer* backgroundLayer;
	// ��ײ��
	cocos2d::TMXLayer* collisionLayer=nullptr;
	// ������
	cocos2d::TMXLayer* interactiveLayer;
	// ��Ƭ�ڵ㼯��
	std::vector<std::shared_ptr<TileNode>> tileNodes;
	// ���� houses ��Ա����
	std::vector<House*> houses; 
=======
	// ��ʼ����������
	void initMouseListener();
>>>>>>> origin/master
};

#endif