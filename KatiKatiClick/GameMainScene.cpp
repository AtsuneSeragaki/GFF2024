#include "GameMainScene.h"

GameMainScene::GameMainScene()
{

}

GameMainScene::~GameMainScene()
{
}

void GameMainScene::Update()
{
}

void GameMainScene::Draw() const
{
    DrawFormatString(10, 10, 0xffffff, "GAMEMAIN");
}

AbstractScene* GameMainScene::Change()
{
    return this;
}
