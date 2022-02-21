#include "Renderer.h"
#include "Device.h"
#include "DeviceContext.h"
#include "SwapChain.h"
void Renderer::Init(Window* pWindow)
{
	pWindow->SetOnWindowResizeCallback([&](int width, int height) -> void
	{
			//this->Resize(width, height);
	});
	pWindow->SetOnWindowMoveCallback([](RECT rect) -> void {

	});
	::CreateDevice(&m_pDevice, &m_pDeviceContext);
	m_pDevice->CreateSwapChain(&m_pSwapChain, pWindow);
	RECT rect = pWindow->GetWindowRect();
	Resize(rect.right- rect.left, rect.bottom- rect.top);
}

void Renderer::Tick(float deltaTime)
{
}

void Renderer::Render()
{
	m_pSwapChain->Present();
}

void Renderer::Resize(int width, int height)
{
	m_pSwapChain->ResizeBuffers(width, height);
}
