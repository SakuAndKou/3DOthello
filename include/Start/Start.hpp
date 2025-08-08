#ifndef START_HPP
#define START_HPP
#include "Scene.hpp"
#include "DxLib.h"
class Start:public Scene
{
private:
    int FontHandle; // フォントハンドル
    int FontHandle2; // フォントハンドル
    bool ishover;
public:
    Start(std::weak_ptr<Manager> manager): Scene(manager) 
    {
        FontHandle = CreateFontToHandle( NULL , 180 , 3 );
        FontHandle2 = CreateFontToHandle( NULL , 90 , 3 );
    };
    void Initialize(int num)override;
    void Finalize()override;
    void Update()override;
    void Draw()override;
    void ChangeScene(int num=1)override;
};
#endif