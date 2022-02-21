#pragma once
#include <Windows.h>
class Texture2D;
class Device;
class Window;
class SwapChain
{
public:
	SwapChain(Device* pDevice, Window* pWindow);
	void Present();
	int ResizeBuffers(int width, int height);
	int GetBuffer(Texture2D** ppTexture2D);
private:
	Device* m_pDevice;
	Window* m_pTargetWindow;
	HWND m_hwnd;
	HDC m_hdc;
	HDC m_hBufferDC;

	HBITMAP m_hbitmap;
	Texture2D* m_pBackBuffer;
};
