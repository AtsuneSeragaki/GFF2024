#include "GameMainScene.h"

#include "../ObjectFile/SkillFile/BAttackSkill.h"
#include "../ObjectFile/SkillFile/BSlowDownSkill.h"
#include "../ObjectFile/SkillFile/AttackSKill.h"
#include "../ObjectFile/SkillFile/SlowDownSkill.h"
#include "../UtilityFile/MouseInput.h"

GameMainScene::GameMainScene()
{
    //CreateObject<CrackEnemy>(Vector2D(200.0f,300.0f));//エネミー生成
    CreateObject<Cursor>(Vector2D(0.0f,0.0f));                  //カーソル生成
    CreateObject<BAttackSkill>(Vector2D(90.0f, 720.0f));        // アタックスキルボタン生成
    CreateObject<BSlowDownSkill>(Vector2D(270.0f, 720.0f));     // 足止めスキルボタン生成
    CreateObject<PauseButton>(Vector2D(320.0f, 35.0f));         // ポーズボタン生成
    goal = CreateObject<Goal>(Vector2D((float)SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - GET_LANE_HEIGHT(2)));//ゴール生成

    ui_coins = new UICoins;     // コインUI生成
    ui_timer = new UITimer;     // タイマー生成
    ui_goal = new UIGoal;       //ゴールUI生成

    enm_generate_cnt = 200;

    is_game_clear = false;
    is_game_over = false;
    change_wait_time = 300;
    is_enm_generate = true;
    is_pause = false;
    is_spos_select = false;
    is_attack_active = false;
}

GameMainScene::~GameMainScene()
{
    delete ui_coins;
    for (ObjectBase* obj : objects)
    {
        delete obj;
    }
    objects.clear();
}

void GameMainScene::Update()
{
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

    // UIコインの更新処理
    ui_coins->Update();
    ui_goal->SetGoalHp(goal->GetGoalCnt());

    // スキル置く場所選択中の処理
    if (is_spos_select == true)
    {
        int i;
        float x,y;

        // 更新処理
        for (i = 0; i < objects.size(); i++)
        {
            if (objects[i]->GetObjectType() == ObjectType::cursor)
            {
                // カーソルのみ更新する
                objects[i]->Update();
                x = objects[i]->GetLocation().x;
                y = objects[i]->GetLocation().y;
            }
        }

        if (MouseInput::GetMouseState() == eMouseInputState::eClick)
        {
            if (is_attack_active == true)
            {
                CreateObject<AttackSkill>(Vector2D(x, y));
                for (i = 0; i < objects.size(); i++)
                {
                    if (objects[i]->GetObjectType() == ObjectType::b_attackskill)
                    {
                        BSkillBase* b_skill = dynamic_cast<BSkillBase*>(objects[i]);
                        b_skill->SetSkillStateClose();
                    }
                }
            }
            else
            {
                CreateObject<SlowDownSkill>(Vector2D(x, y));
                for (i = 0; i < objects.size(); i++)
                {
                    if (objects[i]->GetObjectType() == ObjectType::b_slowdownskill)
                    {
                        BSkillBase* b_skill = dynamic_cast<BSkillBase*>(objects[i]);
                        b_skill->SetSkillStateClose();
                    }
                }
            }

            is_spos_select = false;
        }

        return;            //この行より下の処理はしない
    }

    // 一時停止中の処理
    if (is_pause == true && is_game_over == false)
    {
        
        // 更新処理
        for (int i = 0; i < objects.size(); i++)
        {
            if (objects[i]->GetObjectType() == ObjectType::cursor || objects[i]->GetObjectType() == ObjectType::pausebutton)
            {
                // カーソルとポーズボタンのみ更新する
                objects[i]->Update();
            }
        }

        //当たり判定
        for (int i = 0; i < objects.size() - 1; i++)
        {
            for (int j = i + 1; j < objects.size(); j++)
            {
                // objects[i]がcursor、object[j]がpausebuttonなら当たり判定処理
                if (objects[i]->GetObjectType() == ObjectType::cursor && objects[j]->GetObjectType() == ObjectType::pausebutton)
                {
                    if (objects[i]->GetCanHit() != true || objects[j]->GetCanHit() != true)continue;

                    //もしshapeが違かったら
                    if (objects[i]->GetShape() != objects[j]->GetShape())
                    {
                        //ヒットチェック
                        if (objects[i]->HitBoxCircle(objects[j]) == true)
                        {
                            objects[i]->HitReaction(objects[j]);
                            objects[j]->HitReaction(objects[i]);
                        }
                    }
                }
            }
        }

        // 一時停止中か調べる
        PauseCheck();

        // ゲームの更新を一時停止
        return;
    }
   
    if (ui_timer != nullptr && is_game_over == false)
    {
        if (ui_timer->GetSeconds() == 0)
        {
            // 制限時間が0ならゲームクリア
            is_game_clear = true;

            // シーン切り替え待ちカウントを減らす
            change_wait_time--;

            // カーソルのみ更新
            CursorUpdate();

            return;
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
            // カーソルのみ更新
            CursorUpdate();
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

        //flgがtrueだったらcircleの当たり判定だけのclassを生成する
        if (objects[i]->GetCanCreateZone() == true)
        {
            HitCircleZone* circle_zone = CreateObject<HitCircleZone>(objects[i]->GetLocation());
            circle_zone->SetRadius(objects[i]->GetRadius()+20);
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

            // 一時停止か調べる
            PauseCheck();
        }
    }

    //エネミーを生成
    EnmGenerateTimeCheck();

    //小さいCrackEnemyを生成
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::enemy)
        {
            EnemyBase* enemy = dynamic_cast<EnemyBase*>(objects[i]);

            if (enemy->GetCanCreateMini() == true)
            {
                enemy->StopCreateMini();

                //小さいエネミーを作る
                EnemyBase* crack_enemy_mini = CreateObject<CrackEnemy>(Vector2D(objects[i]->GetLocation().x - 30.0f,objects[i]->GetLocation().y + 40.0f));
                crack_enemy_mini->SetHp(10);
                crack_enemy_mini->SetSize(objects[i]->GetWidth(), objects[i]->GetHeight());
                crack_enemy_mini->SetWaitTime(5);
                EnemyBase* crack_enemy_mini2 = CreateObject<CrackEnemy>(Vector2D(objects[i]->GetLocation().x + 30.0f,objects[i]->GetLocation().y + 40.0f));
                crack_enemy_mini2->SetHp(10);
                crack_enemy_mini2->SetSize(objects[i]->GetWidth(), objects[i]->GetHeight());
                crack_enemy_mini2->SetWaitTime(5);

            }
        }
    } 
}

void GameMainScene::Draw() const
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::attackskill)
        {
            objects[i]->Draw();
        }
    }

    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::slowdownskill)
        {
            objects[i]->Draw();
        }
    }

    //敵の描画
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::enemy || objects[i]->GetObjectType() == ObjectType::circlezone)
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

    if (ui_coins != nullptr)
    {
        // コインUIの描画
        ui_coins->Draw();
    }

    if (ui_goal != nullptr)
    {
        ui_goal->Draw();
    }

    // コイン描画
    for (int i = 0; i < coins.size(); i++)
    {
        coins[i]->Draw();
    }

    //ゴール描画
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::goal)
        {
            objects[i]->Draw();
        }
    }

    if (ui_timer != nullptr)
    {
        // タイマー描画処理
        ui_timer->Draw();
    }

    // ポーズボタン描画
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::pausebutton)
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

    if (is_game_clear)
    {
        DrawString(30, 350, "GAME CLEAR", 0xffffff);
        DrawFormatString(30, 370, 0xffffff, "start : %d sec", change_wait_time / 60 + 1);
    }

    if (is_game_over)
    {
        DrawString(30, 350, "GAME OVER", 0xffffff);
        DrawFormatString(30, 370, 0xffffff, "start : %d sec", change_wait_time / 60 + 1);
    }

    if (is_pause)
    {
       //DrawString(30, 350, "PAUSE", 0xffffff);
    }

    //DrawFormatString(30, 350, 0xffffff, "%d",is_spos_select);
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
            EnemyBase* crack_enemy = CreateObject<CrackEnemy>(Vector2D(((float)LANE_WIDTH * 1.0f) - (float)LANE_WIDTH_HALF, 0.0f));//エネミー生成
            crack_enemy->SetWaitTime(i * 60 * num);
            EnemyBase* crack_enemy2 = CreateObject<CrackEnemy>(Vector2D(((float)LANE_WIDTH * 2.0f) - (float)LANE_WIDTH_HALF, 0.0f));//エネミー生成
            crack_enemy2->SetWaitTime(i * 60 * num);
            EnemyBase* crack_enemy3 = CreateObject<CrackEnemy>(Vector2D(((float)LANE_WIDTH * 3.0f) - (float)LANE_WIDTH_HALF, 0.0f));//エネミー生成
            crack_enemy3->SetWaitTime(i * 60 * num);
        }

        //ランダムで出てくる位置を決める
        int max = 3;
        int min = 1;
        int random_num = min + rand() * (max - min + 1) / (1 + RAND_MAX);

        EnemyBase* burst_enemy = CreateObject<BurstEnemy>(Vector2D(((float)LANE_WIDTH * (float)random_num) - (float)LANE_WIDTH_HALF, 0.0f));//円エネミー
        burst_enemy->SetWaitTime(random_num*60);
        if (random_num == max) { random_num--; }
        else if (random_num == min) { random_num++; }
        else { random_num++; }
        EnemyBase* burst_enemy2 = CreateObject<BurstEnemy>(Vector2D(((float)LANE_WIDTH * (float)random_num) - (float)LANE_WIDTH_HALF, 0.0f));//円エネミー
        burst_enemy2->SetWaitTime(random_num * 60);


        for (int i = 0; i < 3; i++) {
            EnemyBase* snake_enemy = CreateObject<SnakeEnemy>(Vector2D(((float)LANE_WIDTH * 2.0f) - (float)LANE_WIDTH_HALF, -600.0f));//エネミー生成
            //i*60待ってから出てくる
            snake_enemy->SetWaitTime(i * 40);
        }
        CreateObject<FrogEnemy>(Vector2D(((float)LANE_WIDTH * 1.0f) - (float)LANE_WIDTH_HALF, -500.0f));//エネミー生成
        CreateObject<FrogEnemy>(Vector2D(((float)LANE_WIDTH * 3.0f) - (float)LANE_WIDTH_HALF, -500.0f));//エネミー生成
    }
    
}

void GameMainScene::EnmGenerateTimeCheck()
{
    //10秒ごとに敵を生成
//残り時間が少なくなっていくほど敵を多く生成
    switch (ui_timer->GetSeconds())
    {
    case 60:
        EnemyGenerate(1);
        break;
    case 50:
        EnemyGenerate(2);
        break;
    case 40:
        EnemyGenerate(3);
        break;
    case 30:
        EnemyGenerate(4);
        break;
    case 20:
        EnemyGenerate(4);
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
        // コインUIの座標を渡す
        coins.back()->SetUICoinsLocation(ui_coins->GetLocation());
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
        // コインUIの座標を渡す
        coins.back()->SetUICoinsLocation(ui_coins->GetLocation());
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
        // possibleの状態でコインがcoin_num未満だったら、closeの状態にする
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
        is_spos_select = true;

        // ポーズ状態にする
        if (b_skill->GetObjectType() == ObjectType::b_attackskill)
        {
            is_attack_active = true;
        }
    }
}

// カーソルのみの更新処理
void GameMainScene::CursorUpdate()
{
    for (int i = 0; i < objects.size(); i++)
    {
        // objects[i]がカーソルかチェック
        Cursor* cursor = dynamic_cast<Cursor*>(objects[i]);

        if (cursor != nullptr)
        {
            // 更新処理
            objects[i]->Update();
            return;
        }
    }
}

// 一時停止か調べる処理
void GameMainScene::PauseCheck()
{
    for (int i = 0; i < objects.size(); i++)
    {
        // objects[i]がポーズボタンかチェック
        PauseButton* pause_button = dynamic_cast<PauseButton*>(objects[i]);

        if (pause_button != nullptr)
        {
            // ポーズフラグの取得
            is_pause = pause_button->GetPauseFlg();
            return;
        }
    }
}

// 一時停止時のポーズボタンとカーソルの当たり判定
void GameMainScene::PausedHitCheck()
{

}