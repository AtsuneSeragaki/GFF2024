#include "GameMainScene.h"

GameMainScene::GameMainScene()
{
    squishenemy = new SquishEnemy;
}

GameMainScene::~GameMainScene()
{
}

void GameMainScene::Update()
{
    if (squishenemy != nullptr)
    {
        squishenemy->Update();
    }
}

void GameMainScene::Draw() const
{
    DrawFormatString(10, 10, 0xffffff, "GAMEMAIN");
    if (squishenemy != nullptr)
    {
        squishenemy->Draw();
    }

}

AbstractScene* GameMainScene::Change()
{
    return this;
}
