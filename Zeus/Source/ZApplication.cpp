#include "Core/CoreLibrary.h"
#include "ZApplication.h"

ZApplication::ZApplication()
{
}

ZApplication::~ZApplication()
{
}

void ZApplication::FixedUpdate()
{
    z_TimeStep += ZTime.DeltaTime * 150.0f;
    while (z_TimeStep >= z_GameWindow.GetVideoMode()->refreshRate)
    {
        z_TimeStep -= z_GameWindow.GetVideoMode()->refreshRate;

        // Run entity fixed update here
    }
}

void ZApplication::Update()
{
    z_GameCamera = ZCamera(Vec3(0, 0, 10));

    //Log::Info(std::filesystem::current_path().string());

    z_BoxesShader = ZShader("Zeus/Resource/Shaders/Box.vert", "Zeus/Resource/Shaders/Box.frag");


    z_Plane = z_MainLevel.Create3DMeshEntity(ZTransform(Vec3(0, -5, 0)), ZPlane(), ZShader("Zeus/Resource/Shaders/Light.vert", "Zeus/Resource/Shaders/Light.frag"));
    z_Sphere = z_MainLevel.Create3DMeshEntity(ZTransform(Vec3(-5.0, 0.0, 0.0), Vec3(0), Vec3(0.05f)), ZSphere(), ZShader("Zeus/Resource/Shaders/Light.vert", "Zeus/Resource/Shaders/Light.frag"));
    z_Cube = z_MainLevel.Create3DMeshEntity(ZTransform(Vec3(0.0), Vec3(45, 0, 0)), ZCube(), ZShader("Zeus/Resource/Shaders/Basic3d.vert", "Zeus/Resource/Shaders/Basic3d.frag"));
    z_Ship = z_MainLevel.Create3DMeshEntity(ZTransform(Vec3(2.5, 2, 0), Vec3(1.0)), ZModel("Zeus/Resource/Models/SpaceShip", "scene.gltf"), ZShader("Zeus/Resource/Shaders/AssimpModel.vert", "Zeus/Resource/Shaders/AssimpModel.frag"));
    z_Sprite = z_MainLevel.CreateUiSpriteEntity(ZTransform(Vec3(10.0f, 540.0f, 0.0f), Vec3(270.0f, 0.0f, 0.0f), Vec3(50.0f, 50.0f, 0.0f)), ZSprite(), ZShader("Zeus/Resource/Shaders/Sprites/SpriteColored.vert", "Zeus/Resource/Shaders/Sprites/SpriteColored.frag"));
    z_Text = z_MainLevel.CreateUiTextEntity(ZTransform(Vec3(400,500,0)), ZText("Hello World", 20, { .Red = 0.33, .Green = 0.67, .Blue = 0.89 }), ZShader("Zeus/Resource/Shaders/Texts/Text.vert", "Zeus/Resource/Shaders/Texts/Text.frag"));

    ZOutput.Load("Shoot", "Zeus/Resource/Sounds/Shoot.wav");

    //glfwSetInputMode(z_GameWindow.Get(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    //glfwSetInputMode(z_GameWindow.Get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    while (!glfwWindowShouldClose(z_GameWindow.Get()))
    {
        z_GameWindow.Events();

        double currentTime = glfwGetTime();
        ZTime.DeltaTime = currentTime - z_LastFrame;
        z_LastFrame = currentTime;

        FixedUpdate();

        z_Renderer3D.Update(z_MainLevel,z_GameCamera);

        z_Renderer2D.Update(z_MainLevel);

        if (ZInput.Key(GLFW_KEY_A))
        {
            z_GameCamera.MoveLeft(-1.0f);
        }

        if (ZInput.Key(GLFW_KEY_D))
        {
            z_GameCamera.MoveLeft(1.0f);
        }

        if (ZInput.Key(GLFW_KEY_W))
        {
            z_GameCamera.MoveForward(-1.0f);
        }

        if (ZInput.Key(GLFW_KEY_S))
        {
            z_GameCamera.MoveForward(1.0f);
        }

        if (ZInput.Key(GLFW_KEY_SPACE))
        {
            z_GameCamera.MoveUp(1.0f);
        }

        if (ZInput.Key(GLFW_KEY_LEFT_SHIFT))
        {
            z_GameCamera.MoveUp(-1.0f);
        }

        if (ZInput.KeyWentDown(GLFW_KEY_B))
        {
            z_Boxes.GetPositions().push_back(Vec3(z_Boxes.GetPositions().size() * 1.0f));
            z_Boxes.GetScales().push_back(Vec3(z_Boxes.GetScales().size() * 1.0f));
        }

        if (ZInput.KeyWentDown(GLFW_KEY_P))
        {
            ZOutput.Play("Shoot");
        }


        if (z_Boxes.GetPositions().size() > 0)
        {
            z_Boxes.Render(z_BoxesShader,z_GameCamera);
        }

        /*auto dx = ZInput.GetMouse().GetDX();
        auto dy = ZInput.GetMouse().GetDY();
        if (dx != 0 || dy != 0)
        {
            z_GameCamera.ProcessMouseMovement(dx, dy);
        }*/

        z_GameWindow.SwapBuffers();
    }

    ZLog.Free();
    ZInput.Free();
    ZOutput.Free();
    ZTime.Free();
}
