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

class SaveManage {
public:
	static SaveManage* getInstance();

	// 保存玩家数据到文件
	bool savePlayerData(const PlayerSaveData& data);

	// 从玩家中加载玩家数据
	bool loadPlayerData(PlayerSaveData& data);

	// 加载数据的接口
	void loadData();

private:
	SaveManage() = default;
	~SaveManage() = default;
	
	std::string serializeToJson(const PlayerSaveData& data);

	bool deserializeFromJson(const std::string& jsonStr, PlayerSaveData& data);

	static const std::string SAVE_FILE_NAME; // "player_save.json"
};

#endif

