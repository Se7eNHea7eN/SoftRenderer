#pragma once
#include <Windows.h>

class SwapChain;
class DeviceContext;
class Texture2D;
class RenderTargetView;
class Window;
struct TEXTURE2D_DESC;
class Device
{
public:
	int CreateSwapChain(SwapChain** ppSwapChain, Window* pWindow);
	int CreateRenderTargetView(Texture2D* pTexture2D, RenderTargetView** ppRenderTargetView);
	int CreateTexture2D(TEXTURE2D_DESC desc, Texture2D** ppTexture2D);
};

int CreateDevice(Device** ppDevice, DeviceContext** ppDeviceContext);