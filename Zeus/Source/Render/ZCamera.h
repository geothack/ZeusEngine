#pragma once


class ZCamera
{
public:
    ZCamera(Vec3 position = Vec3(0.0f), Vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), const float yaw = -90.0f, const float pitch = 0.0f);

    ZCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    void ProcessMouseScroll(float yoffset);

    void MoveForward(float amt);
    void MoveBack(float amt);
    void MoveDown(float amt);
    void MoveUp(float amt);
    void MoveRight(float amt);
    void MoveLeft(float amt);



    glm::mat4 GetViewMatrix();

    glm::vec3 GetPos() { return z_Position; }
    glm::vec3 GetFront() { return z_Front; }

private:
    void UpdateCameraVectors();

    glm::vec3 z_Position;
    glm::vec3 z_Front;
    glm::vec3 z_Up;
    glm::vec3 z_Right;
    glm::vec3 z_WorldUp;

    float z_Yaw;
    float z_Pitch;

    float z_MovementSpeed;
    float z_MouseSensitivity;
    float z_Zoom;
};

