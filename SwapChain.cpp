#include <Windows.h>
#include "SwapChain.h"
#include "Device.h"
#include "Texture2D.h"
#include "Window.h"

SwapChain::SwapChain(Device* pDevice, Window* pWindow) :
    m_hwnd((HWND)pWindow->GetNativeWindowHandle()),
    m_pTargetWindow(pWindow),
    m_pDevice(pDevice),
    m_pBackBuffer(nullptr)
{
    m_hdc = GetDC(m_hwnd);
    m_hBufferDC = CreateCompatibleDC(m_hdc);

}
void SwapChain::Present()
{
    RECT windowRect = m_pTargetWindow->GetWindowRect();
    RECT clientRect = m_pTargetWindow->GetWindowRect();
    BitBlt(m_hdc, clientRect.left, clientRect.top, clientRect.right, clientRect.bottom, m_hBufferDC, 0, 0, SRCCOPY);
    //BitBlt(m_hdc, 0, 0, 1280, 720, m_hBufferDC, 0, 0, SRCCOPY);

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
