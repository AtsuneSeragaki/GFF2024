#include "GameMainScene.h"

GameMainScene::GameMainScene()
{
    CreateObject<SquishEnemy>();//エネミー生成
    CreateObject<BurstEnemy>();//円エネミー
    CreateObject<Cursor>();//カーソル生成
}

GameMainScene::~GameMainScene()
{
}

void GameMainScene::Update()
{

    //更新処理
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->Update();

        //消してもOKだったらobjectを削除
        if (objects[i]->GetIsDelete() == true)
        {
            objects.erase(objects.begin() + i);
        }
    }

    //当たり判定
    for (int i = 0; i < objects.size() - 1; i++)
    {
        for (int j = i + 1; j <= objects.size() - 1; j++)
        {
            if (objects[i]->GetCanHit() != true || objects[j]->GetCanHit() != true)continue;

            if (objects[i]->HitCheck(objects[j]->GetLocation(), objects[j]->GetRadius()) == true)
            {
                objects[i]->HitReaction(objects[j]);
                objects[j]->HitReaction(objects[i]);
            }
        }
    }

    EnemyGenerate();
}

void GameMainScene::Draw() const
{
    DrawFormatString(10, 10, 0xffffff, "GAMEMAIN");
    //キャラクター描画
    //for (int i = 0; i < objects.size(); i++)
    //{
    //        objects[i]->Draw();   
    //}

    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::enemy)
        {
            objects[i]->Draw();   
        }
    }

    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::cursor)
        {
            objects[i]->Draw();
        }
    }
}

AbstractScene* GameMainScene::Change()
{
    return this;
}

void GameMainScene::EnemyGenerate()
{
    if (objects.size() <= 1)
    {
        CreateObject<SquishEnemy>();//エネミー生成
        CreateObject<BurstEnemy>();//円エネミー
    }


}
