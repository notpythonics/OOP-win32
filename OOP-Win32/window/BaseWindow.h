#ifndef BASE_WINDOW
#define BASE_WINDOW


#include <Windows.h>


template<typename DERIVED_TYPE>
class BaseWindow {

public:

	HWND GetHWND() const { return m_hWnd; }

	BOOL Create(HWND hWndParent = NULL) {
		WNDCLASS wc{};

		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = StaticWindowProc;
		wc.hInstance = GetModuleHandle(NULL);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));


		PreRegisterClass(wc);

		// if not given class name
		if (!wc.lpszClassName) {
			wc.lpszClassName = L"ASIAN WOMEN";
		}

		RegisterClass(&wc);


		CREATESTRUCT cs{};

		cs.lpCreateParams = reinterpret_cast<VOID*>(this);
		cs.hInstance = GetModuleHandle(NULL);
		cs.hwndParent = hWndParent;

		if (!hWndParent) {
			cs.cx = CW_USEDEFAULT;
			cs.cy = CW_USEDEFAULT;
			cs.x = CW_USEDEFAULT;
			cs.y = CW_USEDEFAULT;
		}

		cs.style = (hWndParent ? WS_CHILDWINDOW : WS_OVERLAPPEDWINDOW) | WS_VISIBLE;
		cs.lpszClass = wc.lpszClassName;

		PreCreateWindow(cs);

		HWND hWnd = CreateWindowEx(cs.dwExStyle, cs.lpszClass, cs.lpszName, cs.style,
			cs.x, cs.y, cs.cx, cs.cy, cs.hwndParent, cs.hMenu, cs.hInstance, reinterpret_cast<VOID*>(this));

		return (hWnd ? TRUE : FALSE);
	}

protected:

	static LRESULT CALLBACK StaticWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		DERIVED_TYPE* pThis{};

		if (uMsg == WM_NCCREATE) {
			CREATESTRUCT* pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
			pThis = reinterpret_cast<DERIVED_TYPE*>(pCreateStruct->lpCreateParams);

			pThis->m_hWnd = hWnd;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));

			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		else
			pThis = reinterpret_cast<DERIVED_TYPE*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		if (pThis)
			return pThis->HandleMessage(hWnd, uMsg, wParam, lParam);
		else
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	BaseWindow() = default;

	HWND m_hWnd{};

	// overridables
	virtual VOID PreRegisterClass(WNDCLASS& wc) CONST {}
	virtual VOID PreCreateWindow(CREATESTRUCT& cs) CONST {}

	virtual LRESULT HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		// override this to process more messages

		return DefHandleMessage(hWnd, uMsg, wParam, lParam);
	}

	// do not override
	LRESULT DefHandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		switch (uMsg) {

		case WM_PAINT:
			OnPaint();
			return 0;

		case WM_DESTROY:
			OnDestroy();
			return 0;
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	// overridables
	virtual VOID OnPaint() CONST {}
	virtual VOID OnDestroy() CONST {}
};


#endif