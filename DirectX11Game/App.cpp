#include "App.h"
#include "Cube.h"


App::App() : window(1920, 1080, "DirectX Game") 
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
    std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
    std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
    std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
    for (auto i = 0; i < 200; i++)
    {
        cubes.push_back(std::make_unique<Cube>(
            window.getGfx(), rng, adist,
            ddist, odist, rdist
            ));
    }
    singleCube = std::make_unique<Cube>(window.getGfx(), rng, adist, ddist, odist, rdist);

    window.getGfx().SetProjection(DirectX::XMMatrixPerspectiveLH(5, 3840.0f/2160.0f, 0.5f, 100.0f));

    levelLoader.ReadFile("TestLevel.txt");

    
        //for (size_t i = 0; i < 11; i++)
        //{
        //    if (levelLoader.ConstructLevel(cubes[i].get()))
        //    {
        //        window.SetTitle("Level read");
        //    }
        //}
    for (size_t i = 0; i < 200; i++)
    {
        if (levelLoader.ConstructLevel(cubes[i].get()))
        {
            window.SetTitle("Level read");
        }
    }




}

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

App::~App()
{
}

void App::DoFrame() 
{
    auto deltaTime = timer.Mark();
    window.getGfx().ClearBuffer(0.5f, 0.5f, 1);
    window.getGfx().SetCamera(cam.GetMatrix());
    
    if(window.keyboard.KeyIsPressed('W'))
    {
        cam.ChangePosition(0.0f,deltaTime * 5,0.0f);
    }

    if(window.keyboard.KeyIsPressed('S'))
    {
        cam.ChangePosition(0.0f, -deltaTime * 5, 0.0f);
    }

    if (window.keyboard.KeyIsPressed('A'))
    {
        cam.ChangePosition(-deltaTime * 5, 0.0f, 0.0f);
    }

    if (window.keyboard.KeyIsPressed('D'))
    {
        cam.ChangePosition(deltaTime * 5, 0.0f, 0.0f);
    }

    if (window.keyboard.KeyIsPressed(VK_SPACE))
    {
        cam.ChangePosition(0.0f, 0.0f, deltaTime * 5);
    }

    if (window.keyboard.KeyIsPressed(VK_CONTROL))
    {
        cam.ChangePosition(0.0f, 0.0f, -deltaTime * 5);
    }


    for (size_t i = 0; i < 200; i++)
    {
        cubes[i]->Update(deltaTime);
        cubes[i]->Draw(window.getGfx());
    }
    

    window.getGfx().EndFrame();

}
