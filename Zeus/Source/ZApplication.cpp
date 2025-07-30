#include "Core/CoreLibrary.h"
#include "ZApplication.h"

ZApplication::ZApplication()
{
}

ZApplication::~ZApplication()
{
}

void ZApplication::Update()
{
    auto gameWindow = ZWindow("Game", 800, 600);

    //Log::Info(std::filesystem::current_path().string());

    z_BasicShader = ZShader("Zeus/Resource/Shaders/Basic3d.vert", "Zeus/Resource/Shaders/Basic3d.frag");
    z_LightShader = ZShader("Zeus/Resource/Shaders/Light.vert", "Zeus/Resource/Shaders/Light.frag");
    z_TrollShader = ZShader("Zeus/Resource/Shaders/Troll.vert", "Zeus/Resource/Shaders/Troll.frag");
    z_ShipShader = ZShader("Zeus/Resource/Shaders/Troll.vert", "Zeus/Resource/Shaders/Troll.frag");

    z_Sphere = ZSphere(ZTransform(Vec3(-5.0,0.0,0.0), Vec3(0), Vec3(0.05f)));
    z_Sphere.Init();

    z_BasicCube = ZCube(ZTransform(Vec3(0.0),Vec3(45,0,0)));
    z_BasicCube.Init();

    z_Plane = ZPlane(ZTransform(Vec3(0,-12,-25)));
    z_Plane.Init();

    z_Troll = ZModel(ZTransform(Vec3(5, 0, 0),Vec3(0.0),Vec3(0.0127f)));
    z_Troll.Load("Zeus/Resource/Models/Troll", "scene.gltf");
    z_Ship = ZModel(ZTransform(Vec3(2.5, 2, 0),Vec3(1.0)));
    z_Ship.Load("Zeus/Resource/Models/SpaceShip", "scene.gltf");

    while (true)
    {
        gameWindow.Events();

        glClearColor(0.33, 0.33, 0.33, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        z_BasicCube.Render(z_BasicShader);

        z_Troll.Render(z_TrollShader);

        z_Sphere.Render(z_LightShader);

        z_Ship.Render(z_ShipShader);

        z_Plane.Render(z_LightShader);

        gameWindow.SwapBuffers();
    }
}
