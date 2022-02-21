#pragma once
#include "Window.h"

class SwapChain;
class Device;
class DeviceContext;
class RenderTargetView;
class Buffer;
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

	void LoadCube();
	void LoadSword();

	Buffer* m_pCubeVertexBuffer;
	Buffer* m_pCubeIndexBuffer;

	Buffer* m_pBladeVertexBuffer;
	Buffer* m_pBladeIndexBuffer;

	Buffer* m_pSwordVertexBuffer;
	Buffer* m_pSwordIndexBuffer;
};

