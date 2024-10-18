#include "GameMainScene.h"

GameMainScene::GameMainScene()
{
    check_virtual = dynamic_cast<ObjectBase*>(new SquishEnemy);
    if (check_virtual != nullptr)
    {
        objects.push_back(check_virtual);
    }
}

GameMainScene::~GameMainScene()
{
}

void GameMainScene::Update()
{
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->Update();
    }

}

void GameMainScene::Draw() const
{
    DrawFormatString(10, 10, 0xffffff, "GAMEMAIN");
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->Draw();
    }
}

AbstractScene* GameMainScene::Change()
{
    return this;
}
