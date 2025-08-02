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

void ZApplication::Update(ZLevel& level, ZCamera& activeCamera, ZSkybox* skyBox)
{
    ZUniforms.Create("Camera", sizeof(CameraData), 0);
    ZUniforms.Update("Camera", 0, glm::value_ptr(z_CameraData.View), sizeof(z_CameraData.View));
    ZUniforms.Update("Camera", sizeof(z_CameraData.Projection), glm::value_ptr(z_CameraData.Projection), sizeof(z_CameraData.Projection));

    Boxes.Init();
    
    while (!glfwWindowShouldClose(ZWindow::Get()))
    {
        z_GameWindow.Events();

        double currentTime = glfwGetTime();
        ZTime.DeltaTime = currentTime - z_LastFrame;
        z_LastFrame = currentTime;

        z_CameraData.View = activeCamera.GetViewMatrix();
        z_CameraData.Projection = glm::perspective(glm::radians(45.0f), (float)ZWindow::GetSize().Width / (float)ZWindow::GetSize().Height, 0.1f, 100.0f);
        ZUniforms.Update("Camera", 0, glm::value_ptr(z_CameraData.View), sizeof(z_CameraData.View));
        ZUniforms.Update("Camera", sizeof(z_CameraData.Projection), glm::value_ptr(z_CameraData.Projection), sizeof(z_CameraData.Projection));

        //z_Ship.GetComponent<ZTransform>().SetPosition(Vec3(glm::sin(currentTime * glm::two_pi<float>() * 0.1) * 15.0, z_Ship.GetPosition().y, z_Ship.GetPosition().z));

        z_Renderer3D.Update(level, activeCamera, skyBox);

        z_Renderer2D.Update(level);

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
