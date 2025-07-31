#include "Core/CoreLibrary.h"
#include "ZFPSController.h"

ZFPSController::ZFPSController(ZWindow& window, ZCamera& camera) : z_FPSCamera(&camera)
{
    glfwSetInputMode(window.Get(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetInputMode(window.Get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

ZFPSController::~ZFPSController()
{
}

void ZFPSController::Start()
{
}

void ZFPSController::FixedUpdate()
{
}

void ZFPSController::Update()
{
    if (ZInput.Key(GLFW_KEY_A))
    {
        z_FPSCamera->MoveLeft(-1.0f);
    }

    if (ZInput.Key(GLFW_KEY_D))
    {
        z_FPSCamera->MoveLeft(1.0f);
    }

    if (ZInput.Key(GLFW_KEY_W))
    {
        z_FPSCamera->MoveForward(-1.0f);
    }

    if (ZInput.Key(GLFW_KEY_S))
    {
        z_FPSCamera->MoveForward(1.0f);
    }

    if (ZInput.Key(GLFW_KEY_SPACE))
    {
        z_FPSCamera->MoveUp(1.0f);
    }

    if (ZInput.Key(GLFW_KEY_LEFT_SHIFT))
    {
        z_FPSCamera->MoveUp(-1.0f);
    }

    if (ZInput.KeyWentDown(GLFW_KEY_P))
    {
        ZOutput.Play("Shoot");
    }


    auto dx = ZInput.GetMouse().GetDX();
    auto dy = ZInput.GetMouse().GetDY();
    if (dx != 0 || dy != 0)
    {
        z_FPSCamera->ProcessMouseMovement(dx, dy);
    }
}
