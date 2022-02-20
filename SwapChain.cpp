#include <Windows.h>
#include "SwapChain.h"
#include "Device.h"
#include "Texture2D.h"

SwapChain::SwapChain(Device* pDevice, HWND hwnd) : 
    m_hwnd(hwnd),
    m_pDevice(pDevice),
    m_pBackBuffer(nullptr)
{
    m_hdc = GetDC(hwnd);
    m_hBufferDC = CreateCompatibleDC(m_hdc);

}
void SwapChain::Present()
{
    BitBlt(m_hdc, 0, 0, m_pBackBuffer->GetDesc().width, m_pBackBuffer->GetDesc().height, m_hBufferDC, 0, 0, SRCCOPY);
}

int SwapChain::ResizeBuffers(int width, int height)
{
    if (m_pBackBuffer != nullptr)
    {
        delete m_pBackBuffer;
    }
    TEXTURE2D_DESC desc;
    desc.width = width;
    desc.height = height;
    //m_pDevice->CreateTexture2D(desc, &m_pBackBuffer);

    BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), width, -height, 1, 32, BI_RGB, width* height * 4, 0, 0, 0, 0 } };
    LPVOID ptr;
    auto screen_hb = CreateDIBSection(m_hBufferDC, &bi, DIB_RGB_COLORS, &ptr, 0, 0);
    auto screen_ob = (HBITMAP)SelectObject(m_hBufferDC, screen_hb);
    m_pBackBuffer = new Texture2D(desc, (unsigned char*)ptr);
    return 0;
}

int SwapChain::GetBuffer(Texture2D** ppTexture2D)
{
    *ppTexture2D = m_pBackBuffer;
    return 0;
}
