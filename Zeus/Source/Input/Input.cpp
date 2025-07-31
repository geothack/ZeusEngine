#include "Core/CoreLibrary.h"
#include "Input.h"

Input& Input::Get()
{
	if (!z_Input)
	{
		z_Input = new Input();
	}

	return *z_Input;
}

bool Input::Key(int key)
{
    return z_Keyboard.Key(key);
}

bool Input::KeyWentUp(int key)
{
    return z_Keyboard.KeyWentUp(key);
}

bool Input::KeyWentDown(int key)
{
    return z_Keyboard.KeyWentDown(key);
}

void Input::Free()
{
	delete z_Input;
}
