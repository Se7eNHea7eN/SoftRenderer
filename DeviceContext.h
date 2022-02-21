#pragma once
class RenderTargetView;
class DepthStencilView;
class Buffer;
class DeviceContext
{
public:
	void ClearRenderTargetView(RenderTargetView* pRenderTargetView ,const float* color);
	void ClearDepthStencilView(DepthStencilView* pDepthStencilView,float depth,unsigned int stencil);
	void DrawIndexed(unsigned int indexCount, unsigned int startIndexLocation);

	void SetVertexBuffer(Buffer* pBuffer);
	void SetIndexBuffer(Buffer* pBuffer);

private:
	Buffer* m_pCurrentVertexBuffer;
	Buffer* m_pCurrentIndexBuffer;
};