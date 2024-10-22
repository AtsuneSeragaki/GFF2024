#include "GameMainScene.h"

GameMainScene::GameMainScene()
{
    //check_virtual = dynamic_cast<ObjectBase*>(new SquishEnemy);
    //if (check_virtual != nullptr)
    //{
    //    objects.push_back(check_virtual);
    //}
    CreateObject<SquishEnemy>();//エネミー生成
    CreateObject<Cursor>();
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

    for (int i = 0; i < objects.size() - 1; i++)
    {
        for (int j = i + 1; j <= objects.size() - 1; j++)
        {
            if (objects[i]->GetCanHit() != true && objects[j]->GetCanHit() != true)continue;

            if (objects[i]->HitCheck(objects[j]->GetLocation(), objects[j]->GetRadius()) == true)
            {
                objects[i]->HitReaction(objects[j]);
                objects[j]->HitReaction(objects[i]);
            }
        }
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
