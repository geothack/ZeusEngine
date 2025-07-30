#include "Core/CoreLibrary.h"
#include "ZMouse.h"

double ZMouse::GetMouseX()
{
	return z_X;
}

double ZMouse::GetMouseY()
{
	return z_Y;
}

double ZMouse::GetDX()
{
	double _dx = z_Dx;
	z_Dx = 0;
	return _dx;
}

double ZMouse::GetDY()
{
	double _dy = z_Dy;
	z_Dy = 0;
	return _dy;
}

double ZMouse::GetScrollDX()
{
	double _scrollDx = z_ScrollDx;
	z_ScrollDx = 0;
	return _scrollDx;
}

double ZMouse::GetScrollDY()
{
	double _scrollDy = z_ScrollDy;
	z_ScrollDy = 0;
	return _scrollDy;
}

bool ZMouse::Button(int button)
{
	return z_Buttons[button];
}

bool ZMouse::ButtonChanged(int button)
{
	bool ret = z_ButtonsChanged[button];
	z_ButtonsChanged[button] = false;
	return ret;
}

bool ZMouse::ButtonWentUp(int button)
{
	return !z_Buttons[button] && ButtonChanged(button);
}

bool ZMouse::ButtonWentDown(int button)
{
	return z_Buttons[button] && ButtonChanged(button);
}

void ZMouse::SetPosition(double _x, double _y)
{
	z_X = _x;
	z_Y = _y;

	if (z_FirstMouse)
	{
		z_LastX = z_X;
		z_LastY = z_Y;
		z_FirstMouse = false;
	}

	z_Dx = z_X - z_LastX;
	z_Dy = z_LastY - z_Y;
	z_LastX = z_X;
	z_LastY = z_Y;
}

void ZMouse::SetButtons(int button, int action)
{
	if (action != GLFW_RELEASE)
	{
		if (!z_Buttons[button])
		{
			z_Buttons[button] = true;
		}
	}
	else
	{
		z_Buttons[button] = false;
	}
	z_ButtonsChanged[button] = action != GLFW_REPEAT;
}

void ZMouse::SetWheel(double _Dx, double _Dy)
{
	z_ScrollDx = _Dx;
	z_ScrollDy = _Dy;
}
