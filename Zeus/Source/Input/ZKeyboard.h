#pragma once


class ZKeyboard
{
public:
    ZKeyboard() = default;

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    bool Key(int key);
    
    bool KeyChanged(int key);
    
    bool KeyWentUp(int key);

    bool KeyWentDown(int key);

private:
    inline static bool z_Keys[GLFW_KEY_LAST] = { 0 };
    inline static bool z_KeysChanged[GLFW_KEY_LAST] = { 0 };
};

