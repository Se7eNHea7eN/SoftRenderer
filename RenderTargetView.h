#pragma once
class Texture2D;
class RenderTargetView
{
public:
	RenderTargetView(Texture2D* pBuffer);
private:
	Texture2D* m_pBuffer;
};