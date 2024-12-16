#include "SaveManage.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "json/rapidjson.h"
#include "../Player/Player.h"
#include "../Map/FarmMap.h"

USING_NS_CC;

const std::string SaveManage::SAVE_FILE_NAME = "playerSave.json";

// 获取单例实例
SaveManage* SaveManage::getInstance() {
	static SaveManage instance;
	return &instance;
}

// 序列化到json文件
std::string SaveManage::serializeToJson(const SaveData& data) {
	rapidjson::Document doc;
	doc.SetObject();
	auto& alloc = doc.GetAllocator();

	// 存储玩家位置和朝向
	rapidjson::Value playerObj(rapidjson::kObjectType);
	playerObj.AddMember("posX", data.playerData.posX, alloc);
	playerObj.AddMember("posY", data.playerData.posY, alloc);
	playerObj.AddMember("dirX", data.playerData.dirX, alloc);
	playerObj.AddMember("dirY", data.playerData.dirY, alloc);
	doc.AddMember("playerData", playerObj, alloc);

	// 存储地图的位置
	rapidjson::Value mapObj(rapidjson::kObjectType);
	mapObj.AddMember("posX", data.mapData.posX, alloc);
	mapObj.AddMember("posY", data.mapData.posY, alloc);
	doc.AddMember("mapData", mapObj, alloc);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	return buffer.GetString();
}


// 从json文件中反序列化
bool SaveManage::deserializeFromJson(const std::string& jsonStr, SaveData& data) {
	rapidjson::Document doc;
	if (doc.Parse(jsonStr.c_str()).HasParseError()) {
		return false;
	}
	if (!doc.IsObject()) {
		return false;
	}
	// 玩家数据
	if (doc.HasMember("playerData") && doc["playerData"].IsObject()) {
		const rapidjson::Value& playerObj = doc["playerData"];
		if (playerObj.HasMember("posX") && playerObj["posX"].IsNumber()) {
			data.playerData.posX = playerObj["posX"].GetFloat();
		}
		if (playerObj.HasMember("posY") && playerObj["posY"].IsNumber()) {
			data.playerData.posY = playerObj["posY"].GetFloat();
		}
		if (playerObj.HasMember("dirX") && playerObj["dirX"].IsNumber()) {
			data.playerData.dirX = playerObj["dirX"].GetFloat();
		}
		if (playerObj.HasMember("dirY") && playerObj["dirY"].IsNumber()) {
			data.playerData.dirY = playerObj["dirY"].GetFloat();
		}
	}
	if (doc.HasMember("mapData") && doc["mapData"].IsObject()) {
		const rapidjson::Value& mapObj = doc["mapData"];
		if (mapObj.HasMember("posX") && mapObj["posX"].IsNumber()) {
			data.mapData.posX = mapObj["posX"].GetFloat();
		}
		if (mapObj.HasMember("posY") && mapObj["posY"].IsNumber()) {
			data.mapData.posY = mapObj["posY"].GetFloat();
		}
	}


	return true;
}

bool SaveManage::saveGameData() {
	SaveData data;

	// 获取玩家数据
	const Player* player = Player::getInstance();
	data.playerData.posX = player->getPositionX();
	data.playerData.posY = player->getPositionY();
	data.playerData.dirX = player->getLastDirection().x;
	data.playerData.dirY = player->getLastDirection().y;
	
	// 获取地图数据
	const FarmMap* farmMap = FarmMap::getInstance();
	data.mapData.posX = farmMap->getPositionX();
	data.mapData.posY = farmMap->getPositionY();

	// 序列化
	std::string jsonStr = serializeToJson(data);
	std::string path = FileUtils::getInstance()->getWritablePath() + SAVE_FILE_NAME;

	return FileUtils::getInstance()->writeStringToFile(jsonStr, path);
}


bool SaveManage::loadGameData() {
	// 尝试加载存档数据
	std::string path = FileUtils::getInstance()->getWritablePath() + SAVE_FILE_NAME;

	std::string jsonStr = FileUtils::getInstance()->getStringFromFile(path);
	SaveData data;

	bool success = deserializeFromJson(jsonStr, data);
	if (success) {
		Player* player = Player::getInstance();
		player->setPosition(Vec2(data.playerData.posX, data.playerData.posY));
		player->setLastDirection(Vec2(data.playerData.dirX, data.playerData.dirY));
		
		FarmMap* farmMap = FarmMap::getInstance();
		farmMap->setPosition(Vec2(data.mapData.posX, data.mapData.posY));
		return true;
	}

	return false;
}