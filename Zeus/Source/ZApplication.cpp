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

    ZUniforms.Create("Camera", sizeof(CameraData), 0);
    ZUniforms.Update("Camera", 0, glm::value_ptr(z_CameraData.View), sizeof(z_CameraData.View));
    ZUniforms.Update("Camera", sizeof(z_CameraData.Projection), glm::value_ptr(z_CameraData.Projection), sizeof(z_CameraData.Projection));


    z_Cube2 = z_MainLevel.Create3DMeshEntity(ZTransform(Vec3(-7.5, 0, 0), Vec3(45, 0, 0)), ZCube(), ZShader("Zeus/Resource/Shaders/Lighting/TEADS.vert", "Zeus/Resource/Shaders/Lighting/TEADS.frag", { .Red = -1, .Green = -1, .Blue = -1 },"",{ ZTexture("diffues0","Zeus/Resource/Textures/Wood.png") },true));
    z_Cube2.AddComponent<ZBoxCollider>(ZBoxCollider(z_Boxes, Vec3(0), Vec3(3.0)));

    z_Plane = z_MainLevel.Create3DMeshEntity(ZTransform(Vec3(0, -5, 0)), ZPlane(), ZShader("Zeus/Resource/Shaders/Lighting/ADS.vert", "Zeus/Resource/Shaders/Lighting/ADS.frag", { .Red = 0.33, .Green = 0.33, .Blue = 0.33 }));
    z_Plane.AddComponent<ZBoxCollider>(ZBoxCollider(z_Boxes,z_Plane.GetPosition(),Vec3(50,1,50)));
    z_Sphere = z_MainLevel.Create3DMeshEntity(ZTransform(Vec3(-5.0, 0.0, 0.0), Vec3(0), Vec3(0.05f)), ZSphere(), ZShader("Zeus/Resource/Shaders/Lighting/ADS.vert", "Zeus/Resource/Shaders/Lighting/ADS.frag", { .Red = 1.0, .Green = 0.0, .Blue = 0.23 }));
    z_Sphere.AddComponent<ZBoxCollider>(ZBoxCollider(z_Boxes,Vec3(-5.0,0,0.5), Vec3(1.0)));
    z_Cube = z_MainLevel.Create3DMeshEntity(ZTransform(Vec3(0.0), Vec3(45, 0, 0)), ZCube(), ZShader("Zeus/Resource/Shaders/Lighting/ADS.vert", "Zeus/Resource/Shaders/Lighting/ADS.frag", { .Red = 0.0, .Green = 0.67, .Blue = 0.89 }));
    z_Cube.AddComponent<ZBoxCollider>(ZBoxCollider(z_Boxes,Vec3(0),Vec3(3.0)));
    z_Ship = z_MainLevel.Create3DMeshEntity(ZTransform(Vec3(5.0, 2, 0), Vec3(1.0)), ZModel("Zeus/Resource/Models/SpaceShip", "scene.gltf"), ZShader("Zeus/Resource/Shaders/Lighting/AssimpEADS.vert", "Zeus/Resource/Shaders/Lighting/AssimpEADS.frag", { .Red = -1, .Green = -1, .Blue = -1 }, "", {},true));
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

        z_CameraData.View = z_GameCamera.GetViewMatrix();
        z_CameraData.Projection = glm::perspective(glm::radians(45.0f), (float)ZWindow::GetSize().Width / (float)ZWindow::GetSize().Height, 0.1f, 100.0f);
        ZUniforms.Update("Camera", 0, glm::value_ptr(z_CameraData.View), sizeof(z_CameraData.View));
        ZUniforms.Update("Camera", sizeof(z_CameraData.Projection), glm::value_ptr(z_CameraData.Projection), sizeof(z_CameraData.Projection));

        z_Renderer3D.Update(z_MainLevel,z_GameCamera,z_Boxes,z_Skybox);

        z_Renderer2D.Update(z_MainLevel);

        ZRuntime.Update();

        FixedUpdate();

        z_GameWindow.SwapBuffers();
    }

    ZLog.Free();
    ZInput.Free();
    ZUniforms.Free();
    ZOutput.Free();
    ZTime.Free();
    ZRuntime.Free();
}
