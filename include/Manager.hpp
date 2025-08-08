#ifndef MANAGER_HPP
#define MANAGER_HPP
#include <vector>
#include "Scene.hpp"
#include <memory>
class Scene; // 前方宣言
class Manager
{
private:
    std::vector<std::unique_ptr<Scene>>Scenes;
    int PreSceneIndex = 0;
    int CurrentSceneIndex = 0;
public:
    Manager();
    void AddScene(std::unique_ptr<Scene> scene);
    void Update();
    void ChangeScene(int sceneIndex);
};
#endif