#ifndef __CONSTANT_H
#define __CONSTANT_H
#include "cocos2d.h"
#include <string>
#include <array>
#include <unordered_map>

// 资源路径
namespace ResPath {
	// 背景框、按钮、字体
	constexpr char BACKGROUND_IMAGE[] = "icon/background.png";
	constexpr char NEW_GAME_ITEM[] = "icon/newGameButton.png";
	constexpr char NEW_GAME_ON_ITEM[] = "icon/newGameButtonOn.png";
	constexpr char LOAD_GAME_ITEM[] = "icon/loadGameButton.png";
	constexpr char LOAD_GAME_ON_ITEM[] = "icon/loadGameButtonOn.png";
	constexpr char COOPERATION_ITEM[] = "icon/cooperationButton.png";
	constexpr char COOPERATION_ON_ITEM[] = "icon/cooperationButtonOn.png";
	constexpr char EXIT_ITEM[] = "icon/exitButton.png";
	constexpr char EXIT_ON_ITEM[] = "icon/exitButtonOn.png";
	constexpr char TITLE[] = "icon/title.png";
	constexpr char FONT_TTF[] = "fonts/Marker Felt.ttf";
	constexpr char FONT_ARIAL[] = "fonts/arial.ttf";
	constexpr char COOP_BACKGROUND[] = "icon/coopBackground.png";
	constexpr char COOP_PANEL[] = "icon/cooperationPanel.png";
	constexpr char NAME_BAR[] = "icon/nameBar.png";
	constexpr char OK_BUTTON[] = "icon/okButton.png";
	constexpr char OK_BUTTON_ON[] = "icon/okButtonOn.png";
	constexpr char BACK_BUTTON[] = "icon/backButton.png";
	constexpr char UP_ARROW[] = "icon/upArrow.png";
	constexpr char DOWN_ARROW[] = "icon/downArrow.png";
	constexpr char CLOSE_BUTTON_NORMAL[] = "CloseNormal.png";
	constexpr char CLOSE_BUTTON_HOVER[] = "CloseHover.png";
	constexpr char BAG_BACKGROUND[] = "icon/bagBackground.png";
	constexpr char SKILL_BACKGROUND[] = "icon/allScreenButton.png";
	constexpr char SKILL_CLOSE[] = "icon/closeButton.png";
	constexpr char SKILL_CLOSE_ON[] = "icon/closeButtonOn.png";

	// Axe 动画帧
	constexpr char AXE_RIGHT_1[] = "tools/axe/rightUseAxe1.png";
	constexpr char AXE_RIGHT_2[] = "tools/axe/rightUseAxe2.png";
	constexpr char AXE_RIGHT_3[] = "tools/axe/rightUseAxe3.png";
	constexpr char AXE_LEFT_1[] = "tools/axe/leftUseAxe1.png";
	constexpr char AXE_LEFT_2[] = "tools/axe/leftUseAxe2.png";
	constexpr char AXE_LEFT_3[] = "tools/axe/leftUseAxe3.png";
	constexpr char AXE_UP_1[] = "tools/axe/upUseAxe1.png";
	constexpr char AXE_UP_2[] = "tools/axe/upUseAxe2.png";
	constexpr char AXE_UP_3[] = "tools/axe/upUseAxe3.png";
	constexpr char AXE_DOWN_1[] = "tools/axe/downUseAxe1.png";
	constexpr char AXE_DOWN_2[] = "tools/axe/downUseAxe2.png";
	constexpr char AXE_DOWN_3[] = "tools/downUseAxe3.png";

	// Hoe 动画帧路径
	constexpr char HOE_RIGHT_1[] = "tools/hoe/rightUseHoe1.png";
	constexpr char HOE_RIGHT_2[] = "tools/hoe/rightUseHoe2.png";
	constexpr char HOE_RIGHT_3[] = "tools/hoe/rightUseHoe3.png";
	constexpr char HOE_LEFT_1[] = "tools/hoe/leftUseHoe1.png";
	constexpr char HOE_LEFT_2[] = "tools/hoe/leftUseHoe2.png";
	constexpr char HOE_LEFT_3[] = "tools/hoe/leftUseHoe3.png";
	constexpr char HOE_UP_1[] = "tools/hoe/upUseHoe1.png";
	constexpr char HOE_UP_2[] = "tools/hoe/upUseHoe2.png";
	constexpr char HOE_UP_3[] = "tools/hoe/upUseHoe3.png";
	constexpr char HOE_DOWN_1[] = "tools/hoe/downUseHoe1.png";
	constexpr char HOE_DOWN_2[] = "tools/hoe/downUseHoe2.png";

	// Pickaxe 动画帧路径
	constexpr char PICKAXE_RIGHT_1[] = "tools/pickaxe/rightUsePickaxe1.png";
	constexpr char PICKAXE_RIGHT_2[] = "tools/pickaxe/rightUsePickaxe2.png";
	constexpr char PICKAXE_RIGHT_3[] = "tools/pickaxe/rightUsePickaxe3.png";
	constexpr char PICKAXE_LEFT_1[] = "tools/pickaxe/leftUsePickaxe1.png";
	constexpr char PICKAXE_LEFT_2[] = "tools/pickaxe/leftUsePickaxe2.png";
	constexpr char PICKAXE_LEFT_3[] = "tools/pickaxe/leftUsePickaxe3.png";
	constexpr char PICKAXE_UP_1[] = "tools/pickaxe/upUsePickaxe1.png";
	constexpr char PICKAXE_UP_2[] = "tools/pickaxe/upUsePickaxe2.png";
	constexpr char PICKAXE_DOWN_1[] = "tools/pickaxe/downUsePickaxe1.png";
	constexpr char PICKAXE_DOWN_2[] = "tools/pickaxe/downUsePickaxe2.png";
	constexpr char PICKAXE_DOWN_3[] = "tools/pickaxe/downUsePickaxe3.png";

	// Scythe 动画帧路径
	constexpr char SCYTHE_RIGHT_1[] = "tools/scythe/rightUseScythe1.png";
	constexpr char SCYTHE_RIGHT_2[] = "tools/scythe/rightUseScythe2.png";
	constexpr char SCYTHE_RIGHT_3[] = "tools/scythe/rightUseScythe3.png";
	constexpr char SCYTHE_LEFT_1[] = "tools/scythe/leftUseScythe1.png";
	constexpr char SCYTHE_LEFT_2[] = "tools/scythe/leftUseScythe2.png";
	constexpr char SCYTHE_LEFT_3[] = "tools/scythe/leftUseScythe3.png";
	constexpr char SCYTHE_UP_1[] = "tools/scythe/upUseScythe1.png";
	constexpr char SCYTHE_UP_2[] = "tools/scythe/upUseScythe2.png";
	constexpr char SCYTHE_UP_3[] = "tools/scythe/upUseScythe3.png";
	constexpr char SCYTHE_DOWN_1[] = "tools/scythe/downUseScythe1.png";
	constexpr char SCYTHE_DOWN_2[] = "tools/scythe/downUseScythe2.png";
	constexpr char SCYTHE_DOWN_3[] = "tools/scythe/downUseScythe3.png";

	//fishing
	constexpr char DOWN_FISHING_OUT_1[] = "tools/fishing/downOut1.png";
	constexpr char DOWN_FISHING_OUT_2[] = "tools/fishing/downOut2.png";
	constexpr char DOWN_FISHING_OUT_3[] = "tools/fishing/downOut3.png";
	constexpr char DOWN_FISHING_OUT_4[] = "tools/fishing/downOut4.png";
	constexpr char DOWN_FISHING_WAITING_1[] = "tools/fishing/downWaiting1.png";
	constexpr char DOWN_FISHING_WAITING_2[] = "tools/fishing/downWaiting2.png";
	constexpr char DOWN_FISHING_IN_1[] = "tools/fishing/downIn1.png";
	constexpr char DOWN_FISHING_IN_2[] = "tools/fishing/downIn2.png";

	constexpr char UP_FISHING_OUT_1[] = "tools/fishing/upOut1.png";
	constexpr char UP_FISHING_OUT_2[] = "tools/fishing/upOut2.png";
	constexpr char UP_FISHING_OUT_3[] = "tools/fishing/upOut3.png";
	constexpr char UP_FISHING_WAITING_1[] = "tools/fishing/upWaiting1.png";
	constexpr char UP_FISHING_WAITING_2[] = "tools/fishing/upWaiting2.png";
	constexpr char UP_FISHING_IN_1[] = "tools/fishing/upIn1.png";
	constexpr char UP_FISHING_IN_2[] = "tools/fishing/upIn2.png";
	constexpr char UP_FISHING_IN_3[] = "tools/fishing/upIn3.png";

	constexpr char LEFT_FISHING_OUT_1[] = "tools/fishing/leftOut1.png";
	constexpr char LEFT_FISHING_OUT_2[] = "tools/fishing/leftOut2.png";
	constexpr char LEFT_FISHING_OUT_3[] = "tools/fishing/leftOut3.png";
	constexpr char LEFT_FISHING_OUT_4[] = "tools/fishing/leftOut4.png";
	constexpr char LEFT_FISHING_WAITING_1[] = "tools/fishing/leftWaiting1.png";
	constexpr char LEFT_FISHING_WAITING_2[] = "tools/fishing/leftWaiting2.png";
	constexpr char LEFT_FISHING_IN_1[] = "tools/fishing/leftIn1.png";
	constexpr char LEFT_FISHING_IN_2[] = "tools/fishing/leftIn2.png";
	constexpr char LEFT_FISHING_IN_3[] = "tools/fishing/leftIn3.png";
	constexpr char LEFT_FISHING_IN_4[] = "tools/fishing/leftIn4.png";
	constexpr char LEFT_FISHING_IN_5[] = "tools/fishing/leftIn5.png";

	constexpr char RIGHT_FISHING_OUT_1[] = "tools/fishing/rightOut1.png";
	constexpr char RIGHT_FISHING_OUT_2[] = "tools/fishing/rightOut2.png";
	constexpr char RIGHT_FISHING_OUT_3[] = "tools/fishing/rightOut3.png";
	constexpr char RIGHT_FISHING_OUT_4[] = "tools/fishing/rightOut4.png";
	constexpr char RIGHT_FISHING_WAITING_1[] = "tools/fishing/rightWaiting1.png";
	constexpr char RIGHT_FISHING_WAITING_2[] = "tools/fishing/rightWaiting2.png";
	constexpr char RIGHT_FISHING_IN_1[] = "tools/fishing/rightIn1.png";
	constexpr char RIGHT_FISHING_IN_2[] = "tools/fishing/rightIn2.png";
	constexpr char RIGHT_FISHING_IN_3[] = "tools/fishing/rightIn3.png";
	constexpr char RIGHT_FISHING_IN_4[] = "tools/fishing/rightIn4.png";
	constexpr char RIGHT_FISHING_IN_5[] = "tools/fishing/rightIn5.png";

	//KETTLE
	constexpr char KETTLE_RIGHT_1[] = "tools/kettle/rightUseKettle1.png";
	constexpr char KETTLE_RIGHT_2[] = "tools/kettle/rightUseKettle2.png";
	constexpr char KETTLE_RIGHT_3[] = "tools/kettle/rightUseKettle3.png";
	constexpr char KETTLE_RIGHT_4[] = "tools/kettle/rightUseKettle4.png";
	constexpr char KETTLE_RIGHT_5[] = "tools/kettle/rightUseKettle5.png";
	constexpr char KETTLE_LEFT_1[] = "tools/kettle/leftUseKettle1.png";
	constexpr char KETTLE_LEFT_2[] = "tools/kettle/leftUseKettle2.png";
	constexpr char KETTLE_LEFT_3[] = "tools/kettle/leftUseKettle3.png";
	constexpr char KETTLE_LEFT_4[] = "tools/kettle/leftUseKettle4.png";
	constexpr char KETTLE_LEFT_5[] = "tools/kettle/leftUseKettle5.png";
	constexpr char KETTLE_UP_1[] = "tools/kettle/upUseKettle1.png";
	constexpr char KETTLE_UP_2[] = "tools/kettle/upUseKettle2.png";
	constexpr char KETTLE_UP_3[] = "tools/kettle/upUseKettle3.png";
	constexpr char KETTLE_UP_4[] = "tools/kettle/upUseKettle4.png";
	constexpr char KETTLE_DOWN_1[] = "tools/kettle/downUseKettle1.png";
	constexpr char KETTLE_DOWN_2[] = "tools/kettle/downUseKettle2.png";
	constexpr char KETTLE_DOWN_3[] = "tools/kettle/downUseKettle3.png";

	// 玩家站立帧
	constexpr char STAND_RIGHT[] = "playerWalkImages/standRight.png";
	constexpr char STAND_LEFT[] = "playerWalkImages/standLeft.png";
	constexpr char STAND_UP[] = "playerWalkImages/standUp.png";
	constexpr char STAND_DOWN[] = "playerWalkImages/standDown.png";
}
//工具图片
constexpr char AXE[] = "tools/axe.png";
constexpr char FISHING_ROD[] = "tools/fishingRod.png";
constexpr char HOE[] = "tools/hoe.png";
constexpr char PICKAXE[] = "tools/pickaxe.png";
constexpr char SCYTHE[] = "tools/scythe.png";
constexpr char KETTLE[] = "tools/kettle.png";

// 工具动画帧的裁剪区域
namespace ToolRects {
	// Axe 动画帧 Rect
	const cocos2d::Rect AXE_RIGHT_1(0, 0, 100, 183);
	const cocos2d::Rect AXE_RIGHT_2(0, 0, 201, 183);
	const cocos2d::Rect AXE_RIGHT_3(0, 0, 165, 164);
	const cocos2d::Rect AXE_LEFT_1(0, 0, 100, 183);
	const cocos2d::Rect AXE_LEFT_2(0, 0, 201, 183);
	const cocos2d::Rect AXE_LEFT_3(0, 0, 165, 164);
	const cocos2d::Rect AXE_UP_1(0, 0, 85, 200);
	const cocos2d::Rect AXE_UP_2(0, 0, 81, 127);
	const cocos2d::Rect AXE_UP_3(0, 0, 75, 145);
	const cocos2d::Rect AXE_DOWN_1(0, 0, 74, 185);
	const cocos2d::Rect AXE_DOWN_2(0, 0, 75, 127);
	const cocos2d::Rect AXE_DOWN_3(0, 0, 77, 109);

	// Hoe 动画帧 Rect
	const cocos2d::Rect HOE_RIGHT_1(0, 0, 128, 180);
	const cocos2d::Rect HOE_RIGHT_2(0, 0, 169, 184);
	const cocos2d::Rect HOE_RIGHT_3(0, 0, 206, 271);
	const cocos2d::Rect HOE_LEFT_1(0, 0, 128, 180);
	const cocos2d::Rect HOE_LEFT_2(0, 0, 169, 184);
	const cocos2d::Rect HOE_LEFT_3(0, 0, 206, 271);
	const cocos2d::Rect HOE_UP_1(0, 0, 89, 190);
	const cocos2d::Rect HOE_UP_2(0, 0, 83, 190);
	const cocos2d::Rect HOE_UP_3(0, 0, 97, 145);
	const cocos2d::Rect HOE_DOWN_1(0, 0, 70, 196);
	const cocos2d::Rect HOE_DOWN_2(0, 0, 70, 195);

	// Pickaxe 动画帧 Rect
	const cocos2d::Rect PICKAXE_RIGHT_1(0, 0, 131, 198);
	const cocos2d::Rect PICKAXE_RIGHT_2(0, 0, 95, 193);
	const cocos2d::Rect PICKAXE_RIGHT_3(0, 0, 267, 183);
	const cocos2d::Rect PICKAXE_LEFT_1(0, 0, 131, 198);
	const cocos2d::Rect PICKAXE_LEFT_2(0, 0, 95, 193);
	const cocos2d::Rect PICKAXE_LEFT_3(0, 0, 267, 183);
	const cocos2d::Rect PICKAXE_UP_1(0, 0, 98, 261);
	const cocos2d::Rect PICKAXE_UP_2(0, 0, 93, 146);
	const cocos2d::Rect PICKAXE_DOWN_1(0, 0, 86, 270);
	const cocos2d::Rect PICKAXE_DOWN_2(0, 0, 81, 203);
	const cocos2d::Rect PICKAXE_DOWN_3(0, 0, 63, 132);

	// Scythe动画帧
	const cocos2d::Rect SCYTHE_RIGHT_1(0, 0, 105, 182);
	const cocos2d::Rect SCYTHE_RIGHT_2(0, 0, 208, 155);
	const cocos2d::Rect SCYTHE_RIGHT_3(0, 0, 159, 210);
	const cocos2d::Rect SCYTHE_LEFT_1(0, 0, 105, 182);
	const cocos2d::Rect SCYTHE_LEFT_2(0, 0, 203, 151);
	const cocos2d::Rect SCYTHE_LEFT_3(0, 0, 178, 167);
	const cocos2d::Rect SCYTHE_UP_1(0, 0, 163, 146);
	const cocos2d::Rect SCYTHE_UP_2(0, 0, 98, 202);
	const cocos2d::Rect SCYTHE_UP_3(0, 0, 178, 167);
	const cocos2d::Rect SCYTHE_DOWN_1(0, 0, 176, 141);
	const cocos2d::Rect SCYTHE_DOWN_2(0, 0, 162, 173);
	const cocos2d::Rect SCYTHE_DOWN_3(0, 0, 290, 186);

	// fishing
	const cocos2d::Rect DOWN_FISHING_OUT_1(0, 0, 67, 142);
	const cocos2d::Rect DOWN_FISHING_OUT_2(0, 0, 92, 432);
	const cocos2d::Rect DOWN_FISHING_OUT_3(0, 0, 71, 217);
	const cocos2d::Rect DOWN_FISHING_OUT_4(0, 0, 70, 163);
	const cocos2d::Rect DOWN_FISHING_WAITING_1(0, 0, 102, 377);
	const cocos2d::Rect DOWN_FISHING_WAITING_2(0, 0, 94, 321);
	const cocos2d::Rect DOWN_FISHING_IN_1(0, 0, 70, 174);
	const cocos2d::Rect DOWN_FISHING_IN_2(0, 0, 71, 217);

	const cocos2d::Rect LEFT_FISHING_OUT_1(0, 0, 212, 215);
	const cocos2d::Rect LEFT_FISHING_OUT_2(0, 0, 181, 267);
	const cocos2d::Rect LEFT_FISHING_OUT_3(0, 0, 245, 371);
	const cocos2d::Rect LEFT_FISHING_OUT_4(0, 0, 303, 189);
	const cocos2d::Rect LEFT_FISHING_WAITING_1(0, 0, 284, 160);
	const cocos2d::Rect LEFT_FISHING_WAITING_2(0, 0, 284, 165);
	const cocos2d::Rect LEFT_FISHING_IN_1(0, 0, 247, 181);
	const cocos2d::Rect LEFT_FISHING_IN_2(0, 0, 188, 195);
	const cocos2d::Rect LEFT_FISHING_IN_3(0, 0, 175, 178);
	const cocos2d::Rect LEFT_FISHING_IN_4(0, 0, 197, 195);
	const cocos2d::Rect LEFT_FISHING_IN_5(0, 0, 201, 175);

	const cocos2d::Rect RIGHT_FISHING_OUT_1(0, 0, 212, 215);
	const cocos2d::Rect RIGHT_FISHING_OUT_2(0, 0, 181, 267);
	const cocos2d::Rect RIGHT_FISHING_OUT_3(0, 0, 245, 371);
	const cocos2d::Rect RIGHT_FISHING_OUT_4(0, 0, 303, 189);
	const cocos2d::Rect RIGHT_FISHING_WAITING_1(0, 0, 284, 160);
	const cocos2d::Rect RIGHT_FISHING_WAITING_2(0, 0, 284, 165);
	const cocos2d::Rect RIGHT_FISHING_IN_1(0, 0, 247, 181);
	const cocos2d::Rect RIGHT_FISHING_IN_2(0, 0, 188, 195);
	const cocos2d::Rect RIGHT_FISHING_IN_3(0, 0, 175, 178);
	const cocos2d::Rect RIGHT_FISHING_IN_4(0, 0, 197, 195);
	const cocos2d::Rect RIGHT_FISHING_IN_5(0, 0, 201, 175);

	const cocos2d::Rect UP_FISHING_OUT_1(0, 0, 70, 163);
	const cocos2d::Rect UP_FISHING_OUT_2(0, 0, 91, 268);
	const cocos2d::Rect UP_FISHING_OUT_3(0, 0, 88, 259);
	const cocos2d::Rect UP_FISHING_WAITING_1(0, 0, 91, 219);
	const cocos2d::Rect UP_FISHING_WAITING_2(0, 0, 75, 225);
	const cocos2d::Rect UP_FISHING_IN_1(0, 0, 102, 249);
	const cocos2d::Rect UP_FISHING_IN_2(0, 0, 97, 270);
	const cocos2d::Rect UP_FISHING_IN_3(0, 0, 70, 163);

	//kettle
	const cocos2d::Rect KETTLE_RIGHT_1(0, 0, 176, 150);
	const cocos2d::Rect KETTLE_RIGHT_2(0, 0, 195, 141);
	const cocos2d::Rect KETTLE_RIGHT_3(0, 0, 162, 166);
	const cocos2d::Rect KETTLE_RIGHT_4(0, 0, 156, 182);
	const cocos2d::Rect KETTLE_RIGHT_5(0, 0, 155, 177);
	const cocos2d::Rect KETTLE_LEFT_1(0, 0, 176, 150);
	const cocos2d::Rect KETTLE_LEFT_2(0, 0, 195, 141);
	const cocos2d::Rect KETTLE_LEFT_3(0, 0, 162, 166);
	const cocos2d::Rect KETTLE_LEFT_4(0, 0, 156, 182);
	const cocos2d::Rect KETTLE_LEFT_5(0, 0, 155, 177);
	const cocos2d::Rect KETTLE_UP_1(0, 0, 106, 130);
	const cocos2d::Rect KETTLE_UP_2(0, 0, 92, 182);
	const cocos2d::Rect KETTLE_UP_3(0, 0, 122, 188);
	const cocos2d::Rect KETTLE_UP_4(0, 0, 118, 149);
	const cocos2d::Rect KETTLE_DOWN_1(0, 0, 95, 131);
	const cocos2d::Rect KETTLE_DOWN_2(0, 0, 91, 160);
	const cocos2d::Rect KETTLE_DOWN_3(0, 0, 163, 235);

	// 玩家站立帧 Rect
	const cocos2d::Rect STAND_RIGHT(0, 0, 70, 120);
	const cocos2d::Rect STAND_LEFT(0, 0, 70, 120);
	const cocos2d::Rect STAND_UP(0, 0, 70, 120);
	const cocos2d::Rect STAND_DOWN(0, 0, 70, 120);
}

// 全局窗口大小
const cocos2d::Size WINSIZE(1280.0f, 720.0f);

// 全局移动速度
constexpr float MAP_MOVE_SPEED = 300.0f;			// 地图移动速度
constexpr float PLAYER_MOVE_SPEED = 300.0f;			// 玩家移动速度

// WecomScene
constexpr float MENU_ITEM_INTERVAL = 24.0f;			// 菜单项之间的间距
constexpr float WELCOME_LABEL_SIZE = 24.0f;			// Weclome标签字体大小
const cocos2d::Color3B PURPUL(15, 13, 38);			// 紫色

// NewGameScene
constexpr char DEFAULT_PLAYER_NAME[] = "Kuanye";	// 默认玩家名字
constexpr float OK_BUTTON_POSITION_X_RATIO = 0.7f;	// OK按钮X轴位置比例
constexpr float OK_BUTTON_POSITION_Y_RATIO = 0.3f;	// OK按钮Y轴位置比例
constexpr float BACK_BUTTON_PADDING_RIGHT = 40.0f;	// 返回按钮右边距
constexpr float BACK_BUTTON_PADDING_BOTTOM = 20.0f; // 返回按钮下边距

// CooperationScene
constexpr float ARROW_BUTTON_PADDING = 40.0f;		// 翻页按钮的右边距
constexpr float UP_BUTTON_OFFSET_Y = 50.0f;			// 向上箭头按钮Y轴偏移
constexpr float DOWN_BUTTON_OFFSET_Y = -50.0f;		// 向下箭头按钮Y轴偏移
constexpr float MOVE_BY_DISTANCE = 50.0f;			// 翻页按钮移动的像素距离
constexpr char COOP_TEXT_CONTENT[] = "Connecting to online services...";

//对话框
constexpr char DIALOGUE_BACKGROUND[] = "npcImages/dialogueBox.png";
constexpr std::array<const char*, 4> options = {
	"Relationship between us",
	"Any tasks?",
	"Community Celebrations",
	"I have a gift for you"
};
// NPC
struct NpcInfo {
	const std::string name;
	const std::string birthdate;
	const int friendshipLevel;
	const std::vector<std::string> gifts;
	const std::vector<std::string> dislikes;
	const std::vector<std::string> dialogues;
	const std::string image;
};

const NpcInfo WIZARD_INFO = {
	"Wizard Yuuu",
	"Fall 5",
	90,
	{ "Magic Essence", "Diamond" },
	{ "Milk" },
	{ "Get out of my way.", "It's nice to see you here.", "I like to spend time with you." },
	"npcImages/wizard.png"
};

const NpcInfo CLEANER_INFO = {
	"Cleaner Levi",
	"Winter 25",
	10,
	{ "Milk", "Cleaning tools" },
	{ "Clay" },
	{ "...", "Ahh, hi.", "Come and have some black-tea with me." },
	"npcImages/cleaner.png"
};

constexpr float INTERACTION_RANGE = 100.0f;			// 可调整的阈值，表示玩家与 NPC 之间的最大交互距离
constexpr int WIZARD_X = 300;
constexpr int WIZARD_Y = 300;
constexpr int CLEANER_X = 500;
constexpr int CLEANER_Y = 300;
constexpr int TALKING_BOX_WIDTH = 1283;
constexpr int TALKING_BOX_HEIGHT = 462;
constexpr int TALKING_BOX_X = 640;
constexpr int TALKING_BOX_Y = 200;
constexpr int LABEL_WIDTH = 720;
constexpr int LABEL_HEIGHT = 390;

// Bag


// Crop
constexpr int WATER_SCARCITY_DAY = 5;
constexpr int INFESTED_DAY = 5;

//SEED
constexpr char APPLE_SEED[] = "tools/appleSeed.png";
constexpr char CARROT_SEED[] = "tools/carrotSeed.png";
constexpr char CORN_SEED[] = "tools/cornSeed.png";
constexpr char FERTILIZER[] = "tools/fertilizer.png";

// DateManage
const std::unordered_map<std::string, int>
SEASONINDEX = { {"Spring", 0}, {"Summer", 1}, {"Fall", 2}, {"Winter", 3} }; // 季节的索引
const std::string SEASONNAME[] = { "Spring", "Summer", "Fall", "Winter" };  // 季节的名字
constexpr int DAYSINSEASON = 28;											// 每个季节的天数
constexpr int DAYSINYEAR = 112;												// 每年的天数（一年4季，每季28天）
constexpr int DAYSINWEEK = 7;												// 每周的天数
constexpr char SPRING_CONVERSATION[] = "Celebrate the arrival of Spring with games, food, and fun!\n";
constexpr char SUMMER_CONVERSATION[] = "The hot days of Summer are here! Time for the beach!\n";
constexpr char FALL_CONVERSATION[] = "Let's picking up the falling leaves!\n";
constexpr char WINTER_CONVERSATION[] = "Merry Christmas and Happy Birthday to levi!\n";

// FarmMap
constexpr int FARMMAP_WIDTH = 31;
constexpr int FARMMAP_HEIGHT = 17;
constexpr int SUN_OFFSET = 100;

// TileNode
constexpr int SOIL_GID = 36;
constexpr int HOED_SOIL_GID = 64;
constexpr int WATER_SOIL_GID = 96;
constexpr int WATER_GID = 17;
constexpr int STONE_GID = 22;
constexpr int MAX_WATER_RESOURCE = 1000;
constexpr int RANIY_REPLENISH = 200;

// Crop
constexpr int SEED_GID = 34;
constexpr int APPLE_GID = 1;
constexpr int CARROT_GID = 2;
constexpr int CORN_GID = 3;

// TOOL
constexpr int MAX_WATERINGCAN_CAPACITY = 100;			// 水壶最大容量
constexpr int AMOUNT_OF_WATER_PER_USE = 20;				// 每次用水量

//Item
struct ItemInfo {
	const char* name;             // 名称
	const char* image;            // 图片路径
};

// fish
// 示例鱼类数据
constexpr ItemInfo PUFFER_FISH = {
	"pufferFish",               // 鱼的名称
	"tools/pufferFish.png"      // 图片路径
};

constexpr ItemInfo TUNA = {
	"tuna",                      // 鱼的名称
	"tools/tuna.png",            // 图片路径
};

constexpr ItemInfo ANCHOVY = {
	"anchovy",                   // 鱼的名称
	"tools/anchovy.png",         // 图片路径
};

#endif __CONSTANT_H
