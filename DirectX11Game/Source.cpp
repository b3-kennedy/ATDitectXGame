#include "Window.h"
#include "ErrorHandling.h"
#include <sstream>
#include "App.h"



int CALLBACK WinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    LPSTR       lpCmdLine,
    int         nCmdShow)
{


    return App{}.Go();
    
    
}