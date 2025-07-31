#pragma once

#include "Input/ZKeyboard.h"
#include "Input/ZMouse.h"

class Input
{
public:
	static Input& Get();

	bool Key(int key);

	bool KeyWentUp(int key);

	bool KeyWentDown(int key);

	void Free();

	ZMouse& GetMouse() { return z_Mouse; }

private:
	inline static Input* z_Input = nullptr;

	ZKeyboard z_Keyboard;
	ZMouse z_Mouse;
};

