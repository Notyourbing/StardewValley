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

std::string SaveManage::serializeToJson(const PlayerSaveData& data) {
	rapidjson::Document doc;
	doc.SetObject();
	auto& alloc = doc.GetAllocator();

	// 存储玩家位置和朝向
	doc.AddMember("posX", data.posX, alloc);
	doc.AddMember("posY", data.posY, alloc);
	doc.AddMember("direction", data.direction, alloc);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	return buffer.GetString();
}