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
	constexpr char  FONT_TTF[] = "fonts/Marker Felt.ttf";
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
	constexpr char SKILL_FOREGROUND[] = "icon/skillButton.png";
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

	// 音乐
	constexpr char SPRING_MUSIC[] = "sound/spring.mp3";
	constexpr char WELCOME_MUSIC[] = "sound/welcome.mp3";
	constexpr char BUTTON_MUSIC[] = "sound/button.mp3";
}
//工具图片
constexpr char AXE[] = "tools/axe.png";
constexpr char FISHING_ROD[] = "tools/fishingRod.png";
constexpr char HOE[] = "tools/hoe.png";
constexpr char PICKAXE[] = "tools/pickaxe.png";
constexpr char SCYTHE[] = "tools/scythe.png";
constexpr char KETTLE[] = "tools/kettle.png";
constexpr char MILKPAIL[] = "tools/milkPail.png";
constexpr char AGROCHEMICAL[] = "tools/agrochemical.png";

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
	"I have a gift for you.."
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
	const std::string task;
};

const NpcInfo WIZARD_INFO = {
	"Wizard Yuuu",
	"Fall 5",
	90,
	{ "appleSeed"},
	{ "tuna" },
	{ "Get out of my way.", "It's nice to see you here.", "I like to spend time with you." },
	"npcImages/wizard.png",
	"Go and get a tuna for my cat."
};

const NpcInfo CLEANER_INFO = {
	"Cleaner Levi",
	"Winter 25",
	10,
	{ "cornSeed"},
	{ "chicken" },
	{ "...", "Ahh, hi.", "Come and have some black-tea with me." },
	"npcImages/cleaner.png",
	"Find the notice board, and come back to me when you have finished what it says.\n"
};

constexpr float INTERACTION_RANGE = 100.0f;			// 可调整的阈值，表示玩家与 NPC 之间的最大交互距离
constexpr int WIZARD_X = 300;
constexpr int WIZARD_Y = 300;
constexpr int CLEANER_X = 500;
constexpr int CLEANER_Y = 300;
constexpr int CAMPFIRE_X = 400;
constexpr int CAMPFIRE_Y = 500;
constexpr int TALKING_BOX_WIDTH = 1283;
constexpr int TALKING_BOX_HEIGHT = 462;
constexpr int TALKING_BOX_X = 640;
constexpr int TALKING_BOX_Y = 200;
constexpr int LABEL_WIDTH = 720;
constexpr int LABEL_HEIGHT = 390;
constexpr int BOARD_X = 1600;
constexpr int BOARD_Y = 800;

// Bag
	// 添加初始化的物品
const std::vector<std::string> INIT_ITEMS ={	
	"hoe",
	"axe",
	"scythe",
	"kettle",
	"dogbaneSeed",
	"cornSeed",
	"carrotSeed",
	"fertilizer",
	"agrochemical",
	"cow",
	"chicken",
	"sheep",
	"pig"
};

// Crop
constexpr int WATER_SCARCITY_DAY = 5;
constexpr int INFESTED_DAY = 5;
constexpr int DOGBANE_SPRING_STAGE_FIRST = 2;
constexpr int DOGBANE_SPRING_STAGE_SECOND = 2;
constexpr int DOGBANE_SPRING_STAGE_THIRD = 2;
constexpr int DOGBANE_SUMMER_STAGE_FIRST = 1;
constexpr int DOGBANE_SUMMER_STAGE_SECOND = 1;
constexpr int DOGBANE_SUMMER_STAGE_THIRD = 1;
constexpr int DOGBANE_AUTUMN_STAGE_FIRST = 3;
constexpr int DOGBANE_AUTUMN_STAGE_SECOND = 3;
constexpr int DOGBANE_AUTUMN_STAGE_THIRD = 3;
constexpr int DOGBANE_WINTER_STAGE_FIRST = 4;
constexpr int DOGBANE_WINTER_STAGE_SECOND = 4;
constexpr int DOGBANE_WINTER_STAGE_THIRD = 4;
constexpr int CORN_SPRING_STAGE_FIRST = 3;
constexpr int CORN_SPRING_STAGE_SECOND = 2;
constexpr int CORN_SUMMER_STAGE_FIRST = 2;
constexpr int CORN_SUMMER_STAGE_SECOND = 1;
constexpr int CORN_AUTUMN_STAGE_FIRST = 4;
constexpr int CORN_AUTUMN_STAGE_SECOND = 3;
constexpr int CORN_WINTER_STAGE_FIRST = 5;
constexpr int CORN_WINTER_STAGE_SECOND = 4;
constexpr int CARROT_SPRING_STAGE_FIRST = 4;
constexpr int CARROT_SPRING_STAGE_SECOND = 2;
constexpr int CARROT_SUMMER_STAGE_FIRST = 2;
constexpr int CARROT_SUMMER_STAGE_SECOND = 1;
constexpr int CARROT_AUTUMN_STAGE_FIRST = 6;
constexpr int CARROT_AUTUMN_STAGE_SECOND = 5;
constexpr int CARROT_WINTER_STAGE_FIRST = 7;
constexpr int CARROT_WINTER_STAGE_SECOND = 6;

//SEED
constexpr char DOGBANE_SEED[] = "tools/dogbaneSeed.png";
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
constexpr int FARMMAP_SIZE_WIDTH = 1980;
constexpr int FARMMAP_SIZE_HEIGHT = 1080;
constexpr int FARMMAP_WIDTH = 31;
constexpr int FARMMAP_HEIGHT = 17;
constexpr int SUN_OFFSET = 100;
constexpr float CHANGE_MAP_DISTANCE = 80.0f;

// BeachMap
constexpr int BEACHMAP_WIDTH = 48;
constexpr int BEACHMAP_HEIGHT = 24;

// TileNode
constexpr int GRASS_GID = 87;
constexpr int SOIL_GID = 1;
constexpr int HOED_SOIL_GID = 2;
constexpr int WATER_SOIL_GID = 3;
constexpr int FERTILIZED_SOIL_GID = 4;
constexpr int WATER_GID = 95;
constexpr int STONE_GID = 89;
constexpr int OBSTACLES_GID = 100;
constexpr int MOLD_GID = 200;
constexpr int MAX_WATER_RESOURCE = 1000;
constexpr int MAX_SEED_RESOURCE = 1000;
constexpr int MAX_FERTILIZE_RESOURCE = 1000;
constexpr int RANIY_REPLENISH = 200;

// DogbaneCrop
constexpr int DOGBANE_FIRST = 5;
constexpr int DOGBANE_FIRST_FERTILIZE = 6;
constexpr int DOGBANE_FIRST_WATER = 7;
constexpr int DOGBANE_FIRST_FERTILIZE_WATER = 8;
constexpr int DOGBANE_SECOND = 9;
constexpr int DOGBANE_SECOND_FERTILIZE = 10;
constexpr int DOGBANE_SECOND_WATER = 11;
constexpr int DOGBANE_SECOND_FERTILIZE_WATER = 12;
constexpr int DOGBANE_THIRD = 13;
constexpr int DOGBANE_THIRD_ILL = 14;
constexpr int DOGBANE_THIRD_FERTILIZE = 15;
constexpr int DOGBANE_THIRD_WATER = 16;
constexpr int DOGBANE_THIRD_FERTILIZE_WATER = 17;
constexpr int DOGBANE_FOURTH = 18;
constexpr int DOGBANE_FOURTH_ILL = 19;
constexpr int DOGBANE_FOURTH_FERTILIZE = 20;
constexpr int DOGBANE_FOURTH_WATER = 21;
constexpr int DOGBANE_FOURTH_FERTILIZE_WATER = 22;

// CornCrop
constexpr int CORN_FIRST = 23;
constexpr int CORN_FIRST_FERTILIZE = 24;
constexpr int CORN_FIRST_WATER = 25;
constexpr int CORN_FIRST_FERTILIZE_WATER = 26;
constexpr int CORN_SECOND = 27;
constexpr int CORN_SECOND_ILL = 28;
constexpr int CORN_SECOND_FERTILIZE = 29;
constexpr int CORN_SECOND_FERTILIZE_WATER = 30;
constexpr int CORN_SECOND_WATER = 31;
constexpr int CORN_THIRD = 32;
constexpr int CORN_THIRD_ILL = 33;
constexpr int CORN_THIRD_FERTILIZE = 34;
constexpr int CORN_THIRD_FERTILIZE_WATER = 35;
constexpr int CORN_THIRD_WATER = 36;

// CarrotCrop
constexpr int CARROT_FIRST = 37;
constexpr int CARROT_FIRST_WATER = 38;
constexpr int CARROT_FIRST_FERTILIZE = 39;
constexpr int CARROT_FIRST_FERTILIZE_WATER = 40;
constexpr int CARROT_SECOND = 41;
constexpr int CARROT_SECOND_ILL = 42;
constexpr int CARROT_SECOND_FERTILIZE = 43;
constexpr int CARROT_SECOND_FERTILIZE_WATER = 44;
constexpr int CARROT_SECOND_WATER = 45;
constexpr int CARROT_THIRD = 46;
constexpr int CARROT_THIRD_ILL = 47;
constexpr int CARROT_THIRD_FERTILIZE = 48;
constexpr int CARROT_THIRD_WATER = 49;
constexpr int CARROT_THIRD_FERTILIZE_WATER = 50;

// DeadCrop
constexpr int DEAD_CROP = 51;

// MAXGROWTHSTAGE
constexpr int DOGBANE_MAX_GROWTH_STAGE = 4;
constexpr int CORN_MAX_GROWTH_STAGE = 3;
constexpr int CARROT_MAX_GROWTH_STAGE = 3;

// CropPestProbability
constexpr int DOGBANE_SPRING_PEST_PROBABILITY=30;
constexpr int DOGBANE_SUMMER_PEST_PROBABILITY = 20;
constexpr int DOGBANE_AUTUMN_PEST_PROBABILITY = 25;
constexpr int DOGBANE_WINTER_PEST_PROBABILITY = 10;
constexpr int CORN_SPRING_PEST_PROBABILITY = 25;
constexpr int CORN_SUMMER_PEST_PROBABILITY = 15;
constexpr int CORN_AUTUMN_PEST_PROBABILITY = 20;
constexpr int CORN_WINTER_PEST_PROBABILITY = 10;
constexpr int CARROT_SPRING_PEST_PROBABILITY = 35;
constexpr int CARROT_SUMMER_PEST_PROBABILITY = 25;
constexpr int CARROT_AUTUMN_PEST_PROBABILITY = 30;
constexpr int CARROT_WINTER_PEST_PROBABILITY = 10;

// Animal
constexpr char COW[] = "Animal/Cow.png";
constexpr char CHICKEN[] = "Animal/Chicken.png";
constexpr char SHEEP[] = "Animal/Sheep.png";
constexpr char PIG[] = "Animal/Pig.png";

// AnimalBehaviorControl
constexpr float COW_MOVE_RADIUS = 150.0f;
constexpr float COW_MOVE_INTERVAL = 1.0f;
constexpr float SHEEP_MOVE_RADIUS = 100.0f;
constexpr float SHEEP_MOVE_INTERVAL = 0.5f;
constexpr float PATROL_OFFSET = 50.0f;
constexpr float	SUNNY_WANDER_RADIUS_INFLUENCE = 20.0f;
constexpr float SUNNY_WANDER_MOVEDURATION_INFLUENCE = -0.2f;
constexpr float LIGHTRAIN_WANDER_RADIUS_INFLUENCE = -40.f;
constexpr float LIGHTRAIN_WANDER_MOVEDURATION_INFLUENCE = 1.0f;
constexpr float HEAVYRAIN_WANDER_RADIUS_INFLUENCE = -70.f;
constexpr float HEAVYRAIN_WANDER_MOVEDURATION_INFLUENCE = 2.0f;
constexpr float SUNNY_SPEED_INFLUENCE = 10;
constexpr float LIGHTRAIN_SPEED_INFLUENCE = -30;
constexpr float HEAVYRAIN_SPEED_INFLUENCE = -50;

// Tool
constexpr int MAX_WATERINGCAN_CAPACITY = 100;			// 水壶最大容量
constexpr int AMOUNT_OF_WATER_PER_USE = 20;				// 每次用水量
constexpr int AMOUNT_OF_FERTILIZE_PER_USE = 10;			// 每次施肥量

//Item
struct ItemInfo {
	const char* name;             // 名称
	const char* image;            // 图片路径
};

constexpr ItemInfo STONE_ITEM = {
	"stone",
	"tools/stone.png"
};

// AnimalItem
constexpr ItemInfo COW_ITEM = {
	"cow",
	"tools/cow.png"
};

constexpr ItemInfo CHICKEN_ITEM = {
	"chicken",
	"tools/chicken.png"
};

constexpr ItemInfo SHEEP_ITEM = {
	"sheep",
	"tools/sheep.png"
};

constexpr ItemInfo PIG_ITEM = {
	"pig",
	"tools/pig.png"
};

// FoodItem
constexpr ItemInfo DOGBANE_ITEM = {
	"dogbane",
	"food/parsnip.png"
};
constexpr ItemInfo CORN_ITEM = {
	"corn",
	"food/corn.png"
};
constexpr ItemInfo CARROT_ITEM = {
	"carrot",
	"food/carrot.png"
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

constexpr ItemInfo CAMPFIRE = {
	"campFire",                   // 名称
	"tools/campFire.png",         // 图片路径
};

constexpr ItemInfo BOARD = {
	"noticeBoard",                   // 名称
	"tools/noticeBoard.png",         // 图片路径
};

constexpr ItemInfo BUILDING = {
	"building",                   // 名称
	"tools/building.png",         // 图片路径
};

// MarketGood
struct MarketGoodLabel{
	const char* name;             // 名称
	const int basePrice;		  // 商品的基础价格
};

// 防风草商品
const MarketGoodLabel DOGBANE = {
	"dogbaneFood",
	20,
};

// 玉米商品
const MarketGoodLabel CORN = {
	"cornFood",
	25,
};

// 胡萝卜商品
const MarketGoodLabel CARROT = {
	"carrotFood",
	30,
};

// 石头商品
const MarketGoodLabel STONE = {
	"stoneItem",
	5,
};

// 市场的初始化
const std::vector<MarketGoodLabel> INIT_GOODS = {
	DOGBANE,
	CARROT,
	CARROT,
	STONE,
};

// 人物初始金币
constexpr int PLAYER_INITIAL_MONEY = 500;
constexpr int SUNNY_MONEY_INFLUENCE = 0;
constexpr int LIGHTRAIN_MONEY_INFLUENCE = 10;
constexpr int HEAVYRAIN_MONEY_INFLUENCE = 30;
constexpr int SNOWY_MONEY_INFLUENCE = 50;

// Weather
constexpr int SUNNY_SET_SPEED = 0;
constexpr int LIGHTRAIN_SPEED=500;
constexpr int LIGHTRAIN_SPEED_VAR = 50;
constexpr float LIGHTRAIN_SIZE = 10.0f;
constexpr float LIGHTRAIN_SIZE_END = 5.0f;
constexpr int HEAVYRAIN_SPEED = 800;
constexpr int HEAVYRAIN_SPEED_VAR = 100;
constexpr float HEAVYRAIN_SIZE = 15.0f;
constexpr float HEAVYRAIN_SIZE_END = 10.0f;
constexpr int SNOWY_SPEED = 100;
constexpr int SNOWY_SPEED_VAR = 20;
constexpr float SNOWY_SIZE = 10.0f;
constexpr float SNOWY_SIZE_END = 5.0f;
constexpr int WEATHER_CHILD_NUM = 100;

#endif __CONSTANT_H