#include "OpeningAnim.h"
#include "../UtilityFile/ResourceManager.h"
#include "../UtilityFile/Define.h"
#include "../UtilityFile/MouseInput.h"
#include "../ObjectFile/EnemyFile/EnemyBase.h"
#include "../ObjectFile/EnemyFile/CrackEnemy.h"
#include "../ObjectFile/EnemyFile/SplitEnemy.h"
#include "../ObjectFile/EnemyFile/FrogEnemy.h"
#include "../ObjectFile/EnemyFile/SnakeEnemy.h"
#include "DxLib.h"


OpeningAnim::OpeningAnim()
{
    op_enm_array =
    {
        {0,1,1,1,0},
        {0,3,1,3,0},
        {0,1,2,1,0},
        {0,4,2,4,0},
    };

    right_smoke_pos.x = ((float)SCREEN_WIDTH / 6) * (float)4 + 40.0f + (float)4 * 10.0f;
    right_smoke_pos.y = -170.0f;

    left_smoke_pos.x = ((float)SCREEN_WIDTH / 6) * (float)0 + 40.0f;
    left_smoke_pos.y = -170.0f;

    for (int i = 0; i < op_enm_array.size(); i++)
    {
        for (int j = 0; j < op_enm_array[i].size(); j++)
        {

            if (op_enm_array[i][j] == 0) { continue; }

            float lane = ((float)SCREEN_WIDTH / 6) * (float)j + 40.0f + (float)j*10.0f;

            if (op_enm_array[i][j] == 1)
            {
                EnemyBase* crack_enemy = CreateObject<CrackEnemy>(Vector2D(lane, -100.0f-(i*70)));//エネミー生成
                crack_enemy->SetStateOpening(true);
            }

            if (op_enm_array[i][j] == 2)
            {
                EnemyBase* split_enemy = CreateObject<SplitEnemy>(Vector2D(lane, -100.0f - (i * 70)));//エネミー生成
                split_enemy->SetStateOpening(true);
            }

            if (op_enm_array[i][j] == 3)
            {
                EnemyBase* frog_enemy = CreateObject<FrogEnemy>(Vector2D(lane, -100.0f - (i * 70)));//エネミー生成
                frog_enemy->SetStateOpening(true);
            }


            if (op_enm_array[i][j] == 4)
            {
               EnemyBase* snake_enemy = CreateObject<SnakeEnemy>(Vector2D(lane, -100.0f - (i * 70)));//エネミー生成
               snake_enemy->SetStateOpening(true);
            }


        }
    }

    // ResourceManagerのインスタンスを取得
    ResourceManager* rm = ResourceManager::GetInstance();

    //画像読込
    std::vector<int> tmp_img;
    tmp_img = rm->GetImages("Resource/Images/Opening/pizza_margherita.png");
    pizza_img.push_back(tmp_img[0]);

    tmp_img = rm->GetImages("Resource/Images/Barrier/smoke.png", 8, 8, 1, 32, 32);
    for (int i = 0; i < 8; i++)
    {
        smoke_img.push_back(tmp_img[i]);
    }

    int tmp_s;
    tmp_s = rm->GetSounds("Resource/Sounds/Title/pizza_fall.mp3");
    pizza_se = tmp_s;
    tmp_s = rm->GetSounds("Resource/Sounds/Title/enm_dash.mp3");
    enm_se = tmp_s;



    ChangeVolumeSoundMem(200,enm_se);


    display_num = 0;
    check_enm_y = 0.0f;

    anim_num = 0;
    pizza_pos.x = SCREEN_WIDTH / 2;
    pizza_pos.y = 0.0f;
    pizza_angle = 0.0;
    anim_end = false;
    se_cnt = 20;
    se_flg = true;
    right_smoke_num = 1;
    left_smoke_num = 0;
}

OpeningAnim::~OpeningAnim()
{

    objects.clear();
    
}

void OpeningAnim::Update()
{

    if (MouseInput::GetMouseState() == eMouseInputState::eClick)
    {
        anim_num = -1;
    }

    if (anim_num == -1)
    {
        anim_end = true;
        return;
    }

    if (se_flg == true)
    {
        if (se_cnt++ > 20)
        {
            se_cnt = 0;
            if (CheckSoundMem(pizza_se) == FALSE) {
                PlaySoundMem(pizza_se, DX_PLAYTYPE_BACK, TRUE);
            }
        }
    }

    switch (anim_num)
    {
    case 0:
        //pizzaが回転しながら落下
        PizzaFall();
        break;
    case 1:
        //エネミーがおいかけてくる
        for (int i = 0; i < objects.size(); i++)
        {
            objects[i]->Update();
        }
        pizza_angle += 0.1;
        pizza_pos.y += 5.0f;
        left_smoke_pos.y += 8;
        right_smoke_pos.y += 8;

        smoke_cnt++;
        if (smoke_cnt > 3)
        {
            smoke_cnt = 0;
            left_smoke_num+=2;
            right_smoke_num+=2;
            if (left_smoke_num > 7)
            {
                left_smoke_num = 0;
                right_smoke_num = 1;
            }
        }


        if (pizza_pos.y > 700)
        {
            se_flg = false;
        }

        check_enm_y = objects[0]->GetLocation().y;
        //画像の中心座標＋画像サイズの半分より下に行ったら画像表示
        //タイトルロゴ表示
        if (check_enm_y > GET_LANE_HEIGHT(3) + 160)
        {
            display_num = 1;
        }

        //タイトルロゴとスタートボタン
        if (check_enm_y > GET_LANE_HEIGHT(6) + 130)
        {
            display_num = 2;
        }

        //タイトルロゴとスタート,エンドボタン
        if (check_enm_y > GET_LANE_HEIGHT(7.5f) + 130)
        {
            display_num = 3;
        }

        //最後のエネミーが800より下にいったら
        if (objects.back()->GetLocation().y > SCREEN_HEIGHT+70)
        {
            anim_num = -1;
        }

        if (CheckSoundMem(enm_se) == FALSE) {
            PlaySoundMem(enm_se, DX_PLAYTYPE_BACK, TRUE);
        }
        break;
    default:
        break;
    }
}

void OpeningAnim::Draw() const
{
    DrawRotaGraphF(pizza_pos.x, pizza_pos.y, 0.3, pizza_angle, pizza_img[0], TRUE);

    for (int i = 0; i < 4; i++)
    {
        //-100.0f - (i * 70))
        DrawRotaGraphF(right_smoke_pos.x-10.0f, right_smoke_pos.y - (i * 70), 2.5, 0, smoke_img[right_smoke_num], TRUE);
    }

    for (int i = 0; i < 4; i++)
    {
        DrawRotaGraphF(left_smoke_pos.x + 10.0f, left_smoke_pos.y - (i * 70), 2.5, 0, smoke_img[left_smoke_num], TRUE);
    }

    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->Draw();
    }



}

void OpeningAnim::PizzaFall()
{
    if (pizza_pos.y > GET_LANE_HEIGHT(5))
    {
        
        anim_num = 1;
    }
    else
    {
        pizza_angle += 0.1;
        pizza_pos.y += 5.0f;
    }
}