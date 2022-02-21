#include "DeviceContext.h"

void DeviceContext::ClearRenderTargetView(RenderTargetView* pRenderTargetView, const float* color)
{
}

void DeviceContext::ClearDepthStencilView(DepthStencilView* pDepthStencilView, float depth, unsigned int stencil)
{
}

void DeviceContext::DrawIndexed(unsigned int indexCount, unsigned int startIndexLocation)
{
}

void DeviceContext::SetVertexBuffer(Buffer* pBuffer)
{
	m_pCurrentVertexBuffer = pBuffer;
}

void DeviceContext::SetIndexBuffer(Buffer* pBuffer)
{
	m_pCurrentIndexBuffer = pBuffer;
}
