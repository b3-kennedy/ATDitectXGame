#include "App.h"
#include "Cube.h"


App::App() : window(1920, 1080, "DirectX Game")
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
    std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
    std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
    std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
    for (auto i = 0; i < NUMBER_OF_CUBES; i++)
    {
        cubes.push_back(std::make_unique<Cube>(
            window.getGfx(), rng, adist,
            ddist, odist, rdist
            ));
    }
    singleCube = std::make_unique<Cube>(window.getGfx(), rng, adist, ddist, odist, rdist);

    window.getGfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 1.0f, 0.5f, 100.0f));

    levelLoader.ReadFile("TestLevel2.txt");


    for (size_t i = 0; i < NUMBER_OF_CUBES; i++)
    {
        if (levelLoader.ConstructLevel(cubes[i].get()))
        {
            window.SetTitle("Level read");
        }
    }

    cam->SetPosition(5.0f, 5.0f, 5.0f);




}

int App::Go()
{

    while (true)
    {
        //window.DisableCursor();
        if (const auto code = Window::ProcessMessages())
        {
            return *code;
        }
        auto deltaTime = timer.Mark();
        Input(deltaTime);
        DoFrame(deltaTime);
    }
}

App::~App()
{
}

void App::DoFrame(float deltaTime)
{

    window.getGfx().ClearBuffer(0.5f, 0.5f, 1);
    //window.SetTitle(std::to_string(cam->trans.x) + " " + std::to_string(cam->trans.y) + " " + std::to_string(cam->trans.z));
    for (size_t i = 0; i < NUMBER_OF_CUBES; i++)
    {
        cubes[i]->Update(deltaTime);
        cubes[i]->Draw(window.getGfx());
        if (cubes[i]->OnCollision(cam.get()))
        {

            canInput = false;
            //cam->SetSpeed(0.0f);
            //cam->SetPosition(cam->prevPosition.x,cam->prevPosition.y,cam->prevPosition.z);
            cam->Translate({ -cam->trans.x * deltaTime * 30, 0.0f, -cam->trans.z * deltaTime * 30 });
        }
        else
        {
            //cam->SetSpeed(12.0f);
            canInput = true;
        }
    }

    window.getGfx().SetCamera(cam->GetMatrix());






    window.getGfx().EndFrame();

}

void App::Input(float deltaTime)
{
    if (canInput)
    {
        if (window.keyboard.KeyIsPressed('W'))
        {
            cam->Translate({ 0.0f, 0.0f,deltaTime });
        }

        if (window.keyboard.KeyIsPressed('S'))
        {
            cam->Translate({ 0.0f, 0.0f, -deltaTime });
        }

        if (window.keyboard.KeyIsPressed('A'))
        {
            cam->Translate({ -deltaTime, 0.0f, 0.0f });
        }

        if (window.keyboard.KeyIsPressed('D'))
        {
            cam->Translate({ deltaTime, 0.0f, 0.0f });
        }

        if (window.keyboard.KeyIsPressed(VK_SPACE))
        {
            cam->Translate({ 0.0f, deltaTime, 0.0f });
        }

        if (window.keyboard.KeyIsPressed(VK_CONTROL))
        {
            cam->Translate({ 0.0f, -deltaTime, 0.0f });
        }
    }

    while (const auto delta = window.mouse.ReadRawDelta())
    {
        cam->Rotate(delta->x, delta->y);
    }
}
