#include "SaveManage.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "json/rapidjson.h"
#include "../Player/Player.h"

USING_NS_CC;

const std::string SaveManage::SAVE_FILE_NAME = "playerSave.json";

SaveManage* SaveManage::getInstance() {
	static SaveManage instance;
	return &instance;
}

bool SaveManage::savePlayerData(const PlayerSaveData& data) {
	std::string jsonStr = serializeToJson(data);
	std::string path = FileUtils::getInstance()->getDefaultResourceRootPath() + SAVE_FILE_NAME;
	return FileUtils::getInstance()->writeStringToFile(jsonStr, path);
}

bool SaveManage::loadPlayerData(PlayerSaveData& data) {
	std::string path = FileUtils::getInstance()->getDefaultResourceRootPath() + SAVE_FILE_NAME;
	if (!FileUtils::getInstance()->isFileExist(path)) {
		return false;
	}
	std::string jsonStr = FileUtils::getInstance()->getStringFromFile(path);
	return deserializeFromJson(jsonStr, data);
}

std::string SaveManage::serializeToJson(const PlayerSaveData& data) {
	rapidjson::Document doc;
	doc.SetObject();
	auto& alloc = doc.GetAllocator();

	// 存储玩家位置和朝向
	doc.AddMember("posX", data.posX, alloc);
	doc.AddMember("posY", data.posY, alloc);
	doc.AddMember("dirX", data.dirX, alloc);
	doc.AddMember("dirY", data.dirY, alloc);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	return buffer.GetString();
}

bool SaveManage::deserializeFromJson(const std::string& jsonStr, PlayerSaveData& data) {
	rapidjson::Document doc;
	if (doc.Parse(jsonStr.c_str()).HasParseError()) {
		return false;
	}
	if (!doc.IsObject()) {
		return false;
	}
	if (doc.HasMember("posX") && doc["posX"].IsNumber()) {
		data.posX = doc["posX"].GetFloat();
	}
	if (doc.HasMember("posY") && doc["posY"].IsNumber()) {
		data.posY = doc["posY"].GetFloat();
	}
	if (doc.HasMember("dirX") && doc["dirX"].IsNumber()) {
		data.dirX = doc["dirX"].GetFloat();
	}
	if (doc.HasMember("dirY") && doc["dirY"].IsNumber()) {
		data.dirY = doc["dirY"].GetFloat();
	}

	return true;
}

void SaveManage::loadData() {
	// 尝试加载存档数据
	PlayerSaveData data;
	bool loadSuccess = loadPlayerData(data);

	// 如果加载成功，将玩家位置和朝向设置回玩家单例
	if (loadSuccess) {
		auto player = Player::getInstance();
		player->setPosition(cocos2d::Vec2(data.posX, data.posY));
		player->setLastDirection(cocos2d::Vec2(data.dirX, data.dirY));
	}
}