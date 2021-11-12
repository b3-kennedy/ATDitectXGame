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

    cam->SetPosition(5.0f, -5.0f, 5.0f);




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
    window.SetTitle(std::to_string(cam->lookDir.x) + " " + std::to_string(cam->lookDir.y) + " " + std::to_string(cam->lookDir.z));
    //window.SetTitle(std::to_string(vel.x) + " " + std::to_string(vel.y) + " " + std::to_string(vel.z));

    //window.SetTitle(std::to_string(cam->GetPosition().x) + " " + std::to_string(cam->GetPosition().y) + " " + std::to_string(-cam->GetPosition().z));

    if (cube != nullptr)
    {
        if (cube->OnCollisionExit(cam.get()))
        {
            window.SetTitle("exit");
        }
    }


    for (size_t i = 0; i < NUMBER_OF_CUBES; i++)
    {
        cubes[i]->Update(deltaTime);
        cubes[i]->Draw(window.getGfx());
        if (cubes[i]->OnCollision(cam.get()))
        {
            cam->IsColliding(true);
            
            cam->SetSpeed(1.0f);







            vel = { cam->trans.x * deltaTime * 25 ,0.0f, cam->trans.z * deltaTime * 25 };
            if(canMove)
            {
                cam->SetPosition(cam->GetPosition().x - 
                    vel.x, cam->GetPosition().y, 
                    cam->GetPosition().z - vel.z);
            }
            
            






            
            cube = cubes[i].get();
            
        }
    }



    window.getGfx().SetCamera(cam->GetMatrix());






    window.getGfx().EndFrame();

}

void App::Input(float deltaTime)
{
    if (canInput)
    {


        if (canMove)
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


        //if((cam->lookDir.x > 0.8f || cam->lookDir.x < -0.8f) || (cam->lookDir.z > 0.8f || cam->lookDir.z < -0.8f))
        //{
        //    window.SetTitle("test");
        //    if (window.keyboard.KeyIsPressed('W') && window.keyboard.KeyIsPressed('A') && cam->Colliding())
        //    {
        //        canMove = false;
        //        cam->trans = { 0.0f,0.0f,0.0f };
        //        vel = { 0.0f,0.0f,0.0f };
        //    }
        //    else if (window.keyboard.KeyIsPressed('W') && window.keyboard.KeyIsPressed('D') && cam->Colliding())
        //    {
        //        canMove = false;
        //        window.SetTitle("yo");
        //        cam->trans = { 0.0f,0.0f,0.0f };
        //        vel = { 0.0f,0.0f,0.0f };

        //    }
        //    else if (window.keyboard.KeyIsPressed('S') && window.keyboard.KeyIsPressed('A') && cam->Colliding())
        //    {
        //        canMove = false;
        //        window.SetTitle("yo");
        //        cam->trans = { 0.0f,0.0f,0.0f };
        //        vel = { 0.0f,0.0f,0.0f };
        //    }
        //    else if (window.keyboard.KeyIsPressed('S') && window.keyboard.KeyIsPressed('D') && cam->Colliding())
        //    {
        //        canMove = false;
        //        window.SetTitle("yo");
        //        cam->trans = { 0.0f,0.0f,0.0f };
        //        vel = { 0.0f,0.0f,0.0f };
        //    }
        //    else
        //    {
        //        canMove = true;
        //    }
        //}


    }

    while (const auto delta = window.mouse.ReadRawDelta())
    {
        cam->Rotate(delta->x, delta->y);
    }
}
