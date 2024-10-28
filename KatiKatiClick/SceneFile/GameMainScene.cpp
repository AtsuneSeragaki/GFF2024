#include "GameMainScene.h"

GameMainScene::GameMainScene()
{
    CreateObject<SquishEnemy>();//エネミー生成
    CreateObject<BurstEnemy>();//円エネミー
    CreateObject<Cursor>();//カーソル生成
    ui_coins = new UICoins;     // コインUI生成
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

                // コインの生成
                coins.push_back(new Coin);
                if (objects[i]->GetObjectType() == ObjectType::enemy)
                {
                    // 生成座標の設定
                    coins.back()->SetLocation(objects[i]->GetLocation());
                    // コインの加算
                    ui_coins->IncreaseCoins();
                }
                
                if (objects[j]->GetObjectType() == ObjectType::enemy)
                {
                    // 生成座標の設定
                    coins.back()->SetLocation(objects[j]->GetLocation());
                    // コインの加算
                    ui_coins->IncreaseCoins();
                }
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

    // コイン描画
    for (int i = 0; i < coins.size(); i++)
    {
        coins[i]->Draw();
    }

    // コインUIの描画
    if (ui_coins != nullptr)
    {
        ui_coins->Draw();
    }
}

AbstractScene* GameMainScene::Change()
{
    return this;
}

void GameMainScene::Initialize()
{
}

void GameMainScene::EnemyGenerate()
{
    if (objects.size() <= 1)
    {
        CreateObject<SquishEnemy>();//エネミー生成
        CreateObject<BurstEnemy>();//円エネミー
    }


}