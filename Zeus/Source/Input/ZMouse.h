#pragma once


class ZMouse
{
public:
    ZMouse() = default;

    double GetMouseX();
    double GetMouseY();

    double GetDX();
    double GetDY();

    double GetScrollDX();
    double GetScrollDY();

    bool Button(int button);
    bool ButtonChanged(int button);
    bool ButtonWentUp(int button);
    bool ButtonWentDown(int button);

    void SetPosition(double _x, double _y);
    void SetButtons(int button, int action);
    void SetWheel (double _Dx, double _Dy);

private:
    double z_X;
    double z_Y;
           
    double z_LastX;
    double z_LastY;
           
    double z_Dx;
    double z_Dy;
           
    double z_ScrollDx;
    double z_ScrollDy;

    bool z_FirstMouse;

    bool z_Buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
    bool z_ButtonsChanged[GLFW_MOUSE_BUTTON_LAST] = { 0 };
};

