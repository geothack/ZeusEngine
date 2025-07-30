#include "Core/CoreLibrary.h"
#include "Input.h"

Input* Input::Get()
{
	if (!mInput)
	{
		mInput = new Input();
	}

	return mInput;
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
	delete mInput;
}
