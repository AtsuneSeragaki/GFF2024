#include "GameMainScene.h"

GameMainScene::GameMainScene()
{
    CreateObject<CrackEnemy>();//エネミー生成
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
            //ヒットチェック
            if (objects[i]->HitCheck(objects[j]->GetLocation(), objects[j]->GetRadius()) == true)
            {
                objects[i]->HitReaction(objects[j]);
                objects[j]->HitReaction(objects[i]);

                CoinGenerate(i, j);

                /*
                //objects[i]がエネミーだったら判定
                EnemyBase* enemy_i = dynamic_cast<EnemyBase*>(objects[i]);
                if (enemy_i != nullptr && enemy_i->GetHitCursor()==true)
                {
                    // コインの生成
                    coins.push_back(new Coin);

                    // 生成座標の設定
                    coins.back()->SetLocation(objects[i]->GetLocation());
                    

                    enemy_i->SetFalseHitCursor();
                }

                //objects[j]がエネミーだったら判定
                EnemyBase* enemy_j = dynamic_cast<EnemyBase*>(objects[j]);
                if (enemy_j != nullptr && enemy_j->GetHitCursor() == true)
                {
                    // コインの生成
                    coins.push_back(new Coin);
                    if (objects[j]->GetObjectType() == ObjectType::enemy)
                    {
                        // 生成座標の設定
                        coins.back()->SetLocation(objects[j]->GetLocation());
                    }

                    enemy_j->SetFalseHitCursor();
                }

                */
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
        CreateObject<CrackEnemy>();//エネミー生成
        CreateObject<BurstEnemy>();//円エネミー
    }


}

void GameMainScene::CoinGenerate(int i, int j)
{
    //objects[i]がエネミーだったら判定
    EnemyBase* enemy_i = dynamic_cast<EnemyBase*>(objects[i]);
    if (enemy_i != nullptr && enemy_i->GetHitCursor() == true)
    {
        // コインの生成
        coins.push_back(new Coin);

        // 生成座標の設定
        coins.back()->SetLocation(objects[i]->GetLocation());


        enemy_i->SetFalseHitCursor();
    }

    //objects[j]がエネミーだったら判定
    EnemyBase* enemy_j = dynamic_cast<EnemyBase*>(objects[j]);
    if (enemy_j != nullptr && enemy_j->GetHitCursor() == true)
    {
        // コインの生成
        coins.push_back(new Coin);
        if (objects[j]->GetObjectType() == ObjectType::enemy)
        {
            // 生成座標の設定
            coins.back()->SetLocation(objects[j]->GetLocation());
        }

        enemy_j->SetFalseHitCursor();
    }

}
