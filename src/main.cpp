#include "DxLib.h"
#include "Manager.hpp"
#include "Scene.hpp"
#include "Othello/3DOthello.hpp"
#include "Start/Start.hpp"
#include "Select/Select.hpp"
#include <memory>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // ウインドウモードで起動
    ChangeWindowMode(TRUE);
    SetGraphMode(1280, 720, 32);

    // ＤＸライブラリの初期化
    if (DxLib_Init() < 0)
    {
        return 0;
    }
    SetBackgroundColor(24, 123, 49);
    // 描画先を裏画面に変更
    SetDrawScreen(DX_SCREEN_BACK);
    std::shared_ptr<Manager> manager= std::make_shared<Manager>();
    std::unique_ptr<Start> start_Scene=std::make_unique<Start>(manager);
    std::unique_ptr<Select> select_Scene=std::make_unique<Select>(manager);
    std::unique_ptr<_3DOthello> _3DOthello_Scene=std::make_unique<_3DOthello>(manager);
    manager->AddScene(std::move(start_Scene));
    manager->AddScene(std::move(select_Scene));
    manager->AddScene(std::move(_3DOthello_Scene));
    // メインループ
    while (ProcessMessage() != -1)
    {
        // 画面をクリア
        ClearDrawScreen();
        manager->Update();
        // 裏画面の内容を表画面に反映する
        ScreenFlip();
    }
    // ＤＸライブラリの後始末
    DxLib_End();
    return 0;
}
