#pragma once
#include <functional>
#include <Windows.h>
class Window
{
public:
	virtual bool InitWindow(int width, int height, const char* windowName);

	virtual bool ReleaseWindow();

	virtual void* GetNativeWindowHandle();


	virtual bool ShowWindow();

	virtual void MessageProcess();

	virtual void SetOnWindowResizeCallback(std::function<void(int, int)> onWindowResize)
	{
		m_onWindowResize = onWindowResize;
	}

	virtual void SetOnWindowCloseCallback(std::function<void(void)> onWindowClose)
	{
		m_onWindowClose = onWindowClose;
	}
	virtual void SetOnWindowMoveCallback(std::function<void(RECT)> onWindowMove)
	{
		m_onWindowMove = onWindowMove;
	}

	RECT GetWindowRect()
	{
		return m_windowRect;
	}
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
	HWND m_hWnd;
	std::function<void(int, int)> m_onWindowResize;
	std::function<void(void)> m_onWindowClose;
	std::function<void(RECT)> m_onWindowMove;
	RECT m_windowRect;
	RECT m_clientRect;
	int m_nWidth, m_nHeight;
};