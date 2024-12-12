#ifndef __SAVE_MANAGE_H__
#define __SAVE_MANAGE_H__
#include <string>
#include <vector>
#include "cocos2d.h"

// 用来保存玩家数据的结构
struct PlayerSaveData {
	float posX;
	float posY;
	float dirX;
	float dirY;
};

// 用来保存地图位置数据的结构
struct MapSaveData {
	float posX;
	float posY;
};

struct SaveData {
	PlayerSaveData playerData;
	MapSaveData mapData;	
};

class SaveManage {
public:
	static SaveManage* getInstance();

	// 保存数据的公用接口
	bool saveGameData();

	// 加载数据的公用接口
	bool loadGameData();

private:
	SaveManage() = default;
	~SaveManage() = default;
	
	std::string SaveManage::serializeToJson(const SaveData& data);

	bool deserializeFromJson(const std::string& jsonStr, SaveData& data);

	static const std::string SAVE_FILE_NAME; // "player_save.json"
};

#endif

