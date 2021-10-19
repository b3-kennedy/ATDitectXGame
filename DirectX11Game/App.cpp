#include "App.h"


App::App() : window(1920, 1080, "DirectX Game") {};

int App::Go()
{
    
    while(true)
    {
        if(const auto code = Window::ProcessMessages())
        {
            return *code;
        }
        DoFrame();
    }
}

void App::DoFrame() 
{
    window.getGfx().ClearBuffer(0.5f, 0.5f, 1);
    window.getGfx().DrawTriangle();
    window.getGfx().EndFrame();
}
