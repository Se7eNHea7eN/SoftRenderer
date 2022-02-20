#include "Window.h"
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
Window* currentWindow;

bool Window::InitWindow(int width, int height, const char* windowName)
{
	HINSTANCE instance = (HINSTANCE)GetModuleHandle(NULL);
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = ::WindowProc;
	wc.hInstance = instance;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = _T(windowName);

	RegisterClassEx(&wc);

	m_hWnd = CreateWindowEx(WS_EX_ACCEPTFILES,
		_T(windowName), // name of the window class
		_T(windowName), // title of the window
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // window style
		0, // x-position of the window
		0, // y-position of the window
		width, // width of the window
		height, // height of the window
		nullptr, // we have no parent window, NULL
		nullptr, // we aren't using menus, NULL
		instance, // application handle
		nullptr); // used with multiple windows, NULL
	m_nWidth = width;
	m_nHeight = height;
	return true;
}


bool Window::ShowWindow()
{
	::ShowWindow(m_hWnd, SW_SHOWNORMAL);
	currentWindow = this;
	return false;
}

void Window::MessageProcess()
{
	MSG msg;
	while (0 != PeekMessageW(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

LRESULT Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message) {
	case WM_CREATE: {

	}
				  break;
	case WM_SIZE: {
		RECT rc;
		GetClientRect(hWnd, &rc);
		m_onWindowResize(rc.right - rc.left, rc.bottom - rc.top);
	}
				break;
				// this message is read when the window is closed
	case WM_DESTROY: {
		// close the application entirely
		m_onWindowClose();
		PostQuitMessage(0);
		return 0;
	}
				   break;
	case WM_DISPLAYCHANGE:
		// InvalidateRect(hWnd, nullptr, false);
		break;
	}
	// Handle any messages the switch statement didn't
	return
		DefWindowProc(hWnd, message, wParam, lParam);
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (currentWindow != nullptr)
		return currentWindow->WindowProc(hWnd, message, wParam, lParam);
	return
		DefWindowProc(hWnd, message, wParam, lParam);
}



bool Window::ReleaseWindow()
{
	if (currentWindow == this)
		currentWindow = nullptr;
	return true;
}

void* Window::GetNativeWindowHandle()
{
	return nullptr;
}

