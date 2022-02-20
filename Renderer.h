#pragma once
#include "Window.h"

class SwapChain;
class Device;
class DeviceContext;
class RenderTargetView;
class Renderer
{
public:
	void Init(Window* pWindow);
	void Tick(float deltaTime);
	void Render();
	void Resize(int width, int height);
private:
	Device* m_pDevice;
	DeviceContext* m_pDeviceContext;
	SwapChain* m_pSwapChain;
	RenderTargetView* m_pRenderTarget;
};

