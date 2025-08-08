#include "Manager.hpp"

Manager::Manager()
{
    // 初期化処理
}
void Manager::AddScene(std::unique_ptr<Scene> scene)
{
    // シーンを追加する処理
    Scenes.emplace_back(std::move(scene));
}

void Manager::Update()
{
    if(PreSceneIndex != CurrentSceneIndex)
    {
        Scenes[PreSceneIndex]->Finalize();
        // 現在のシーンを初期化
        Scenes[CurrentSceneIndex]->Initialize(Scenes[PreSceneIndex]->num);
        PreSceneIndex = CurrentSceneIndex;
    }
    Scenes[CurrentSceneIndex]->Update();
    Scenes[CurrentSceneIndex]->Draw();
}
void Manager::ChangeScene(int sceneIndex)
{
    // シーンを変更する処理
    if (sceneIndex < 0 || sceneIndex >= static_cast<int>(Scenes.size()))
    {
        return; // 無効なインデックスの場合は何もしない
    }
    CurrentSceneIndex = sceneIndex;
}