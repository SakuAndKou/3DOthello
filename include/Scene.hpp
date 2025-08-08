#ifndef SCENE_HPP
#define SCENE_HPP
#include "Manager.hpp"
#include <memory>
class Manager; // 前方宣言
class Scene
{
protected:
    std::weak_ptr<Manager> manager;
public:
    Scene(std::weak_ptr<Manager> _manager): manager(_manager) {};
    virtual void Initialize(int num)=0;
    virtual void Finalize()=0;
    virtual void Update()=0;
    virtual void Draw()=0;
    virtual void ChangeScene(int num)=0;
    int num=0;
};
#endif