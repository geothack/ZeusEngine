#include "Core/CoreLibrary.h"
#include "ZKeyboard.h"

void ZKeyboard::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_RELEASE)
    {
        if (!z_Keys[key])
        {
            z_Keys[key] = true;
        }
    }
    else
    {
        z_Keys[key] = false;
    }
    z_KeysChanged[key] = action != GLFW_REPEAT;
}

bool ZKeyboard::Key(int key)
{
	return z_Keys[key];
}

bool ZKeyboard::KeyChanged(int key)
{
	bool ret = z_KeysChanged[key];
	z_KeysChanged[key] = false;
	return ret;
}

bool ZKeyboard::KeyWentUp(int key)
{
	return !z_Keys[key] && KeyChanged(key);
}

bool ZKeyboard::KeyWentDown(int key)
{
	return z_Keys[key] && KeyChanged(key);
}
