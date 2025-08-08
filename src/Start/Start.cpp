#include "Start/Start.hpp"

void Start::Initialize(int num)
{
}
void Start::Finalize()
{
}
void Start::Update()
{

}
void Start::Draw()
{
    DrawStringToHandle(1280/2-180*(2.0f/2+3.0f)/2.0f+10.0f, 720/2-200+10.0f, _T("3Dオセロ"), GetColor(0,0,0), FontHandle);
    DrawStringToHandle(1280/2-180*(2.0f/2+3.0f)/2.0f, 720/2-200, _T("3Dオセロ"), GetColor(255, 255, 255), FontHandle);
    float base_size_x = 200;
    float base_size_y = 80;
    float hover_size_x = 220;
    float hover_size_y = 100;
    int X, Y;
    GetMousePoint(&X, &Y);
    float pointx = 1280 / 2;
    float pointy = 500;
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
        DrawStringToHandle(1280/2-5*90/4, pointy-90/2, _T("Start"), GetColor(0, 0, 0), FontHandle2);
        int ClickX, ClickY, Button, LogType;
        if (GetMouseInputLog2(&Button, &ClickX, &ClickY, &LogType, TRUE) == 0)
        {
            // 左ボタンが押されたり離されたりしていたら描画するかどうかのフラグを立てて、座標も保存する
            if (Button == MOUSE_INPUT_LEFT && LogType == MOUSE_INPUT_LOG_DOWN)
            {
                if (1280/2 - hover_size_x < ClickX && 1280/2 + hover_size_x > ClickX)
                {
                    if (500 - hover_size_y < ClickY && 500 + hover_size_y > ClickY)
                    {
                        ChangeScene(); // 例として、次のシーンに変更
                    }
                }
            }
        }
}
void Start::ChangeScene(int num)
{
    manager.lock()->ChangeScene(num); 
}