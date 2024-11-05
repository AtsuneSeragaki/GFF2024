#include "GameMainScene.h"

#include "../ObjectFile/SkillFile/BAttackSkill.h"
#include "../ObjectFile/SkillFile/BSlowDownSkill.h"
#include "../ObjectFile/SkillFile/AttackSKill.h"
#include "../ObjectFile/SkillFile/SlowDownSkill.h"

GameMainScene::GameMainScene()
{
    CreateObject<CrackEnemy>(Vector2D(220.0f, 0.0f));           //エネミー生成
    CreateObject<Cursor>(Vector2D(0.0f,0.0f));                  //カーソル生成
    CreateObject<BAttackSkill>(Vector2D(90.0f, 720.0f));        // アタックスキルボタン生成
    CreateObject<BSlowDownSkill>(Vector2D(270.0f, 720.0f));     // 足止めスキルボタン生成
    CreateObject<PauseButton>(Vector2D(289.0f, 20.0f));         // ポーズボタン生成
    goal = CreateObject<Goal>(Vector2D((float)SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - GET_LANE_HEIGHT(2)));//ゴール生成

    ui_coins = new UICoins;     // コインUI生成
    ui_timer = new UITimer;     // タイマー生成

    enm_generate_cnt = 200;

    is_game_clear = false;
    is_game_over = false;
    change_wait_time = 300;
    is_enm_generate = true;
}

GameMainScene::~GameMainScene()
{

}

void GameMainScene::Update()
{
    if (ui_timer != nullptr && is_game_over == false)
    {
        if (ui_timer->GetSeconds() == 0)
        {
            // 制限時間が0ならゲームクリア
            is_game_clear = true;

            // シーン切り替え待ちカウントを減らす
            change_wait_time--;

            for (int i = 0; i < objects.size(); i++)
            {
                // カーソルのみ更新処理を行う
                Cursor* cursor = dynamic_cast<Cursor*>(objects[i]);

                if (cursor != nullptr)
                {
                    objects[i]->Update();

                    //消してもOKだったらobjectを削除
                    if (objects[i]->GetIsDelete() == true)
                    {
                        objects.erase(objects.begin() + i);
                    }
                    return;
                }
            }
        }

        // タイマー更新処理
        ui_timer->Update();
    }

    //ゲームオーバーかチェック
    if (goal != nullptr)
    {
        if (goal->GetGoalCnt() <= 0)
        {
            // シーン切り替え待ちカウントを減らす
            change_wait_time--;
            is_game_over = true;
            return;            //この行より下の処理はしない
        }
    }

    //更新処理
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::b_attackskill)
        {
            SkillCoinUse(i, 20);
            SkillPause(i);
        }
        else if (objects[i]->GetObjectType() == ObjectType::b_slowdownskill)
        {
            SkillCoinUse(i, 40);
            SkillPause(i);
        }
        else
        {
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
        for (int j = i + 1; j < objects.size(); j++)
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
                if (objects[i]->GetShape() == Shape::circle && objects[j]->GetShape() == Shape::circle)
                {
                    //ヒットチェック
                    if (objects[i]->HitCircle(objects[j]->GetLocation(), objects[j]->GetRadius()) == true)
                    {
                        objects[i]->HitReaction(objects[j]);
                        objects[j]->HitReaction(objects[i]);
                    }
                }

                if (objects[i]->GetShape() == Shape::square && objects[j]->GetShape() == Shape::square)
                {
                    //ヒットチェック
                    if (objects[i]->HitBox(objects[j]->GetLocation(), objects[j]->GetHeight(), objects[j]->GetWidth()))
                    {
                        objects[i]->HitReaction(objects[j]);
                        objects[j]->HitReaction(objects[i]);
                    }
                }
            }

            // コインの生成
            CoinGenerate(i, j);
        }
    }

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

    //エネミーを生成
    EnmGenerateTimeCheck();
}

void GameMainScene::Draw() const
{

    //敵の描画
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::enemy)
        {
            objects[i]->Draw();
        }
    }

    //UI設置仮
    DrawBox(0, 0, SCREEN_WIDTH, ONE_LANE_HEIGHT, 0x999999, TRUE);
    DrawBox(0, SCREEN_HEIGHT - GET_LANE_HEIGHT(2), SCREEN_WIDTH, SCREEN_HEIGHT, 0x999999, TRUE);

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

    // ポーズボタン描画
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::pausebutton)
        {
            objects[i]->Draw();
        }
    }


    // コイン描画
    for (int i = 0; i < coins.size(); i++)
    {
        coins[i]->Draw();
    }



    if (ui_coins != nullptr)
    {
        // コインUIの描画
        ui_coins->Draw();
    }

    //ゴール描画
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::goal)
        {
            objects[i]->Draw();
        }
    }

    //カーソル描画
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::cursor)
        {
            objects[i]->Draw();
        }
    }
    if (ui_timer != nullptr)
    {
        // タイマー描画処理
        ui_timer->Draw();
    }

    if (is_game_clear)
    {
        DrawString(30, 350, "GAME CLEAE", 0xffffff);
        DrawFormatString(30, 370, 0xffffff, "start : %d sec", change_wait_time / 60 + 1);
    }

    if (is_game_over)
    {
        DrawString(30, 350, "GAME OVER", 0xffffff);
        DrawFormatString(30, 370, 0xffffff, "start : %d sec", change_wait_time / 60 + 1);
    }

    
}

AbstractScene* GameMainScene::Change()
{
    if (change_wait_time <= 0)
    {
        return new GameMainScene;
    }

    return this;
}

void GameMainScene::Initialize()
{
}

void GameMainScene::EnemyGenerate(int num)
{
    if (is_enm_generate == true)
    {
        is_enm_generate = false;
        for (int i = 0; i < num; i++)
        {
            //ランダムで出てくる位置を決める
            int max = 3;
            int min = 1;
            int random_num = min+rand() * (max - min + 1) / (1 + RAND_MAX);
            EnemyBase* crack_enemy = CreateObject<CrackEnemy>(Vector2D(((float)LANE_WIDTH * (float)random_num) - (float)LANE_WIDTH_HALF, 0.0f));//エネミー生成
            //i*60待ってから出てくる
            crack_enemy->SetWaitTime(i * 60);

            //crack_enemyと出てくるレーンが被らないようにずらす
            if (random_num == max) { random_num--; }           
            else if (random_num == min) { random_num++; }
            else { random_num++; }
            EnemyBase* burst_enemy = CreateObject<BurstEnemy>(Vector2D(((float)LANE_WIDTH * (float)random_num) - (float)LANE_WIDTH_HALF, 0.0f));//円エネミー
            burst_enemy->SetWaitTime(i * 60);

        }
    }
    /*
    if (enm_generate_cnt > 500)
    {
        enm_generate_cnt = 0;

        for (int i = 1; i < 4; i++)
        {
            CreateObject<CrackEnemy>(Vector2D(((float)LANE_WIDTH * (float)i) - (float)LANE_WIDTH_HALF,0.0f));//エネミー生成
            CreateObject<BurstEnemy>(Vector2D(((float)LANE_WIDTH * (float)i) - (float)LANE_WIDTH_HALF, -100.0f));//円エネミー
        }
    }

    enm_generate_cnt++;
    */
}

void GameMainScene::EnmGenerateTimeCheck()
{
    //10秒ごとに敵を生成
//残り時間が少なくなっていくほど敵を多く生成
    switch (ui_timer->GetSeconds())
    {
    case 60:
        EnemyGenerate(3);
        break;
    case 50:
        EnemyGenerate(6);
        break;
    case 40:
        EnemyGenerate(7);
        break;
    case 30:
        EnemyGenerate(8);
        break;
    case 20:
        EnemyGenerate(10);
        break;
    case 10:
        EnemyGenerate(3);
        break;
    default:
        is_enm_generate = true;
        break;
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

void GameMainScene::SkillCoinUse(int i, int coin_num)
{
    BSkillBase* b_skill = dynamic_cast<BSkillBase*>(objects[i]);

    if (ui_coins->GetCoinsNum() >= coin_num)
    {
        // closeの状態でコインがcoin_num以上だったら、possibleの状態にする
        if (b_skill->GetSkillState() == BSkillState::close)
        {
            b_skill->SetSkillStatePossible();
        }
    }
    else
    {
        // possibleの状態でコインがcoin_num未満、closeの状態にする
        if (b_skill->GetSkillState() == BSkillState::possible)
        {
            b_skill->SetSkillStateClose();
        }
    }

    // スキル解放したらコイン減らす
    if (b_skill->GetUseCoinFlg() == TRUE)
    {
        ui_coins->ReduceCoins(coin_num);
        b_skill->SetUseCoinFlg();
    }
}

void GameMainScene::SkillPause(int i)
{
    BSkillBase* b_skill = dynamic_cast<BSkillBase*>(objects[i]);

    if (b_skill->GetSkillState() == BSkillState::active)
    {
        // ポーズ状態にする
    }
}