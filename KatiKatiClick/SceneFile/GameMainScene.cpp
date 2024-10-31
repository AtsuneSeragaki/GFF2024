#include "GameMainScene.h"

#include "../ObjectFile/SkillFile/BAttackSkill.h"
#include "../ObjectFile/SkillFile/BSlowDownSkill.h"

GameMainScene::GameMainScene()
{
    CreateObject<CrackEnemy>(Vector2D(220.0f, 0.0f));//エネミー生成
    CreateObject<BurstEnemy>(Vector2D(420.0f,0.0f));//円エネミー
    CreateObject<Cursor>(Vector2D(0.0f,0.0f));//カーソル生成
    CreateObject<BAttackSkill>(Vector2D(90.0f, 720.0f)); // アタックスキルボタン生成
    CreateObject<BSlowDownSkill>(Vector2D(270.0f, 720.0f)); // 足止めスキルボタン生成
    ui_coins = new UICoins;     // コインUI生成

    enm_generate_cnt = 200;
}

GameMainScene::~GameMainScene()
{

}

void GameMainScene::Update()
{
    // ゲームメインBGM再生
 
    //更新処理
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::b_attackskill)
        {// オブジェクトタイプがアタックスキルボタンだったら

            SkillCoinUse(i,20);
        }
        else if(objects[i]->GetObjectType() == ObjectType::b_slowdownskill)
        {// オブジェクトタイプが足止めスキルボタンだったら

            SkillCoinUse(i,40);
        }
        else
        {// 上記以外の場合

            objects[i]->Update();
        }
        
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

            //もしshapeが違かったら
            if(objects[i]->GetShape()!=objects[j]->GetShape())
            {
                //ヒットチェック
                if (objects[i]->HitBoxCircle(objects[j]) == true)
                {
                    objects[i]->HitReaction(objects[j]);
                    objects[j]->HitReaction(objects[i]);
                }
            }
            else
            {
                //shapeが同じ時
                //ヒットチェック
                if (objects[i]->HitCircle(objects[j]->GetLocation(), objects[j]->GetRadius()) == true)
                {
                    objects[i]->HitReaction(objects[j]);
                    objects[j]->HitReaction(objects[i]);
                }
            }

            // コインの生成
            CoinGenerate(i, j);
        }
    }

    EnemyGenerate();

    for (int i = 0; i < coins.size(); i++)
    {
        // コイン更新
        coins[i]->Update();

        //消してもOKだったらcoinsを削除
        if (coins[i]->GetCanDeleteFlg() == true)
        {
            coins.erase(coins.begin() + i);
        }
    }

}

void GameMainScene::Draw() const
{

    //キャラクター描画
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::enemy)
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

    //UI設置仮現場
    DrawBox(0, 0, 360, 70, 0x999999, TRUE);
    DrawBox(0, 650, 360, 800, 0x999999, TRUE);

    //ゴール仮幅
    DrawBox(0, 645, 360, 650, 0xffff00, TRUE);

    // アタックスキルボタン描画
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::b_attackskill)
        {
            objects[i]->Draw();
        }
    }

    // 足止めスキルボタン描画
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::b_slowdownskill)
        {
            objects[i]->Draw();
        }
    }

    // カーソル描画
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

void GameMainScene::Initialize()
{
}

void GameMainScene::EnemyGenerate()
{
    if (enm_generate_cnt > 500)
    {
        enm_generate_cnt = 0;
        for (int i = 0; i < 3; i++)
        {
            CreateObject<CrackEnemy>(Vector2D(220.0f + (i * 80), 0.0f));//エネミー生成
            CreateObject<BurstEnemy>(Vector2D(420.0f + (i * 120), 0.0f));//円エネミー
        }
    }

    enm_generate_cnt++;
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
        // コインの加算
        ui_coins->IncreaseCoins();
        //hitflgをオフにする
        enemy_i->SetFalseHitCursor();
    }

    //objects[j]がエネミーだったら判定
    EnemyBase* enemy_j = dynamic_cast<EnemyBase*>(objects[j]);
    if (enemy_j != nullptr && enemy_j->GetHitCursor() == true)
    {
        // コインの生成
        coins.push_back(new Coin);
        // 生成座標の設定
        coins.back()->SetLocation(objects[j]->GetLocation());
        // コインの加算
        ui_coins->IncreaseCoins();
        //hitflgをオフにする
        enemy_j->SetFalseHitCursor();
    }

}

void GameMainScene::SkillCoinUse(int i,int coin_num)
{
    BSkillBase* skill = dynamic_cast<BSkillBase*>(objects[i]);

    if (ui_coins->GetCoinsNum() >= coin_num)
    {
        skill->Update();

        // スキル解放したらコイン減らす
        if (skill->GetUseCoinFlg() == true)
        {
            ui_coins->ReduceCoins(coin_num);
            skill->SetUseCoinFlg();
        }
    }
    else
    {
        // possibleの状態でコインがcoin_numより少なくなったら、closeの状態にする
        if (skill->GetSkillState() == BSkillState::possible)
        {
            skill->SetSkillStateClose();
        }
    }
}
