#include "SaveManage.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "json/rapidjson.h"

USING_NS_CC;

const std::string SaveManage::SAVE_FILE_NAME = "playerSave.json";

SaveManage* SaveManage::getInstance() {
	static SaveManage instance;
	return &instance;
}

bool SaveManage::savePlayerData(const PlayerSaveData& data) {
	std::string jsonStr = serializeToJson(data);
	std::string path = FileUtils::getInstance()->getWritablePath() + SAVE_FILE_NAME;
	return FileUtils::getInstance()->writeStringToFile(jsonStr, path);
}

bool SaveManage::loadPlayerData(PlayerSaveData& data) {
	std::string path = FileUtils::getInstance()->getWritablePath() + SAVE_FILE_NAME;
	if (!FileUtils::getInstance()->isFileExist(path)) {
		CCLOG("Save file does not exist!");
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
		CCLOG("JSON parse error!");
		return false;
	}
	if (!doc.IsObject()) {
		CCLOG("JSON is not an object!");
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