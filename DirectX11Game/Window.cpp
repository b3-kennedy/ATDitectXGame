#include "Window.h"
#include <sstream>

Window::WinClass Window::WinClass::windowClass;

Window::WinClass::WinClass() noexcept : hInst(GetModuleHandle(nullptr))
{
    WNDCLASSEX window = { 0 };
    window.cbSize = sizeof(window);
    window.style = CS_OWNDC;
    window.lpfnWndProc = MsgSetup;
    window.cbClsExtra = 0;
    window.cbWndExtra = 0;
    window.hInstance = GetInstance();
    window.hIcon = nullptr;
    window.hCursor = nullptr;
    window.hbrBackground = nullptr;
    window.lpszMenuName = nullptr;
    window.lpszClassName = GetName();
    window.hIconSm = nullptr;

    RegisterClassEx(&window);
}

Window::WinClass::~WinClass() 
{
    UnregisterClass(winClassName, GetInstance());
}

const char* Window::WinClass::GetName() noexcept
{
    return winClassName;
}

HINSTANCE Window::WinClass::GetInstance() noexcept
{
    return windowClass.hInst;
}

Window::Window(int width, int height, const char* name) : width(width), height(height)
{
    RECT rect;
    rect.left = 100;
    rect.right = width * rect.left;
    rect.top = 100;
    rect.bottom = height + rect.top;
    AdjustWindowRect(&rect, WS_CAPTION | WS_MINIMIZE | WS_SYSMENU, FALSE);


    hWnd = CreateWindow(WinClass::GetName(), name, WS_CAPTION | WS_MINIMIZE | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, 
        WinClass::GetInstance(), this);

    ShowWindow(hWnd, SW_SHOWDEFAULT);

    gfx = std::make_unique<Graphics>(hWnd);
}

Window::~Window() 
{
    DestroyWindow(hWnd);
}

void Window::SetTitle(const std::string& title)
{
    if(SetWindowText(hWnd, title.c_str()) == 0)
    {
        SetWindowText(hWnd, title.c_str());
    }
}

std::optional<int> Window::ProcessMessages()
{
    MSG msg;
    while (PeekMessage(&msg,nullptr,0,0,PM_REMOVE))
    {
        if(msg.message == WM_QUIT)
        {
            return msg.wParam;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return {};
}

Graphics& Window::getGfx()
{
    return *gfx;
}

LRESULT WINAPI Window::MsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    if(msg == WM_NCCREATE)
    {
        const CREATESTRUCTW* const paramCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        Window* const paramWindow = static_cast<Window*>(paramCreate->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(paramWindow));
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgCall));
        return paramWindow->HandleMsg(hWnd, msg, wParam, lParam);
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);

}

LRESULT WINAPI Window::HandleMsgCall(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    Window* const paramWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    return paramWindow->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (msg)
    {
    case WM_CLOSE:
    {
        PostQuitMessage(0);
        return 0;
    }
    case WM_KILLFOCUS:
    {
        keyboard.ClearState();
        break;
    }


    case WM_KEYDOWN:
    {
        if (!(lParam & 0x40000000) || keyboard.AutorepeatIsEnabled())
        {
            keyboard.OnKeyPressed(static_cast<unsigned char>(wParam));
        }
        if(wParam == VK_ESCAPE)
        {
            PostQuitMessage(0);
        }
        break;
    }
    case WM_KEYUP:
    {
        keyboard.OnKeyReleased(static_cast<unsigned char>(wParam));
        break;
    }
    case WM_SYSKEYUP:
    {
        keyboard.OnKeyReleased(static_cast<unsigned char>(wParam));
        break;
    }
    case WM_CHAR:
    {
        keyboard.OnChar(static_cast<unsigned char>(wParam));
        break;
    }



    case WM_MOUSEMOVE:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        if(pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height)
        {
            if(!mouse.IsInWindow())
            {
                SetCapture(hWnd);
                mouse.OnMouseEnter();
            }
        }
        else
        {
            if(wParam & (MK_LBUTTON | MK_RBUTTON))
            {
                mouse.OnMouseMove(pt.x, pt.y);
            }
            else
            {
                ReleaseCapture();
                mouse.OnMouseLeave();
            }
        }
        
        break;
    }
    case WM_LBUTTONDOWN:
    {
        const POINTS pt1 = MAKEPOINTS(lParam);
        mouse.OnLeftPressed(pt1.x, pt1.y);
        break;
    }
    case WM_LBUTTONUP:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        mouse.OnLeftReleased(pt.x, pt.y);
        break;
    }
    case WM_RBUTTONDOWN:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        mouse.OnRightPressed(pt.x, pt.y);
        break;
    }
    case WM_RBUTTONUP:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        mouse.OnRightReleased(pt.x, pt.y);
        break;
    }
    case WM_MOUSEWHEEL:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
        mouse.OnWheelDelta(pt.x, pt.y, delta);
        break;
    }

    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

Window::Exception::Exception(int line, const char* file, HRESULT hr) noexcept : ErrorHandling(line, file), hr(hr)
{}

const char* Window::Exception::what() const noexcept
{
    std::ostringstream stream;
    stream << GetType() << std::endl << "[Error Code] " << GetErrorCode() << std::endl << "[Description] " << GetErrorString() << std::endl << GetOriginString();
    whatBuffer = stream.str();
    return whatBuffer.c_str();
}

const char* Window::Exception::GetType() const noexcept
{
    return "Window Exception";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
    char* error = nullptr;
    DWORD errorMsg = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPSTR>(&error), 0, nullptr);

    if(errorMsg == 0)
    {
        return "Unknown Error";
    }

    std::string errorString = error;
    LocalFree(error);
    return errorString;

}

HRESULT Window::Exception::GetErrorCode() const noexcept
{
    return hr;
}

std::string Window::Exception::GetErrorString() const noexcept
{
    return TranslateErrorCode(hr);
}

