#include "OpeningAnim.h"
#include "../UtilityFile/ResourceManager.h"
#include "../UtilityFile/Define.h"
#include "../UtilityFile/MouseInput.h"
#include "../ObjectFile/EnemyFile/EnemyBase.h"
#include "../ObjectFile/EnemyFile/CrackEnemy.h"
#include "DxLib.h"


OpeningAnim::OpeningAnim()
{
    op_enm_array =
    {
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
    };

    for (int i = 0; i < op_enm_array.size(); i++)
    {
        for (int j = 0; j < op_enm_array[i].size(); j++)
        {

            if (op_enm_array[i][j] == 0) { continue; }

            float lane = ((float)SCREEN_WIDTH / 6) * (float)j + 60.0f;

            if (op_enm_array[i][j] == 0)
            {
                EnemyBase* crack_enemy = CreateObject<CrackEnemy>(Vector2D(lane, -100.0f));//エネミー生成
                crack_enemy->SetStateOpening(false);
            }

            /*

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
                    snake_enemy->SetWaitTime((i * 60) + (k * 40));
                }
            }

            */

        }
    }

    // ResourceManagerのインスタンスを取得
    ResourceManager* rm = ResourceManager::GetInstance();

    //画像読込
    std::vector<int> tmp_img;
    tmp_img = rm->GetImages("Resource/Images/Opening/pizza_margherita.png");
    pizza_img.push_back(tmp_img[0]);


    anim_num = 0;
    pizza_pos.x = SCREEN_WIDTH / 2;
    pizza_pos.y = 0.0f;
    pizza_angle = 0;
    anim_end = false;
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

    switch (anim_num)
    {
    case 0:
        //pizzaが回転しながら落下
        PizzaFall();
        break;
    default:
        break;
    }
}

void OpeningAnim::Draw() const
{
    DrawRotaGraph(pizza_pos.x, pizza_pos.y, 0.1, 0, pizza_img[0], TRUE);
}

void OpeningAnim::PizzaFall()
{
    if (pizza_pos.y > GET_LANE_HEIGHT(7))
    {
        anim_num = 1;
    }
    else
    {
        pizza_angle += 1;
        pizza_pos.y += 5.0f;
    }
}