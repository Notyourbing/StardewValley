#include "NoticeBoard.h"

USING_NS_CC;

//bool NoticeBoard::isAdded = false;
bool NoticeBoard::isTaskCompleted = false;

NoticeBoard* NoticeBoard::create() {
    NoticeBoard* noticeBoard = new (std::nothrow) NoticeBoard;
    if (noticeBoard && noticeBoard->init(BOARD)) {
        noticeBoard->autorelease();
        return noticeBoard;
    }
    CC_SAFE_DELETE(noticeBoard);
    return nullptr;
}

//init函数
bool NoticeBoard::init(const ItemInfo& noticeBoardInfo) {
    if (!Sprite::initWithFile(noticeBoardInfo.image)) {
        return false;
    }
    name = noticeBoardInfo.name;
    image = noticeBoardInfo.image;
    return true;
}

//返回固定的对话内容
std::string NoticeBoard::printDialogue() const {
    if (!isTaskCompleted)
        return "It's levi's unique task.Find 3 pieces of  stones to build it up.";
    return "...";
}
