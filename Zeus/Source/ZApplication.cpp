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

        ZRuntime.FixedUpdate();
    }
}

void ZApplication::Update()
{
    z_GameCamera = ZCamera(Vec3(0, 0, 10));

    //Log::Info(std::filesystem::current_path().string());

    z_BoxesShader = ZShader("Zeus/Resource/Shaders/Box.vert", "Zeus/Resource/Shaders/Box.frag");


    z_Plane = z_MainLevel.Create3DMeshEntity(ZTransform(Vec3(0, -5, 0)), ZPlane(), ZShader("Zeus/Resource/Shaders/Light.vert", "Zeus/Resource/Shaders/Light.frag"));
    z_Plane.AddComponent<ZBoxCollider>(ZBoxCollider(z_Boxes,z_Plane.GetPosition(),Vec3(50,1,50)));
    z_Sphere = z_MainLevel.Create3DMeshEntity(ZTransform(Vec3(-5.0, 0.0, 0.0), Vec3(0), Vec3(0.05f)), ZSphere(), ZShader("Zeus/Resource/Shaders/Light.vert", "Zeus/Resource/Shaders/Light.frag"));
    z_Sphere.AddComponent<ZBoxCollider>(ZBoxCollider(z_Boxes,Vec3(-5.0,0,0.5), Vec3(1.0)));
    z_Cube = z_MainLevel.Create3DMeshEntity(ZTransform(Vec3(0.0), Vec3(45, 0, 0)), ZCube(), ZShader("Zeus/Resource/Shaders/Basic3d.vert", "Zeus/Resource/Shaders/Basic3d.frag"));
    z_Cube.AddComponent<ZBoxCollider>(ZBoxCollider(z_Boxes,Vec3(0),Vec3(3.0)));
    z_Ship = z_MainLevel.Create3DMeshEntity(ZTransform(Vec3(5.0, 2, 0), Vec3(1.0)), ZModel("Zeus/Resource/Models/SpaceShip", "scene.gltf"), ZShader("Zeus/Resource/Shaders/AssimpModel.vert", "Zeus/Resource/Shaders/AssimpModel.frag"));
    z_Ship.AddComponent<ZBoxCollider>(ZBoxCollider(z_Boxes, Vec3(5.0,2,0), Vec3(5)));
    z_Sprite = z_MainLevel.CreateUiSpriteEntity(ZTransform(Vec3(10.0f, 540.0f, 0.0f), Vec3(270.0f, 0.0f, 0.0f), Vec3(50.0f, 50.0f, 0.0f)), ZSprite(), ZShader("Zeus/Resource/Shaders/Sprites/SpriteColored.vert", "Zeus/Resource/Shaders/Sprites/SpriteColored.frag"));
    z_Text = z_MainLevel.CreateUiTextEntity(ZTransform(Vec3(400,500,0)), ZText("Hello World", 20, { .Red = 0.33, .Green = 0.67, .Blue = 0.89 }), ZShader("Zeus/Resource/Shaders/Texts/Text.vert", "Zeus/Resource/Shaders/Texts/Text.frag"));

    ZOutput.Load("Shoot", "Zeus/Resource/Sounds/Shoot.wav");

    z_FPSController = ZFPSController(z_GameWindow, z_GameCamera);

    ZRuntime.Add(z_FPSController);

    
    while (!glfwWindowShouldClose(z_GameWindow.Get()))
    {
        z_GameWindow.Events();

        double currentTime = glfwGetTime();
        ZTime.DeltaTime = currentTime - z_LastFrame;
        z_LastFrame = currentTime;

        z_Renderer3D.Update(z_MainLevel,z_GameCamera);

        z_Renderer2D.Update(z_MainLevel);

        ZRuntime.Update();
        

        if (z_Boxes.GetPositions().size() > 0)
        {
            z_Boxes.Render(z_BoxesShader,z_GameCamera);
        }

        FixedUpdate();

        z_GameWindow.SwapBuffers();
    }

    ZLog.Free();
    ZInput.Free();
    ZOutput.Free();
    ZTime.Free();
    ZRuntime.Free();
}
