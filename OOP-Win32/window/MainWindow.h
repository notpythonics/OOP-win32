#ifndef MAIN_WINDOW
#define MAIN_WINDOW


#include "BaseWindow.h"


class MainWindow : public BaseWindow<MainWindow> {

public:

	MainWindow() = default;
	VOID OnDestroy() CONST override { PostQuitMessage(0); }
};


#endif