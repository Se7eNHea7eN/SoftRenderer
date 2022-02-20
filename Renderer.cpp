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
	::CreateDevice(&m_pDevice, &m_pDeviceContext);
	m_pDevice->CreateSwapChain(&m_pSwapChain,(HWND)pWindow->GetNativeWindowHandle());
	Resize(pWindow->Width(), pWindow->Height());
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
