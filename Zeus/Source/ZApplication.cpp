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

    z_GameCamera = ZCamera(Vec3(0, 0, 10));

    //Log::Info(std::filesystem::current_path().string());

    z_BasicShader = ZShader("Zeus/Resource/Shaders/Basic3d.vert", "Zeus/Resource/Shaders/Basic3d.frag");
    z_LightShader = ZShader("Zeus/Resource/Shaders/Light.vert", "Zeus/Resource/Shaders/Light.frag");
    z_ShipShader = ZShader("Zeus/Resource/Shaders/AssimpModel.vert", "Zeus/Resource/Shaders/AssimpModel.frag");
    z_BoxesShader = ZShader("Zeus/Resource/Shaders/Box.vert", "Zeus/Resource/Shaders/Box.frag");

    z_Sphere = ZSphere(ZTransform(Vec3(-5.0,0.0,0.0), Vec3(0), Vec3(0.05f)));
    z_Sphere.Init();

    z_BasicCube = ZCube(ZTransform(Vec3(0.0),Vec3(45,0,0)));
    z_BasicCube.Init();

    z_Plane = ZPlane(ZTransform(Vec3(0,-5,0)));
    z_Plane.Init();

    z_Ship = ZModel(ZTransform(Vec3(2.5, 2, 0),Vec3(1.0)));
    z_Ship.Load("Zeus/Resource/Models/SpaceShip", "scene.gltf");

    z_Boxes.Init();

    //glfwSetInputMode(gameWindow.Get(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    //glfwSetInputMode(gameWindow.Get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(gameWindow.Get()))
    {
        gameWindow.Events();

        double currentTime = glfwGetTime();
        z_DeltaTime = currentTime - z_LastFrame;
        z_LastFrame = currentTime;

        glClearColor(0.33, 0.33, 0.33, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        z_BasicCube.Render(z_BasicShader, z_GameCamera);

        z_Sphere.Render(z_LightShader, z_GameCamera);

        z_Ship.Render(z_ShipShader, z_GameCamera);

        z_Plane.Render(z_LightShader, z_GameCamera);

        if (ZInput->Key(GLFW_KEY_A))
        {
            z_GameCamera.MoveLeft(-1.0f);
        }

        if (ZInput->Key(GLFW_KEY_D))
        {
            z_GameCamera.MoveLeft(1.0f);
        }

        if (ZInput->Key(GLFW_KEY_W))
        {
            z_GameCamera.MoveForward(-1.0f);
        }

        if (ZInput->Key(GLFW_KEY_S))
        {
            z_GameCamera.MoveForward(1.0f);
        }

        if (ZInput->Key(GLFW_KEY_SPACE))
        {
            z_GameCamera.MoveUp(1.0f);
        }

        if (ZInput->Key(GLFW_KEY_LEFT_SHIFT))
        {
            z_GameCamera.MoveUp(-1.0f);
        }

        if (ZInput->KeyWentDown(GLFW_KEY_B))
        {
            z_Boxes.GetPositions().push_back(Vec3(z_Boxes.GetPositions().size() * 1.0f));
            z_Boxes.GetScales().push_back(Vec3(z_Boxes.GetScales().size() * 1.0f));
        }


        if (z_Boxes.GetPositions().size() > 0)
        {
            z_Boxes.Render(z_BoxesShader,z_GameCamera);
        }

        /*auto dx = ZInput->GetMouse().GetDX();
        auto dy = ZInput->GetMouse().GetDY();
        if (dx != 0 || dy != 0)
        {
            z_GameCamera.ProcessMouseMovement(dx, dy);
        }*/

        gameWindow.SwapBuffers();
    }
}
