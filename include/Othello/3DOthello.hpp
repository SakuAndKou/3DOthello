#ifndef _3DOTHELLO_HPP
#define _3DOTHELLO_HPP
#include "Scene.hpp"
#include "DxLib.h"
#include <cmath>
#include "OthelloBoard.hpp"
#include <algorithm>
#include "VECTOR.hpp" 
#include <iostream>
#include <memory>
#include <random>
#include <chrono>
class _3DOthello:public Scene
{
private:
    float XRotate; 
    float YRotate; 
    float ZRotate; 
    VECTOR XVector; 
    VECTOR YVector; 
    VECTOR ZVector; 
    VECTOR cameraPosition; 
    OthelloBoard board; 
    int FontHandle; 

    int mouseX;
    int mouseY;
    bool isMousePressed = false;
    float Rot=0.9f;
    int color = 1; 
    bool result = false; 
    int mycolor = 1; 
    std::chrono::system_clock::time_point last_Time;

    VECTOR Rotate(const VECTOR &vec,const VECTOR &base,float angle)
    {
        return vec*cos(angle)+base*(1-cos(angle))*VDot(base, vec)+VCross(base, vec)*sin(angle);
    }
    void GameLogic(VECTOR WorldPos,int boardSize);
    void ControlCamera();
    bool FinishGame(int boardSize, const std::vector<std::vector<std::vector<int>>>& boardState);
public:
    _3DOthello(std::weak_ptr<Manager> manager): Scene(manager) 
    {
        XVector=VGet(1.0f, 0.0f, 0.0f);
        YVector=VGet(0.0f, 1.0f, 0.0f);
        ZVector=VGet(0.0f, 0.0f, 1.0f);
        XRotate = 0.0f;
        YRotate = 0.0f;
        ZRotate = 0.0f;
        cameraPosition = VGet(0.0f, 60.0f, -60.0f); 
        FontHandle = CreateFontToHandle( NULL , 30 , 3 );
    };
    void Initialize(int num)override;
    void Finalize()override;
    void Update()override;
    void Draw()override;
    void ChangeScene(int num=1)override;
};
#endif