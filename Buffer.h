#pragma once
struct BUFFER_DESC
{
	unsigned int ByteWidth;
};


class Buffer
{
public:
	Buffer(BUFFER_DESC desc,void* initData);
	~Buffer();
private:
	unsigned char* m_pBuffer;
};

