#include "Texture2D.h"
#include <string.h>
Texture2D::Texture2D(TEXTURE2D_DESC desc) : m_desc(desc)
{
	m_BufferSize = desc.width * desc.height * 4;
	m_pBuffer = new unsigned char[m_BufferSize];
	memset(m_pBuffer, 0, m_BufferSize);
}

Texture2D::Texture2D(TEXTURE2D_DESC desc, unsigned char* buffer) : m_desc(desc)
{
	m_BufferSize = desc.width * desc.height * 4;
	m_pBuffer = buffer;
	memset(m_pBuffer, 7, m_BufferSize);
}

Texture2D::~Texture2D()
{
	delete[] m_pBuffer;
}

TEXTURE2D_DESC Texture2D::GetDesc()
{
	return m_desc;
}

const unsigned char* Texture2D::GetBuffer()
{
	return m_pBuffer;
}

int Texture2D::GetBufferSize()
{
	return m_BufferSize;
}
