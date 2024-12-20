/****************************************************************
 * File Function: 告示牌类，继承Sprite类，用于显示和完成特定npc的特殊任务
 * Author:        韦瑾钰
 ****************************************************************/
#ifndef __NOTICE_BOARD_H__
#define __NOTICE_BOARD_H__

#include <string>
#include "cocos2d.h"
#include "../Constant/Constant.h"

USING_NS_CC;

class NoticeBoard : public Sprite{
public:

    // 创建告示牌
    static NoticeBoard* create();

    // 初始化
    bool init(const ItemInfo& noticeBoardInfo);

    // 对话信息
    std::string printDialogue() const;

    //任务完成
    static bool getTaskStatus() { return isTaskCompleted; }
    bool completeTask() { return isTaskCompleted = true; }

private:
    std::string name;
    std::string image;
    static bool isTaskCompleted;
};

#endif // __NOTICE_BOARD_H__
