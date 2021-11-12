#include "App.h"
#include "Cube.h"


App::App() : window(1920, 1080, "DirectX Game")
{
    for (auto i = 0; i < NUMBER_OF_CUBES; i++)
    {
        cubes.push_back(std::make_unique<Cube>(window.getGfx(), 1.0f, 10.0f, 1.0f));
        cubes[i]->SetActive(true);
    }

    window.getGfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 1.0f, 0.5f, 100.0f));

    levelLoader.ReadFile("TestLevel2.txt");


    for (size_t i = 0; i < levelLoader.numberOfCharacters; i++)
    {
        if (levelLoader.ConstructLevel(cubes[i].get()))
        {
            window.SetTitle("Level read");
        }
        else
        {
            levelLoader.PositionEnemies(cubes[i].get(), levelLoader.index);
            if(levelLoader.index < levelLoader.enemyPositions.size() -1)
            {
                levelLoader.index++;
            }
            
        }
    }

    for (size_t i = 0; i < NUMBER_OF_BULLETS; i++)
    {
        bullets.push_back(std::make_unique<Cube>(window.getGfx(), 0.05f, 0.1f, 0.05f));
        bullets[i]->SetPosition(5.0f, -5.0f, 5.0f);
        bullets[i]->SetActive(false);
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
    //window.SetTitle(std::to_string(cam->lookDir.x) + " " + std::to_string(cam->lookDir.y) + " " + std::to_string(cam->lookDir.z));
    //window.SetTitle(std::to_string(vel.x) + " " + std::to_string(vel.y) + " " + std::to_string(vel.z));
    //window.SetTitle(std::to_string(cam->GetPosition().x) + " " + std::to_string(cam->GetPosition().y) + " " + std::to_string(-cam->GetPosition().z));

    if(!bullets.empty())
    {
        for (size_t i = 0; i < NUMBER_OF_BULLETS; i++)
        {
            
            if(bullets[i]->IsActive())
            {
                bullets[i]->Update(deltaTime);
                bullets[i]->Draw(window.getGfx());
                bullets[i]->SetPosition(bullets[i]->GetPosition().x + bullets[i]->getVelocity().x * deltaTime, bullets[i]->GetPosition().y + bullets[i]->getVelocity().y * deltaTime, 
                    bullets[i]->GetPosition().z + bullets[i]->getVelocity().z * deltaTime);
            }
            
        }
    }


    for (size_t i = 0; i < levelLoader.numberOfCharacters; i++)
    {
        for (auto& bullet : bullets)
        {
            if (cubes[i]->OnCollision({bullet->GetPosition().x, bullet->GetPosition().y, bullet->GetPosition().z}))
            {
                if(cubes[i]->tag == "enemy")
                {
                    cubes[i]->SetActive(false);
                }
                //window.SetTitle("bullet collided with wall");
                bullet->SetActive(false);
            }
        }


        if(cubes[i]->IsActive())
        {
            cubes[i]->Update(deltaTime);
            cubes[i]->Draw(window.getGfx());
            if (cubes[i]->OnCollision(cam->GetPosition()))
            {
                cam->IsColliding(true);
                cam->SetSpeed(1.0f);

                vel = { cam->trans.x * deltaTime * 25 ,0.0f, cam->trans.z * deltaTime * 25 };
                if (canMove)
                {
                    cam->SetPosition(cam->GetPosition().x -
                        vel.x, cam->GetPosition().y,
                        cam->GetPosition().z - vel.z);
                }

                cube = cubes[i].get();

            }
        }

    }



    window.getGfx().SetCamera(cam->GetMatrix());






    window.getGfx().EndFrame();

}

void App::Input(float deltaTime)
{
    MovePlayer(deltaTime);
    Shoot(deltaTime);
}

void App::MovePlayer(float deltaTime)
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

void App::Shoot(float deltaTime)
{
    if(mousePressed)
    {
        shootCooldown += deltaTime;
        if(shootCooldown >= 0.3f)
        {
            mousePressed = false;
            shootCooldown = 0.0f;
        }
    }

    if(window.mouse.LeftIsPressed() && !mousePressed)
    {
        if(bulletNum >= bullets.size())
        {
            bulletNum = 0;
        }
        bullets[bulletNum]->SetActive(true);
        currentLookDir = cam->lookDir;
        bullets[bulletNum]->SetPosition(cam->GetPosition().x, cam->GetPosition().y, cam->GetPosition().z);
        bullets[bulletNum]->setVelocity({ currentLookDir.x * 100, currentLookDir.y * 100, currentLookDir.z * 100});
        bulletNum++;
        mousePressed = true;
    }

}
