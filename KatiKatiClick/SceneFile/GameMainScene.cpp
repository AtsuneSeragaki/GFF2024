#include "GameMainScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "../ObjectFile/SkillFile/BAttackSkill.h"
#include "../ObjectFile/SkillFile/BSlowDownSkill.h"
#include "../ObjectFile/SkillFile/AttackSKill.h"
#include "../ObjectFile/SkillFile/SlowDownSkill.h"
#include "../UtilityFile/MouseInput.h"
#include "../UtilityFile/ResourceManager.h"
#include "../ObjectFile/EnemyFile/EnemyArray.h"
#include "../ObjectFile/PauseFile/ArrowButtonFile/LeftButton.h"
#include "../ObjectFile/PauseFile/ArrowButtonFile/RightButton.h"
#include "../ObjectFile/PauseFile/TitleButtonFile/TitleButton.h"
#include "../ObjectFile/PauseFile/ChoicesButtonFile/YesButton.h"
#include "../ObjectFile/PauseFile/ChoicesButtonFile/NoButton.h"

GameMainScene::GameMainScene()
{
    //game_state = GameState::in_game;//プレイ中に設定
    game_state = GameState::start;//プレイ中に設定

    //CreateObject<CrackEnemy>(Vector2D(200.0f,300.0f));//エネミー生成
    CreateObject<Cursor>(Vector2D(0.0f,0.0f));                  //カーソル生成
    CreateObject<BAttackSkill>(Vector2D(255.0f, 675.0f));        // アタックスキルボタン生成
    CreateObject<BSlowDownSkill>(Vector2D(75.0f, 675.0f));     // 足止めスキルボタン生成
    wall_cnt = 0;

    for (int i = 0; i < 3; i++)
    {
        wall_cnt++;
        //壁生成
        float y2 = SCREEN_HEIGHT - GET_LANE_HEIGHT(3)-(i* (float)ONE_LANE_HEIGHT / 4.0f)-10.0f;
        //１と３は右へ
        if (i != 1)
        {
            Wall *wall = CreateObject<Wall>(Vector2D(360.0f+193.0f, y2));
            wall->SetWaitTime(i * 10);
        }
        else
        {
           Wall *wall2 = CreateObject<Wall>(Vector2D(-193.0f, y2));
           wall2->SetWaitTime(i * 10);
        }
    }

    CreateObject<PauseButton>(Vector2D(330.0f, 765.0f));         // ポーズボタン生成

    CreateObject<RightButton>(Vector2D(330.0f, 600.0f));         // ポーズ中右向き矢印ボタン生成
    CreateObject<LeftButton>(Vector2D(30.0f, 600.0f));          // ポーズ中左向き矢印ボタン生成
    CreateObject<TitleButton>(Vector2D(180.0f, 650.0f));         // タイトルへ戻るボタン生成
    CreateObject<YesButton>(Vector2D(100.0f, 400.0f));         // "はい"ボタン生成
    CreateObject<NoButton>(Vector2D(260.0f, 400.0f));         // "いいえ"ボタン生成

    //goal = CreateObject<Goal>(Vector2D((float)SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - GET_LANE_HEIGHT(2)));//ゴール生成

    ui_coins = new UICoins;     // コインUI生成
    ui_timer = new UITimer;     // タイマー生成

    enm_generate_cnt = 200;

    is_game_clear = false;
    is_game_over = false;
    change_wait_time = 120;
    is_enm_generate = true;
    is_pause = false;
    is_spos_select = false;
    is_attack_active = false;

    // ResourceManagerのインスタンスを取得
    ResourceManager* rm = ResourceManager::GetInstance();
    std::vector<int> tmp;
    // 背景画像の読み込み
    tmp = rm->GetImages("Resource/Images/Background/Moon3.png");
    background_image.push_back(tmp[0]);
    tmp = rm->GetImages("Resource/Images/Background/Sun2.png");
    background_image.push_back(tmp[0]);
    tmp = rm->GetImages("Resource/Images/Background/Brick3.png");
    background_image.push_back(tmp[0]);

    // 音データ読み込み
    int tmp_s;
    tmp_s = rm->GetSounds("Resource/Sounds/GameMain/BGM/bgm1.mp3");
    bgm = tmp_s;

    tmp_s = rm->GetSounds("Resource/Sounds/GameMain/Time/Time.mp3");
    se = tmp_s;

    tmp_s = rm->GetSounds("Resource/Sounds/GameMain/Enemy/GameOver.mp3");
    gameover_se = tmp_s;

    tmp_s = rm->GetSounds("Resource/Sounds/GameMain/Time/GameClear.mp3");
    gameclear_se = tmp_s;

    ChangeVolumeSoundMem(180, gameover_se);
    ChangeVolumeSoundMem(180,se);
    ChangeVolumeSoundMem(180, gameclear_se);

    //画像読込
    std::vector<int> tmp_img;
    tmp_img = rm->GetImages("Resource/Images/Opening/pizza_margherita.png");
    pizza_img.push_back(tmp_img[0]);

    tmp_img = rm->GetImages("Resource/Images/Explanation/setumei.png");
    bigperpar_img.push_back(tmp_img[0]);
    tmp_img = rm->GetImages("Resource/Images/Explanation/paper.png");
    little_perpar_img.push_back(tmp_img[0]);
    tmp_img = rm->GetImages("Resource/Images/Opening/pizza_box.png");
    pizzabox_img.push_back(tmp_img[0]);


    /*スタートのピザ用*/
    pizza_pos.x = SCREEN_WIDTH / 2;
    pizza_pos.y = 0.0f;
    pizza_angle = 0.0;
    anim_num = 0;
    perpar_alpha = 0;
    
    //makimono_pos.x = 360.0f + 193.0f;
    //makimono_pos.y = 300.0f;
    perpar_pos.x = SCREEN_WIDTH / 2;
    perpar_pos.y = 0.0f;
    start_cnt = 3;
    fps_cnt = 0;
    pizzabox_pos.x = SCREEN_WIDTH / 2;
    pizzabox_pos.y = SCREEN_HEIGHT - GET_LANE_HEIGHT(3.5);

    background_location_y = 0.0f;

    change_pause_page_flg = false;
    click_left_button_flg = false;
    click_title_button_flg = false;
    going_title = false;
    wait_going_title = false;
    //click_no_button_flg = false;
    //no_button_wait_count = 0;

    is_bgm_active = false;

    gameover_alpha = -50;
    gameclear_alpha = -50;

    slowdown_active = false;

    kill_enemy_cnt = 0;
    get_coin_cnt = 0;
}

GameMainScene::~GameMainScene()
{
    delete ui_coins;
    delete ui_timer;
    for (ObjectBase* obj : objects)
    {
        delete obj;
    }
    objects.clear();

    for (DamageEffect* effect : damage_effect)
    {
        delete effect;
    }
    damage_effect.clear();
}

void GameMainScene::Update()
{
    switch (game_state)
    {
    case GameState::start:
        InStartUpdate();
        break;
    case GameState::in_game:
        InGameUpdate();
        break;
    case GameState::gameclear:
        InGameClearUpdate();
        break;
    case GameState::gameover:
        InGameOverUpdate();
        break;
    default:
        break;
    }
}

void GameMainScene::Draw() const
{
    // 1秒間あたりの透明度
    float result = float(60 - ui_timer->GetSeconds()) * 4.25f;

    if (ui_timer->GetSeconds() >= 30)
    {
        int param = 255 - (int)result * 2;

        // 夕方色の背景
        DrawBoxAA(0.0f, 0.0f, 360.0f, 560.0f, 0xe7985d, TRUE);

        // 描画ブレンドモードをアルファブレンドにする
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, param);
        // 朝背景色
        DrawBoxAA(0.0f, 0.0f, 360.0f, 560.0f, GetColor(252, 255, 179), TRUE);
        // 背景の太陽画像の描画
        DrawRotaGraphF(180.0f, 200.0f - background_location_y, 0.5, 0.0, background_image[1], TRUE);
        // 描画ブレンドモードをノーブレンドにする
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    }
    else
    {
        int param = ((int)result - 128) * 2;

        // 夕方色の背景
        DrawBoxAA(0.0f, 0.0f, 360.0f, 560.0f, 0xe7985d, TRUE);

        // 描画ブレンドモードをアルファブレンドにする
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, param);
        // 夜背景色
        DrawBoxAA(0.0f, 0.0f, 360.0f, 560.0f, 0x383a52, TRUE);
        // 描画ブレンドモードをノーブレンドにする
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        
        // 背景の月画像の描画
        DrawRotaGraphF(180.0f, 600.0f - background_location_y, 0.5, 0.0, background_image[0], TRUE);
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

    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::attackskill)
        {
            objects[i]->Draw();
        }
    }


    //pizza表示
    if (game_state == GameState::start)
    {
        DrawRotaGraph((int)pizza_pos.x, (int)pizza_pos.y, 0.3, pizza_angle, pizza_img[0], TRUE);
        //レシート表示
        DrawRotaGraph((int)perpar_pos.x, (int)perpar_pos.y, 1, 0, little_perpar_img[0], TRUE);
        
        DrawRotaGraph((int)pizzabox_pos.x, (int)pizzabox_pos.y, 1, 0, pizzabox_img[0], TRUE);

        // 描画ブレンドモードをアルファブレンドにする
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, perpar_alpha);
        //説明の紙表示
        DrawGraph(0, 0, bigperpar_img[0], TRUE);
        // 描画ブレンドモードをノーブレンドにする
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        

        DrawFormatString(0, 0,0xffffff,"cnt%d",start_cnt);
        
    }


    // UI下のレンガ画像
    DrawRotaGraphF(180.0f, 680.0f, 1.0, 0.0, background_image[2], TRUE);

    //壁描画
    for (int i = 0; i < objects.size(); i++)
    {

        if (objects[i]->GetObjectType() == ObjectType::wall)
        {
            objects[i]->Draw();
        }
    }

    // 一時停止中でないならUIを描画する
    if (is_pause == false)
    {
        // 足止めスキルボタン描画
        for (int i = 0; i < objects.size(); i++)
        {
            if (objects[i]->GetObjectType() == ObjectType::b_slowdownskill)
            {
                objects[i]->Draw();
            }
        }

        // 範囲攻撃スキルボタン描画
        for (int i = 0; i < objects.size(); i++)
        {
            if (objects[i]->GetObjectType() == ObjectType::b_attackskill)
            {
                objects[i]->Draw();
            }
        }

        //ゴール描画
        for (int i = 0; i < objects.size(); i++)
        {
            if (objects[i]->GetObjectType() == ObjectType::wall)
            {
                objects[i]->Draw();
                // DrawFormatString(30 + i * 20, 350, 0xffffff, "%f", );
            }
        }

        if (ui_coins != nullptr)
        {
            // コインUIの描画
            ui_coins->Draw();
        }

        // コイン描画
        for (int i = 0; i < coins.size(); i++)
        {
            coins[i]->Draw();
        }

        //ダメージエフェクトの描画
        for (int i = 0; i < damage_effect.size(); i++)
        {
            damage_effect[i]->Draw();
        }

        if (ui_timer != nullptr)
        {
            // タイマー描画処理
            ui_timer->Draw();
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

    if (is_pause)
    {
        // ポーズ中のボタン描画
        for (int i = 0; i < objects.size(); i++)
        {
            if (objects[i]->GetObjectType() == ObjectType::in_pausebutton)
            {
                objects[i]->Draw();
            }

            // "タイトルへ戻るボタン"がクリックされたら
            if (click_title_button_flg)
            {
                if (objects[i]->GetObjectType() == ObjectType::choicebutton)
                {
                    // 選択肢のボタンの描画
                    objects[i]->Draw();
                }
            }
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

    if (game_state == GameState::gameclear)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, gameclear_alpha);
        DrawBox(0, 0, 360, 800, GetColor(255, 255, 255), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

    if (game_state == GameState::gameover)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, gameover_alpha);
        DrawBox(0, 0, 360, 800, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    
    //DrawFormatString(30, 350, 0xffffff, "%d",kill_enemy_cnt);
    //DrawFormatString(60, 350, 0xffffff, "%d", get_coin_cnt);

}

AbstractScene* GameMainScene::Change()
{
    if (going_title)
    {
        // BGMを止める
        StopSoundMem(bgm);
        is_bgm_active = 0;

        // タイトルに遷移する
        return new TitleScene;
    }

    if (is_game_clear == true/*  && change_wait_time == 0*/)
    {
        // BGMを止める
        StopSoundMem(bgm);
        is_bgm_active = 0;
        //change_wait_time = 120;
        // リザルト画面に遷移する
        return new ResultScene(is_game_clear,wall_cnt,kill_enemy_cnt, get_coin_cnt);
    }

    if (is_game_over == true)
    {
        // BGMを止める
        StopSoundMem(bgm);
        is_bgm_active = 0;

        // リザルト画面に遷移する
        return new ResultScene(is_game_clear, wall_cnt,kill_enemy_cnt,get_coin_cnt);
    }

    return this;
}

void GameMainScene::InGameUpdate()
{
    // BGMを再生
    if (is_bgm_active == 0 && is_game_clear == false)
    {
        is_bgm_active = 1;
        PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);
    }

    // ポーズ中はBGMの音量を小さくする
    if (is_pause)
    {
        ChangeVolumeSoundMem(100, bgm);
    }
    else
    {
        ChangeVolumeSoundMem(140, bgm);
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

    //ダメージエフェクト更新
    for (int i = 0; i < damage_effect.size(); i++)
    {
        damage_effect[i]->Update();

        if (damage_effect[i]->GetDeleteFlg() == true)
        {
           damage_effect.erase(damage_effect.begin() + i);
        }
    }

    // UIコインの更新処理
    ui_coins->Update();

    // スキル置く場所選択中の処理
    if (is_spos_select == true)
    {
        int i, j;
        float x, y;

        for (int k = 0; k < objects.size() - 1; k++)
        {
            for (int m = k + 1; m < objects.size(); m++)
            {
                if (objects[k]->GetObjectType() == ObjectType::cursor && objects[k]->GetCanHit() != true && MouseInput::GetMouseState() == eMouseInputState::eNone)
                {
                    if (objects[m]->GetObjectType() == ObjectType::b_attackskill || objects[m]->GetObjectType() == ObjectType::b_slowdownskill)
                    {
                        //ヒットチェック
                        if (objects[k]->HitBoxCircle(objects[m]) == true)
                        {
                            HitCursorBSkill(m);
                        }
                        else
                        {
                            ResetCursorBSkill(m);
                        }
                    }
                }
                else if (objects[m]->GetObjectType() == ObjectType::cursor && objects[m]->GetCanHit() != true && MouseInput::GetMouseState() == eMouseInputState::eNone)
                {
                    if (objects[k]->GetObjectType() == ObjectType::b_attackskill || objects[k]->GetObjectType() == ObjectType::b_slowdownskill)
                    {
                        //ヒットチェック
                        if (objects[m]->HitBoxCircle(objects[k]) == true)
                        {
                            HitCursorBSkill(k);
                        }
                        else
                        {
                            ResetCursorBSkill(k);
                        }
                    }
                }
            }
        }


        // 更新処理
        for (i = 0; i < objects.size(); i++)
        {
            if (objects[i]->GetObjectType() == ObjectType::cursor)
            {
                objects[i]->Update();
                x = objects[i]->GetLocation().x;
                y = objects[i]->GetLocation().y;
            }
        }

        for (j = 0; j < objects.size(); j++)
        {
            if (objects[j]->GetObjectType() == ObjectType::b_attackskill || objects[j]->GetObjectType() == ObjectType::b_slowdownskill)
            {
                objects[j]->Update();
            }
        }

        if (MouseInput::GetMouseState() == eMouseInputState::eClick)
        {
            if (y <= 470.0f)
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
                    is_attack_active = false;
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
        }

        return;            //この行より下の処理はしない
    }

    // 一時停止中の処理
    if (is_pause == true && is_game_over == false)
    {
        // 更新処理
        for (int i = 0; i < objects.size(); i++)
        {
            if (objects[i]->GetObjectType() == ObjectType::cursor 
                || objects[i]->GetObjectType() == ObjectType::pausebutton
                || objects[i]->GetObjectType() == ObjectType::in_pausebutton
                || objects[i]->GetObjectType() == ObjectType::choicebutton)
            {
                if (change_pause_page_flg)
                {
                    PauseButton* pause_button = dynamic_cast<PauseButton*>(objects[i]);
                    if (pause_button != nullptr)
                    {
                        // ヘルプのページ番号の変更
                        pause_button->SetPage(click_left_button_flg);
                    }
                }

                // カーソルとポーズ中のボタンのみ更新する
                objects[i]->Update();

                //if (click_no_button_flg)
                //{
                //    // "いいえ"ボタンのアニメーション待ち時間
                //    no_button_wait_count++;
                //    if (no_button_wait_count < 5)
                //    {
                //        return;
                //    }
                //    else
                //    {
                //        no_button_wait_count = 0;
                //        click_title_button_flg = false;
                //        click_no_button_flg = false;
                //    }
                //}

                // "はい"ボタンがクリックされたか
                YesButton* yes_button = dynamic_cast<YesButton*>(objects[i]);
                if (yes_button != nullptr)
                {
                    going_title = yes_button->GetGoingTitleFlg();
                    if (wait_going_title)
                    {
                        if (going_title)
                        {
                            return;
                        }
                        return;
                    }
                }
            }
        }

        //当たり判定
        for (int i = 0; i < objects.size() - 1; i++)
        {
            for (int j = i + 1; j < objects.size(); j++)
            {
                // タイトルボタンが押されたら
                if (click_title_button_flg)
                {
                    if (objects[i]->GetObjectType() == ObjectType::cursor && objects[j]->GetObjectType() == ObjectType::choicebutton)
                    {
                        //もしshapeが違かったら
                        if (objects[i]->GetShape() != objects[j]->GetShape())
                        {
                            //ヒットチェック
                            if (objects[i]->HitBoxCircle(objects[j]) == true)
                            {
                                // カーソルが重なっている
                                PauseBase* pause_button = dynamic_cast<PauseBase*>(objects[j]);
                                if (pause_button != nullptr)
                                {
                                    pause_button->SetCursorOverlapFlg();
                                }
                            }
                        }

                        if (objects[i]->GetCanHit() != true || objects[j]->GetCanHit() != true)continue;

                        //ヒットチェック
                        if (objects[i]->HitBoxCircle(objects[j]) == true)
                        {
                            objects[i]->HitReaction(objects[j]);
                            objects[j]->HitReaction(objects[i]);
                        }

                        // "はい"ボタンがクリックされたか
                        YesButton* yes_button = dynamic_cast<YesButton*>(objects[j]);
                        if (yes_button != nullptr)
                        {
                            wait_going_title = yes_button->GetClickFlg();
                            going_title = yes_button->GetGoingTitleFlg();
                        }

                        // "いいえ"ボタンがクリックされたか
                        //NoButton* no_button = dynamic_cast<NoButton*>(objects[j]);
                        //if (no_button != nullptr)
                        //{
                        //    click_no_button_flg = no_button->GetClickFlg();
                        //}

                        if (wait_going_title/* || click_no_button_flg*/)
                        {
                            return;
                        }
                        else
                        {
                            // 他の領域がクリックされたか
                            Cursor* cursor = dynamic_cast<Cursor*>(objects[i]);
                            if (cursor != nullptr)
                            {
                                if (cursor->GetCanHit())
                                {
                                    click_title_button_flg = false;
                                }
                            }
                        }
                    }
                }
                else
                {
                    // objects[i]がcursor、object[j]がpausebuttonなら当たり判定処理
                    if (objects[i]->GetObjectType() == ObjectType::cursor && objects[j]->GetObjectType() == ObjectType::pausebutton
                        || objects[i]->GetObjectType() == ObjectType::cursor && objects[j]->GetObjectType() == ObjectType::in_pausebutton)
                    {
                        //もしshapeが違かったら
                        if (objects[i]->GetShape() != objects[j]->GetShape())
                        {
                            //ヒットチェック
                            if (objects[i]->HitBoxCircle(objects[j]) == true)
                            {
                                // カーソルが重なっている
                                PauseBase* pause_button = dynamic_cast<PauseBase*>(objects[j]);
                                pause_button->SetCursorOverlapFlg();
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
                                    // カーソルが重なっている
                                    PauseBase* pause_button = dynamic_cast<PauseBase*>(objects[j]);
                                    pause_button->SetCursorOverlapFlg();
                                }
                            }
                        }

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
                        }
                    }

                    TitleButton* title_button = dynamic_cast<TitleButton*>(objects[j]);
                    if (title_button != nullptr)
                    {
                        // タイトルボタンがクリックされたか調べる
                        click_title_button_flg = title_button->GetClickFlg();
                        if (click_title_button_flg)
                        {
                            return;
                        }
                    }

                    LeftButton* left_button = dynamic_cast<LeftButton*>(objects[j]);
                    if (left_button != nullptr)
                    {
                        // 左向き矢印がクリックされたか調べる
                        change_pause_page_flg = left_button->GetClickFlg();
                        if (change_pause_page_flg)
                        {
                            click_left_button_flg = true;
                            return;
                        }
                    }

                    RightButton* right_button = dynamic_cast<RightButton*>(objects[j]);
                    if (right_button != nullptr)
                    {
                        // 右向き矢印がクリックされたか調べる
                        change_pause_page_flg = right_button->GetClickFlg();
                        if (change_pause_page_flg)
                        {
                            click_left_button_flg = false;
                            return;
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
            // ゲームクリア状態にする
            game_state = GameState::gameclear;

            //if (change_wait_time == 120)
            //{
            //    // BGMを止める
            //    StopSoundMem(bgm);
            //    is_bgm_active = 0;

            //    PlaySoundMem(se, DX_PLAYTYPE_BACK, TRUE);
            //    PlaySoundMem(gameclear_se, DX_PLAYTYPE_BACK, TRUE);
            //}
            //
            //// 制限時間が0ならゲームクリア
            //is_game_clear = true;

            // シーン切り替え待ちカウントを減らす
            //change_wait_time--;

            // カーソルのみ更新
            //CursorUpdate();

            return;
        }

        // タイマー更新処理
        ui_timer->Update();

        if (ui_timer->GetSeconds() > 30)
        {
            // 背景y座標のずらす値を増やす
            background_location_y += 0.2f;
        }
        else if (ui_timer->GetSeconds() < 30)
        {
            // 背景y座標のずらす値を増やす
            background_location_y += 0.3f;

        }
        else
        {
            background_location_y = 0.0f;
        }
    }

    //ゲームオーバーかチェック
    //壁の数が０になったら
    if (wall_cnt <= 0)
    {
        GameOver_Enm_Generate();
        game_state = GameState::gameover;//stateをゲームオーバーに
        return;            //この行より下の処理はしない
    }

    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::slowdownskill)
        {
            slowdown_active = true;
        }
        else
        {
            slowdown_active = false;
        }
    }

    //更新処理
    for (int i = 0; i < objects.size(); i++)
    {
        // ポーズ中のボタンは処理を飛ばす
        if (objects[i]->GetObjectType() == ObjectType::in_pausebutton) continue;
        if (objects[i]->GetObjectType() == ObjectType::choicebutton) continue;

        if (objects[i]->GetObjectType() == ObjectType::enemy && slowdown_active == false)
        {
            ResetEnemySpeed(i);
        }

        if (objects[i]->GetObjectType() == ObjectType::b_slowdownskill)
        {
            objects[i]->Update();
            SkillCoinUse(i, 20);
            SkillPause(i);
        }
        else if (objects[i]->GetObjectType() == ObjectType::b_attackskill)
        {
            objects[i]->Update();
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
            circle_zone->SetRadius(objects[i]->GetRadius() + 20);
        }


        //消してもOKだったらobjectを削除
        if (objects[i]->GetIsDelete() == true)
        {
            if (objects[i]->GetObjectType() == ObjectType::wall) { wall_cnt -= 1; }
            if (objects[i]->GetObjectType() == ObjectType::enemy) { kill_enemy_cnt++; }
            objects.erase(objects.begin() + i);
        }
    }

    //当たり判定
    for (int i = 0; i < objects.size() - 1; i++)
    {
        // ポーズ中のボタンは処理を飛ばす
        if (objects[i]->GetObjectType() == ObjectType::in_pausebutton) continue;
        if (objects[i]->GetObjectType() == ObjectType::choicebutton) continue;

        for (int j = i + 1; j < objects.size(); j++)
        {
            // ポーズ中のボタンは処理を飛ばす
            if (objects[j]->GetObjectType() == ObjectType::in_pausebutton) continue;
            if (objects[j]->GetObjectType() == ObjectType::choicebutton) continue;

            if (objects[i]->GetObjectType() == ObjectType::cursor && objects[i]->GetCanHit() != true && MouseInput::GetMouseState() == eMouseInputState::eNone)
            {
                if (objects[j]->GetObjectType() == ObjectType::b_attackskill || objects[j]->GetObjectType() == ObjectType::b_slowdownskill)
                {
                    //ヒットチェック
                    if (objects[i]->HitBoxCircle(objects[j]) == true)
                    {
                        HitCursorBSkill(j);
                    }
                    else
                    {
                        ResetCursorBSkill(j);
                    }
                }
            }
            else if (objects[j]->GetObjectType() == ObjectType::cursor && objects[j]->GetCanHit() != true && MouseInput::GetMouseState() == eMouseInputState::eNone)
            {
                if (objects[i]->GetObjectType() == ObjectType::b_attackskill || objects[i]->GetObjectType() == ObjectType::b_slowdownskill)
                {
                    //ヒットチェック
                    if (objects[j]->HitBoxCircle(objects[i]) == true)
                    {
                        HitCursorBSkill(i);
                    }
                    else
                    {
                        ResetCursorBSkill(i);
                    }
                }
            }

            // PauseButtonがカーソルと重なっているか調べる
            if (objects[i]->GetShape() != objects[j]->GetShape())
            {
                //ヒットチェック
                if (objects[i]->HitBoxCircle(objects[j]) == true)
                {
                    // カーソルが重なっている
                    PauseBase* pause_button = dynamic_cast<PauseBase*>(objects[j]);
                    if (pause_button != nullptr)
                    {
                        pause_button->SetCursorOverlapFlg();
                    }
                }
            }

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
                else
                {
                    // 足止めスキルと当たっていない時、HitSlowDownSkillFlgをFalseにする
                    if (objects[i]->GetObjectType() == ObjectType::enemy && objects[j]->GetObjectType() == ObjectType::slowdownskill)
                    {
                        ResetEnemySpeed(i);
                    }
                   /* else if (objects[j]->GetObjectType() == ObjectType::enemy && objects[i]->GetObjectType() == ObjectType::slowdownskill)
                    {
                        ResetEnemySpeed(j);
                    }*/
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
                    else
                    {
                        // 足止めスキルと当たっていない時、HitSlowDownSkillFlgをFalseにする
                        if (objects[i]->GetObjectType() == ObjectType::enemy && objects[j]->GetObjectType() == ObjectType::slowdownskill)
                        {
                            ResetEnemySpeed(i);
                        }
                        /*else if (objects[j]->GetObjectType() == ObjectType::enemy && objects[i]->GetObjectType() == ObjectType::slowdownskill)
                        {
                            ResetEnemySpeed(j);
                        }*/
                    }
                }

                if (objects[i]->GetShape() == Shape::square && objects[j]->GetShape() == Shape::square)
                {
                    //ヒットチェック
                    if (objects[i]->HitBox(objects[j]->GetLocation(), objects[j]->GetHeight(), objects[j]->GetWidth()) == true)
                    {
                        objects[i]->HitReaction(objects[j]);
                        objects[j]->HitReaction(objects[i]);
                    }
                    else
                    {
                        // 足止めスキルと当たっていない時、HitSlowDownSkillFlgをFalseにする
                        if (objects[i]->GetObjectType() == ObjectType::enemy && objects[j]->GetObjectType() == ObjectType::slowdownskill)
                        {
                            ResetEnemySpeed(i);
                        }
                        /*else if (objects[j]->GetObjectType() == ObjectType::enemy && objects[i]->GetObjectType() == ObjectType::slowdownskill)
                        {
                            ResetEnemySpeed(j);
                        }*/
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

    //小さいSpritEnemyを生成
    EnmMiniGenerate();

    //敵のEffectを生成
    EnmEffectGenerate();

    

    /*
    //小さいSplitEnemyを生成
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::enemy)
        {
            EnemyBase* enemy = dynamic_cast<EnemyBase*>(objects[i]);

            if (enemy->GetCanCreateMini() == true)
            {
                enemy->StopCreateMini();

                //小さいエネミーを作る
                EnemyBase* crack_enemy_mini = CreateObject<SplitEnemy>(Vector2D(objects[i]->GetLocation().x - 30.0f, objects[i]->GetLocation().y + 40.0f));
                crack_enemy_mini->SetHp(10);
                crack_enemy_mini->SetSize(objects[i]->GetWidth(), objects[i]->GetHeight());
                crack_enemy_mini->SetWaitTime(5);
                crack_enemy_mini->SetSpeed(2.0f);
                EnemyBase* crack_enemy_mini2 = CreateObject<SplitEnemy>(Vector2D(objects[i]->GetLocation().x + 30.0f, objects[i]->GetLocation().y + 40.0f));
                crack_enemy_mini2->SetHp(10);
                crack_enemy_mini2->SetSize(objects[i]->GetWidth(), objects[i]->GetHeight());
                crack_enemy_mini2->SetWaitTime(5);
                crack_enemy_mini2->SetSpeed(2.0f);

            }
        }
    }
    */
}

void GameMainScene::InStartUpdate()
{
    //pizzaがはんぶんぐらいから回転しながら上から下に
    //下に行ったら右左から壁が飛んでくる
    //巻物で焼きあがるまでpizzaを守ろう！さあ！クリックだ！って言う
    int wallmove_end_cnt = 0;

    switch (anim_num)
    {
    case 0:

        //紙が落ちてきたら
        if (perpar_pos.y > 200)
        {
            if (perpar_alpha > 255)
            {
                //クリックされるまで待つ
                if (MouseInput::GetMouseState() == eMouseInputState::eClick)
                {
                    //クリックされたらスタンプを押す
                    anim_num = 2;
                }
            }
            else
            {
                perpar_alpha += 3;
                //クリックされるまで待つ
                if (MouseInput::GetMouseState() == eMouseInputState::eClick)
                {
                    perpar_alpha = 256;
                }
            }
        }
        else
        {
            perpar_pos.y += 2;
        }

        if (pizza_pos.y > 600)
        {
            pizzabox_pos.y += 5;
        }

        //ピザ落下
        if (pizza_pos.y < 700)
        {
            pizza_pos.y += 5.0f;
            pizza_angle += 0.1;



        }
        else
        {


            //左右から壁
            for (int i = 0; i < objects.size(); i++)
            {
                if (objects[i]->GetObjectType() != ObjectType::wall)continue;

                objects[i]->Update();
                //objects[i]がエネミーだったら判定
                Wall* wall = dynamic_cast<Wall*>(objects[i]);
                if (wall != nullptr)
                {
                    if (wall->GetMoveOnce())
                    {
                        wallmove_end_cnt++;
                    }
                }



            }

        }


        break;
    case 1:
        //0xfbddc1

        //if (makimono_pos.x <= SCREEN_WIDTH / 2)
        //{
        //    makimono_pos.x = (float)SCREEN_WIDTH / 2 - 15.0f;
        //}
        //else {
        //    makimono_pos.x -= 5;
        //}




        break;
    case 2:

        if (perpar_alpha < 0)
        {
            //321カウント
            if (fps_cnt++ > 30)
            {
                fps_cnt = 0;
                start_cnt--;
            }

            if (start_cnt < 0)
            {
                anim_num = 3;
            }
        }
        else
        {
            perpar_alpha -= 5;
            //クリックされるまで待つ
            if (MouseInput::GetMouseState() == eMouseInputState::eClick)
            {
                perpar_alpha = -1;
            }
        }

        break;
    case 3:
        game_state = GameState::in_game;
        break;
    default:
        break;
    }
    
}

void GameMainScene::InGameClearUpdate()
{
    if (gameclear_alpha == -50)
    {
        // BGMを止める
        StopSoundMem(bgm);
        is_bgm_active = 0;

        // クリアseを鳴らす
        PlaySoundMem(se, DX_PLAYTYPE_BACK, TRUE);
        PlaySoundMem(gameclear_se, DX_PLAYTYPE_BACK, TRUE);
    }

    gameclear_alpha += 2;
    if (gameclear_alpha > 300)
    {
        is_game_clear = true;
    }
    CursorUpdate();        // カーソルのみ更新
}

void GameMainScene::InGameOverUpdate()
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() != ObjectType::enemy) { continue; }
        
            //画面内に表示されていたら
            //stateがgoalだったら
            EnemyBase* enemy = dynamic_cast<EnemyBase*>(objects[i]);
            if (enemy != nullptr && enemy->GetState() == State::goal)
            {
                objects[i]->Update();
            }
    }

    // 敵が降りて来る音一回だけ再生
    if (gameover_alpha == -50)
    {
        // BGMを止める
        StopSoundMem(bgm);
        is_bgm_active = 0;

        PlaySoundMem(gameover_se, DX_PLAYTYPE_BACK, TRUE);
    }

    gameover_alpha += 2;
    if (gameover_alpha > 300)
    {
        is_game_over = true;
    }
    CursorUpdate();        // カーソルのみ更新
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

        float generate_lane = (float)SCREEN_WIDTH / 6.0f;
        EnemyBase* burst_enemy = CreateObject<BurstEnemy>(Vector2D(generate_lane * 2.0f, 0.0f));//円エネミー
        burst_enemy->SetWaitTime(60);
        EnemyBase* burst_enemy2 = CreateObject<BurstEnemy>(Vector2D(generate_lane * 4.0f, 0.0f));//円エネミー
        burst_enemy2->SetWaitTime(60);


        for (int i = 0; i < 3; i++) {
            EnemyBase* snake_enemy = CreateObject<SnakeEnemy>(Vector2D(((float)LANE_WIDTH * 2.0f) - (float)LANE_WIDTH_HALF, -600.0f));//エネミー生成
            //i*60待ってから出てくる
            snake_enemy->SetWaitTime(i * 40);
        }
        CreateObject<FrogEnemy>(Vector2D(((float)LANE_WIDTH * 1.0f) - (float)LANE_WIDTH_HALF, -500.0f));//エネミー生成
        CreateObject<FrogEnemy>(Vector2D(((float)LANE_WIDTH * 3.0f) - (float)LANE_WIDTH_HALF, -500.0f));//エネミー生成
    }
    
}

void GameMainScene::GameOver_Enm_Generate()
{
    int wait_time = 20;

   for (int i = 0; i < gameover_enm_array.size(); i++)
    {
        for (int j = 0; j < gameover_enm_array[i].size(); j++)
        {

            if (gameover_enm_array[i][j] == 0) { continue; }

            float lane = ((float)SCREEN_WIDTH / 6) * (float)j + 60.0f;

            if (gameover_enm_array[i][j] == (int)Enemys::CrackEnemy)
            {
                EnemyBase* crack_enemy = CreateObject<CrackEnemy>(Vector2D(lane, -100.0f));//エネミー生成
                crack_enemy->SetWaitTime(i * wait_time);
                crack_enemy->SetStateGameOver();
            }

            if (gameover_enm_array[i][j] == (int)Enemys::BurstEnemy)
            {
                EnemyBase* burst_enemy = CreateObject<BurstEnemy>(Vector2D(lane, -100.0f));//エネミー生成
                burst_enemy->SetWaitTime(i * wait_time);
                burst_enemy->SetStateGameOver();
            }

            if (gameover_enm_array[i][j] == (int)Enemys::SplitEnemy)
            {
                EnemyBase* split_enemy = CreateObject<SplitEnemy>(Vector2D(lane, -100.0f));//エネミー生成
                split_enemy->SetWaitTime(i * wait_time);
                split_enemy->SetStateGameOver();
            }

            if (gameover_enm_array[i][j] == (int)Enemys::FrogEnemy)
            {
                EnemyBase* frog_enemy = CreateObject<FrogEnemy>(Vector2D(lane, -100.0f));//エネミー生成
                frog_enemy->SetWaitTime(i * wait_time);
                frog_enemy->SetStateGameOver();
            }


            if (gameover_enm_array[i][j] == (int)Enemys::SnakeEnemy)
            {
                EnemyBase* snake_enemy = CreateObject<SnakeEnemy>(Vector2D(lane, -100.0f));//エネミー生成
                //i*60待ってから出てくる
                snake_enemy->SetWaitTime((i * wait_time));
                snake_enemy->SetStateGameOver();
            }
        }
    }
        

}

void GameMainScene::EnmGenerateTimeCheck()
{
    //10秒ごとに敵を生成
//残り時間が少なくなっていくほど敵を多く生成
    switch (ui_timer->GetSeconds())
    {
    case 60:
        if (is_enm_generate == true)
        {
            is_enm_generate = false;

            for (int i = 0; i < enemy_array.size(); i++)
            {
                for (int j = 0; j < enemy_array[i].size(); j++)
                {

                    if (enemy_array[i][j] == 0) { continue; }

                    float lane = ((float)SCREEN_WIDTH / 6) * (float)j + 60.0f;

                    if (enemy_array[i][j] == (int)Enemys::CrackEnemy)
                    {
                        EnemyBase* crack_enemy = CreateObject<CrackEnemy>(Vector2D(lane, -100.0f));//エネミー生成
                        crack_enemy->SetWaitTime(i * 60);
                    }

                    if (enemy_array[i][j] == (int)Enemys::BurstEnemy)
                    {
                        EnemyBase* burst_enemy = CreateObject<BurstEnemy>(Vector2D(lane, -100.0f));//エネミー生成
                        burst_enemy->SetWaitTime(i * 60);
                    }

                    if (enemy_array[i][j] == (int)Enemys::SplitEnemy)
                    {
                        EnemyBase* split_enemy = CreateObject<SplitEnemy>(Vector2D(lane, -100.0f));//エネミー生成
                        split_enemy->SetWaitTime(i * 60);
                    }

                    if (enemy_array[i][j] == (int)Enemys::FrogEnemy)
                    {
                        EnemyBase* frog_enemy = CreateObject<FrogEnemy>(Vector2D(lane, -100.0f));//エネミー生成
                        frog_enemy->SetWaitTime(i * 60);
                    }


                    if (enemy_array[i][j] == (int)Enemys::SnakeEnemy)
                    {
                        for (int k = 0; k < 3; k++)
                        {
                            EnemyBase* snake_enemy = CreateObject<SnakeEnemy>(Vector2D(lane, -100.0f));//エネミー生成
                            //i*60待ってから出てくる
                            snake_enemy->SetWaitTime((i * 60)+(k*40));
                        }
                    }
                }
            }
        }

        break;
    //case 50:
    //    EnemyGenerate(2);
    //    break;
    //case 40:
    //    EnemyGenerate(3);
    //    break;
    //case 30:
    //    EnemyGenerate(4);
    //    break;
    //case 20:
    //    EnemyGenerate(4);
    //    break;
    //case 10:
    //    EnemyGenerate(3);
    //    break;
    default:
        is_enm_generate = true;
        break;
    }

}

void GameMainScene::EnmMiniGenerate()
{
    //小さいSplitEnemyを生成
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::enemy)
        {
            EnemyBase* enemy = dynamic_cast<EnemyBase*>(objects[i]);

            if (enemy->GetCanCreateMini() == true)
            {
                enemy->StopCreateMini();

                //小さいエネミーを作る
                EnemyBase* crack_enemy_mini = CreateObject<SplitEnemy>(Vector2D(objects[i]->GetLocation().x - 30.0f, objects[i]->GetLocation().y + 40.0f));
                crack_enemy_mini->SetMini(objects[i]->GetWidth(), objects[i]->GetHeight());
                crack_enemy_mini->SetWaitTime(5);
                EnemyBase* crack_enemy_mini2 = CreateObject<SplitEnemy>(Vector2D(objects[i]->GetLocation().x + 30.0f, objects[i]->GetLocation().y + 40.0f));
                crack_enemy_mini2->SetMini(objects[i]->GetWidth(), objects[i]->GetHeight());
                crack_enemy_mini2->SetWaitTime(5);

            }
        }
    }

}

void GameMainScene::EnmEffectGenerate()
{

    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetObjectType() == ObjectType::enemy)
        {
            EnemyBase* enemy = dynamic_cast<EnemyBase*>(objects[i]);

            if (enemy->GetCreateWallEffect() == true)
            {
                //flgをオフに
                enemy->OffCreateWallEffect();
                Vector2D set_pos = 0;
                set_pos.x = enemy->GetLocation().x;
                set_pos.y = enemy->GetLocation().y+enemy->GetHeight();

                //壁のダメージエフェクトを作成
                damage_effect.push_back(new DamageEffect(set_pos,enemy->GetColor()));
                damage_effect.back()->SetEffectWallDamage();
            }

            if (enemy->GetCreateDamageEffect() == true)
            {
                //flgをオフに
                enemy->OffCreateDamageEffect();
                //敵のダメージエフェクトを作成
                damage_effect.push_back(new DamageEffect(objects[i]->GetLocation(), enemy->GetColor()));
                damage_effect.back()->SetEffectEnemyDamage();
            }
        }
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
        get_coin_cnt++;
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
        get_coin_cnt++;
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

    b_skill->Update();
    b_skill->SetHitCursorFlg(false);

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

void GameMainScene::HitCursorBSkill(int i)
{
    BSkillBase* b_skill = dynamic_cast<BSkillBase*>(objects[i]);

    b_skill->SetHitCursorFlg(true);
}

void GameMainScene::ResetCursorBSkill(int i)
{
    BSkillBase* b_skill = dynamic_cast<BSkillBase*>(objects[i]);

    b_skill->SetHitCursorFlg(false);
}

void GameMainScene::ResetEnemySpeed(int i)
{
    EnemyBase* enemy = dynamic_cast<EnemyBase*>(objects[i]);
    if (enemy->GetHitSlowDownSkillFlg() == true)
    {
        enemy->SetHitSlowDownSkillFlg(false);
        enemy->SetSpeed(enemy->GetEnemyDefaultSpeed());
    }
}
