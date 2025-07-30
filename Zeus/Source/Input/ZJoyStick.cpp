#include "Core/CoreLibrary.h"
#include "ZJoyStick.h"

ZJoyStick::ZJoyStick(int i)
{
	z_Id = GetId(i);

	Update();
}

void ZJoyStick::Update()
{
	z_Present = glfwJoystickPresent(z_Id);

	if (z_Present)
	{
		z_Name = glfwGetJoystickName(z_Id);
		z_Axes = glfwGetJoystickAxes(z_Id, &z_AxesCount);
		z_Buttons = glfwGetJoystickButtons(z_Id, &z_ButtonCount);
	}
}

float ZJoyStick::AxesState(int axis)
{
	if (z_Present) 
	{
		return z_Axes[axis];
	}

	return -1;
}

unsigned char ZJoyStick::ButtonState(int button)
{
	if (z_Present)
	{
		return z_Buttons[button];
	}

	return GLFW_RELEASE;
}

int ZJoyStick::GetAxesCount()
{
	return z_AxesCount;
}

int ZJoyStick::GetButtonCount()
{
	return z_ButtonCount;
}

bool ZJoyStick::IsPresent()
{
	return z_Present;
}

const char* ZJoyStick::GetName()
{
	return z_Name;
}

int ZJoyStick::GetId(int i)
{
	return GLFW_JOYSTICK_1 + i;
}
