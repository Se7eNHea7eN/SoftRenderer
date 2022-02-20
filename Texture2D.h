#pragma once
struct TEXTURE2D_DESC
{
	int width;
	int height;
};

class Texture2D
{
public:
	Texture2D(TEXTURE2D_DESC desc);
	Texture2D(TEXTURE2D_DESC desc, unsigned char* buffer);
	~Texture2D();
	TEXTURE2D_DESC GetDesc();
	const unsigned char* GetBuffer();
	int GetBufferSize();
private:
	TEXTURE2D_DESC m_desc;
	unsigned char* m_pBuffer;
	int m_BufferSize;
};
