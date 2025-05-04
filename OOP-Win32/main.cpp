#ifndef UNICODE
#define UNICODE
#endif


#include <Windows.h>

#include "App.h"




INT WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, INT) {

	App app{};

	return app.Run();
}