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

    z_BasicShader = ZShader("Zeus/Resource/Shaders/Basic.vert", "Zeus/Resource/Shaders/Basic.frag");

    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f,  
         0.5f, -0.5f, 0.0f,  
         0.0f,  0.5f, 0.0f   
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (true)
    {
        gameWindow.Events();

        glClearColor(0.33, 0.33, 0.33, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);


        z_BasicShader.Attach();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        gameWindow.SwapBuffers();
    }
}
