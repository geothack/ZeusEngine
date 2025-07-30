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

    z_BasicCube = ZCube(ZTransform(Vec3(0.0),Vec3(45,0,0)));
    z_BasicCube.Init();

    while (true)
    {
        gameWindow.Events();

        glClearColor(0.33, 0.33, 0.33, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        z_BasicShader.Attach();
        Mat4 view = Mat4(1.0f);
        Mat4 projection = Mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
        z_BasicShader.SetMat4("Projection", projection);
        z_BasicShader.SetMat4("View", view);
        z_BasicCube.Render(z_BasicShader);
        

        gameWindow.SwapBuffers();
    }
}
