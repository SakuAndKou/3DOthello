#ifndef SELECT_HPP
#define SELECT_HPP
#include "Scene.hpp"
#include "DxLib.h"
#include <string>
class Select:public Scene
{
private:
    int FontHandle; // フォントハンドル
    bool ishover;
    int FontSize = 80; // フォントサイズ
public:
    Select(std::weak_ptr<Manager> manager): Scene(manager) 
    {
        FontHandle = CreateFontToHandle( NULL , FontSize , 3 );
        ishover=false;
    };
    void Initialize(int num)override;
    void Finalize()override;
    void Update()override;
    void Draw()override;
    void ChangeScene(int num)override;
};
#endif