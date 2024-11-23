#include "main.h"
#include "Scene/AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

int WINAPI _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    // the same as return ((Application*)&app)->run();
    return Application::getInstance()->run();
}
