#include "Select/Select.hpp"

void Select::Initialize(int num)
{
}
void Select::Finalize()
{
}
void Select::Update()
{

}
void Select::Draw()
{
    DrawStringToHandle(50, 25, _T("Select Size"), GetColor(255, 255, 255), FontHandle);
    float base_size_x = 200;
    float base_size_y = 80;
    float hover_size_x = 220;
    float hover_size_y = 100;
    int X, Y;
    GetMousePoint(&X, &Y);
    for (int i = 0; i < 3; i++)
    {
        float pointx = 1280 / 2;
        float pointy = 200 + 200 * i;
        if (ishover)
        {
            if (!(pointx - hover_size_x < X && pointy - hover_size_y < Y && pointx + hover_size_x > X && pointy + hover_size_y > Y))
                ishover = false;
        }
        else
        {
            if (pointx - base_size_x < X && pointy - base_size_y < Y && pointx + base_size_x > X && pointy + base_size_y > Y)
                ishover = true;
        }
        if (ishover)
        {
            DrawBoxAA(pointx - hover_size_x, pointy - hover_size_y, pointx + hover_size_x, pointy + hover_size_y, GetColor(255, 255, 255), TRUE);

        }
        else
        {
            DrawBoxAA(pointx - base_size_x, pointy - base_size_y, pointx + base_size_x, pointy + base_size_y, GetColor(255, 255, 255), TRUE);
        }
                    switch(i)
            {
                case 0:
                    DrawStringToHandle(pointx - FontSize*5/4, pointy - FontSize/2, _T("4x4x4"), GetColor(0, 0, 0), FontHandle);
                    break;
                case 1:
                    DrawStringToHandle(pointx - FontSize*5/4, pointy  -FontSize/2, _T("6x6x6"), GetColor(0, 0, 0), FontHandle);
                    break;
                case 2:
                    DrawStringToHandle(pointx - FontSize*5/4, pointy - FontSize/2, _T("8x8x8"), GetColor(0, 0, 0), FontHandle);
                    break;

            }
    }
        int ClickX, ClickY, Button, LogType;
        if (GetMouseInputLog2(&Button, &ClickX, &ClickY, &LogType, TRUE) == 0)
        {
            if (Button == MOUSE_INPUT_LEFT && LogType == MOUSE_INPUT_LOG_DOWN)
            {
                if (1280/2 - hover_size_x < ClickX && 1280/2 + hover_size_x > ClickX)
                {
                    if (200 - hover_size_y < ClickY && 200 + hover_size_y > ClickY)
                    {
                        num = 4;
                        ChangeScene(2); 
                    }
                    if (400 - hover_size_y < ClickY && 400 + hover_size_y > ClickY)
                    {
                        num = 6;
                        ChangeScene(2); 
                    }
                    if (600 - hover_size_y < ClickY && 600 + hover_size_y > ClickY)
                    {
                        num = 8;
                        ChangeScene(2); 
                    }
                }
            }
        }
}
void Select::ChangeScene(int num)
{
    // シーン変更の処理
    manager.lock()->ChangeScene(num); 
}