#include "Buffer.h"
#include<string.h>
Buffer::Buffer(BUFFER_DESC desc, void* initData)
{
	m_pBuffer = new unsigned char[desc.ByteWidth];
	memcpy(m_pBuffer, initData, desc.ByteWidth);

}

Buffer::~Buffer()
{
	delete[] m_pBuffer;
}
