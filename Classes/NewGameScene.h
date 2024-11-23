#ifndef __NEW_GAME_SCENE_H__
#define __NEW_GAME_SCENE_H__

#include "cocos2d.h"

class NewGame : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// ÊµÏÖ¾²Ì¬create()º¯Êý
	CREATE_FUNC(NewGame);
};
#endif
