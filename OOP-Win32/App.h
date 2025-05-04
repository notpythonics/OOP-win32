#ifndef APP
#define APP


#include "core/BaseApp.h"

#include "window/MainWindow.h"


class App : public BaseApp {

protected:

	MainWindow mainWindow{};

	BOOL Init() override {

		return mainWindow.Create();
	}

};


#endif