#include "Window.h"
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
Window* currentWindow;

bool Window::InitWindow(int width, int height, const char* windowName)
{
	HINSTANCE instance = (HINSTANCE)GetModuleHandle(NULL);

	WNDCLASS wc = { CS_BYTEALIGNCLIENT, (WNDPROC)::WindowProc, 0, 0, 0,
		NULL, NULL, NULL, NULL, _T(windowName) };

	RegisterClass(&wc);

	m_hWnd = CreateWindow(
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

	m_windowRect = { 0, 0, width, height };
	m_clientRect = { 0, 0, width, height };
	::GetWindowRect(m_hWnd, &m_windowRect);
	::GetClientRect(m_hWnd, &m_clientRect);

	int wx, wy, sx, sy;
	//RECT rect;
	//AdjustWindowRect(&rect, GetWindowLong(m_hWnd, GWL_STYLE), 0);
	wx = m_windowRect.right - m_windowRect.left;
	wy = m_windowRect.bottom - m_windowRect.top;
	sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
	sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
	if (sy < 0) sy = 0;
	SetWindowPos(m_hWnd, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
	SetForegroundWindow(m_hWnd);
	::GetWindowRect(m_hWnd, &m_windowRect);
	::GetClientRect(m_hWnd, &m_clientRect);
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
		case WM_CREATE: 
		{
			::GetWindowRect(hWnd, &m_windowRect);
			::GetClientRect(hWnd, &m_clientRect);
		}
		break;
		case WM_SIZE: 
		{
			::GetClientRect(hWnd, &m_clientRect);
			::GetWindowRect(hWnd, &m_windowRect);
			m_onWindowResize(m_windowRect.right - m_windowRect.left, m_windowRect.bottom - m_windowRect.top);
		}
		break;
		// this message is read when the window is closed
		case WM_DESTROY: 
		{
			// close the application entirely
			m_onWindowClose();
			PostQuitMessage(0);
			return 0;
		}
		break;
		case WM_MOVE:
		{
			::GetWindowRect(hWnd, &m_windowRect);
			::GetClientRect(hWnd, &m_clientRect);

			if (m_onWindowMove)
			{
				m_onWindowMove(m_windowRect);
			}
		
		}
		break;
		case WM_DISPLAYCHANGE:
			RECT rc;
			GetClientRect(hWnd, &rc);
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

