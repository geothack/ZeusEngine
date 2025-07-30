#include "Core/CoreLibrary.h"
#include "ZCamera.h"

ZCamera::ZCamera(Vec3 position, Vec3 up, const float yaw, const float pitch)
    : z_Front(glm::vec3(0.0f, 0.0f, -1.0f)), z_MovementSpeed(2.5f), z_MouseSensitivity(0.1f), z_Zoom(45.0f)
{
    z_Position = position;
    z_WorldUp = up;
    z_Yaw = yaw;
    z_Pitch = pitch;
    UpdateCameraVectors();
}

ZCamera::ZCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : z_Front(glm::vec3(0.0f, 0.0f, -1.0f)), z_MovementSpeed(2.5f), z_MouseSensitivity(0.1f), z_Zoom(45.0f)
{
    z_Position = glm::vec3(posX, posY, posZ);
    z_WorldUp = glm::vec3(upX, upY, upZ);
    z_Yaw = yaw;
    z_Pitch = pitch;
    UpdateCameraVectors();
}

glm::mat4 ZCamera::GetViewMatrix()
{
    return glm::lookAt(z_Position, z_Position + z_Front, z_Up);
}

void ZCamera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= z_MouseSensitivity;
    yoffset *= z_MouseSensitivity;

    z_Yaw += xoffset;
    z_Pitch += yoffset;

    if (constrainPitch)
    {
        if (z_Pitch > 89.0f)
        {
            z_Pitch = 89.0f;
        }
        if (z_Pitch < -89.0f)
        {
            z_Pitch = -89.0f;
        }
    }

    UpdateCameraVectors();
}

void ZCamera::ProcessMouseScroll(float yoffset)
{
    z_Zoom -= (float)yoffset;
    if (z_Zoom < 1.0f)
    {
        z_Zoom = 1.0f;
    }
    if (z_Zoom > 45.0f)
    {
        z_Zoom = 45.0f;
    }
}

void ZCamera::MoveForward(float amt)
{
    z_Position += -z_Front * amt;
}

void ZCamera::MoveBack(float amt)
{
    z_Position += z_Front * amt;
}

void ZCamera::MoveDown(float amt)
{
    z_Position -= z_Up * amt;
}

void ZCamera::MoveUp(float amt)
{
    z_Position += z_Up * amt;
}

void ZCamera::MoveRight(float amt)
{
    z_Position += glm::cross(z_Up, z_Front) * amt;
}

void ZCamera::MoveLeft(float amt)
{
    z_Position -= glm::cross(z_Up, z_Front) * amt;
}

void ZCamera::UpdateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(z_Yaw)) * cos(glm::radians(z_Pitch));
    front.y = sin(glm::radians(z_Pitch));
    front.z = sin(glm::radians(z_Yaw)) * cos(glm::radians(z_Pitch));
    z_Front = glm::normalize(front);

    z_Right = glm::normalize(glm::cross(z_Front, z_WorldUp));
    z_Up = glm::normalize(glm::cross(z_Right, z_Front));
}