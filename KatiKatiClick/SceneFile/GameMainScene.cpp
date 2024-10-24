#include "GameMainScene.h"

GameMainScene::GameMainScene()
{
    CreateObject<SquishEnemy>();//エネミー生成
    CreateObject<Cursor>();//カーソル生成
    CreateObject<AttackSkill>(); // 範囲攻撃スキル生成
    CreateObject<SlowDownSkill>(); // 足止めスキル生成
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
        if (objects[i]->GetObjectType() == ObjectType::skill)
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
    }
}
