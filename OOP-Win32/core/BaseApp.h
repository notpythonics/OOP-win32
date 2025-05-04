#ifndef BASE_APP
#define BASE_APP


#include <Windows.h>


class BaseApp {

public:

	BaseApp() = default;

	INT Run() {
		if (Init()) {
			return MessageLoop();
		} {
			return -1;
		}
	}

protected:

	// to do app initializing 
	// such as creating windows, menus, etc..
	virtual BOOL Init() = 0;

	// do not override
	INT MessageLoop() CONST {
		MSG msg{};
		BOOL bRet{};

		while (bRet = GetMessage(&msg, NULL, NULL, NULL)) {

			if (bRet == -1) {
				return -1;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		return static_cast<INT>(msg.wParam);
	}
};


#endif