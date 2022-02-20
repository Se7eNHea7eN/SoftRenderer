#include "Device.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "Texture2D.h"
int Device::CreateSwapChain(SwapChain** ppSwapChain, HWND hwnd)
{
	*ppSwapChain = new SwapChain(this,hwnd);
	return 0;
}

int Device::CreateTexture2D(TEXTURE2D_DESC desc, Texture2D** ppTexture2D)
{
	*ppTexture2D = new Texture2D(desc);
	return 0;
}

int CreateDevice(Device** ppDevice, DeviceContext** ppDeviceContext)
{
	*ppDevice = new Device();
	*ppDeviceContext = new DeviceContext();
	return 0;
}
