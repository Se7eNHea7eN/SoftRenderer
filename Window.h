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

	int Width()
	{
		return m_nWidth;
	}
	int Height()
	{
		return m_nHeight;
	}
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
	HWND m_hWnd;
	std::function<void(int, int)> m_onWindowResize;
	std::function<void(void)> m_onWindowClose;
	int m_nWidth, m_nHeight;
};