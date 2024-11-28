#include "ResultScene.h"
#include "TitleScene.h"
#include "GameMainScene.h"
#include "../UtilityFile/ResourceManager.h"
#include "../UtilityFile/Define.h"
#include "../UtilityFile/Define.h"
#include "DxLib.h"
#include <math.h>


ResultScene::ResultScene(bool is_game_clear, int goal_num)
{
	x1 = 85.0f + 20.0f;
	x2 = 275.0f - 20.0f;
	y1 = 570.0f;
	y2 = 570.0f;

	cursor = new Cursor;

	select = -1;

	on_button = -1;

	is_clear = is_game_clear;

	star_num = goal_num;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();

	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/Result/star_silver.png");
	star_images[0] = tmp[0];
	tmp = rm->GetImages("Resource/Images/Result/star_gold.png");
	star_images[1] = tmp[0];
	tmp = rm->GetImages("Resource/Images/Result/fire.png");
	fire_image = tmp[0];
	tmp = rm->GetImages("Resource/Images/Opening/pizza_margherita.png");
	pizza_image = tmp[0];

	// 音データ読み込み
	int tmp_bgm;
	tmp_bgm = rm->GetSounds("Resource/Sounds/Title/bgm.mp3");
	bgm = tmp_bgm;

	is_bgm_active = false;

	// 音量変更
	ChangeVolumeSoundMem(190, bgm);

	pizza_angle = 0.0f;

	for (int i = 0; i < 3; i++)
	{
		star_hp[i] = -1;
		star_x[i] = STAR_X + 85.0f * (float)i;
		star_gold[i] = false;
	}

	star_y[0] = STAR_Y;
	star_y[1] = STAR_Y - 40.0f;
	star_y[2] = STAR_Y;

	star_angle[0] = -PI / 180.0f * 15.0f;
	star_angle[1] = 0.0f;
	star_angle[2] = PI / 180.0f * 15.0f;

	star_extrate[0] = 0.15f;
	star_extrate[1] = 0.2f;
	star_extrate[2] = 0.15f;

	star_gold_extrate[0] = 0.15f;
	star_gold_extrate[1] = 0.2f;
	star_gold_extrate[2] = 0.15f;

	/*star_gold_extrate[0] = 0.55f;
	star_gold_extrate[1] = 0.6f;
	star_gold_extrate[2] = 0.55f;*/

	for (int i = 0; i < goal_num; i++)
	{
		star_gold[i] = true;
		star_hp[i] = 10;
	}
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update()
{
	if (is_bgm_active == false)
	{
		is_bgm_active = true;
		// BGM再生
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);
	}

	cursor->Update();

	HitCheck();

	StarMove();

	ChangePizzaAngle();

}

void ResultScene::Draw() const
{
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x333333,TRUE);
	DrawString(160, 75, "RESULT", 0xffffff);

	// ゲームクリア、ゲームオーバーの表示
	if (is_clear == true)
	{
		DrawString(140, 110, "GAME CLEAR", 0xffffff);
	}
	else
	{
		DrawString(145, 120, "GAME OVER", 0xffffff);
	}

	// 星の表示
	switch (star_num)
	{
	case 1:
		// 銀の星描画
		for (int i = 0; i < 3; i++)
		{
			DrawRotaGraph2F(star_x[i], star_y[i], 250.0f, 250.0f, star_extrate[i], star_angle[i], star_images[0], TRUE);
		}

		// 金の星描画
		for (int i = 0; i < star_num; i++)
		{
			DrawRotaGraph2F(star_x[i], star_y[i], 250.0f, 250.0f, star_gold_extrate[i], star_angle[i], star_images[1], TRUE);
		}
		break;

	case 2:
		// 銀の星描画
		for (int i = 0; i < 3; i++)
		{
			DrawRotaGraph2F(star_x[i], star_y[i], 250.0f, 250.0f, star_extrate[i], star_angle[i], star_images[0], TRUE);
		}

		// 金の星描画
		for (int i = 0; i < star_num; i++)
		{
			DrawRotaGraph2F(star_x[i], star_y[i], 250.0f, 250.0f, star_gold_extrate[i], star_angle[i], star_images[1], TRUE);
		}
		break;

	case 3:

		// 銀の星描画
		for (int i = 0; i < 3; i++)
		{
			DrawRotaGraph2F(star_x[i], star_y[i], 250.0f, 250.0f, star_extrate[i], star_angle[i], star_images[0], TRUE);
		}

		DrawBox(star_x[0] - STAR_WIDTH / 2,star_y[0] - STAR_HEIGHT / 2, star_x[0] + STAR_WIDTH / 2, star_y[0] + STAR_HEIGHT / 2, 0xffffff, TRUE);

		// 金の星描画
		for (int i = 0; i < star_num; i++)
		{
			DrawRotaGraph2F(star_x[i], star_y[i], 250.0f, 250.0f, star_gold_extrate[i], star_angle[i], star_images[1], TRUE);
		}
		break;

	default:
		// 銀の星描画
		for (int i = 0; i < 3; i++)
		{
			DrawRotaGraph2F(star_x[i], star_y[i], 250.0f, 250.0f, star_extrate[i], star_angle[i], star_images[0], TRUE);
		}
		break;
	}

	// ボタンの表示
	switch (on_button)
	{
	case 0:
		DrawBoxAA(x1 - BOX_WIDTH / 2, y1 - BOX_HEIGHT / 2, x1 + BOX_WIDTH / 2, y1 + BOX_HEIGHT / 2, 0x999999, TRUE);
		DrawString((x1 - BOX_WIDTH / 2) + 30, (y1 - BOX_HEIGHT / 2) + 20, "RETRY", 0x000000);
		DrawBoxAA(x2 - BOX_WIDTH / 2, y2 - BOX_HEIGHT / 2, x2 + BOX_WIDTH / 2, y2 + BOX_HEIGHT / 2, 0xffffff, TRUE);
		DrawString((x2 - BOX_WIDTH / 2) + 30, (y2 - BOX_HEIGHT / 2) + 20, "TITLE", 0x000000);
		break;

	case 1:
		DrawBoxAA(x1 - BOX_WIDTH / 2, y1 - BOX_HEIGHT / 2, x1 + BOX_WIDTH / 2, y1 + BOX_HEIGHT / 2, 0xffffff, TRUE);
		DrawString((x1 - BOX_WIDTH / 2) + 30, (y1 - BOX_HEIGHT / 2) + 20, "RETRY", 0x000000);
		DrawBoxAA(x2 - BOX_WIDTH / 2, y2 - BOX_HEIGHT / 2, x2 + BOX_WIDTH / 2, y2 + BOX_HEIGHT / 2, 0x999999, TRUE);
		DrawString((x2 - BOX_WIDTH / 2) + 30, (y2 - BOX_HEIGHT / 2) + 20, "TITLE", 0x000000);
		break;

	default:
		DrawBoxAA(x1 - BOX_WIDTH / 2, y1 - BOX_HEIGHT / 2, x1 + BOX_WIDTH / 2, y1 + BOX_HEIGHT / 2, 0xffffff, TRUE);
		DrawString((x1 - BOX_WIDTH / 2) + 30, (y1 - BOX_HEIGHT / 2) + 20, "RETRY", 0x000000);
		DrawBoxAA(x2 - BOX_WIDTH / 2, y2 - BOX_HEIGHT / 2, x2 + BOX_WIDTH / 2, y2 + BOX_HEIGHT / 2, 0xffffff, TRUE);
		DrawString((x2 - BOX_WIDTH / 2) + 30, (y2 - BOX_HEIGHT / 2) + 20, "TITLE", 0x000000);
		break;
	}

	DrawBox(40, 300, 320, 500, 0xffffff, TRUE);
	DrawRotaGraph2(183, 690, 250, 250, 0.2f, pizza_angle, pizza_image, TRUE);

	cursor->Draw();
}

AbstractScene* ResultScene::Change()
{
	switch (select)
	{
	case 0:
		StopSoundMem(bgm);
		is_bgm_active = false;
		return new GameMainScene();
		break;

	case 1:
		StopSoundMem(bgm);
		is_bgm_active = false;
		return new TitleScene();
		break;

	default:
		break;
	}

	return this;
}

float ResultScene::DistanceSqrf(float box_x, float box_y, float circle_x, float circle_y)
{
	float dx = circle_x - box_x;
	float dy = circle_y - box_y;

	return (dx * dx) + (dy * dy);
}

bool ResultScene::HitBoxCircle(float box_x, float box_y,float width,float height, Vector2D location, float radius)
{
	float box_left, box_right, box_top, box_bottom;
	float circle_x, circle_y;
	float rad;//半径
	bool hit_result = false;//当たったか

	//自分が四角だったら
	box_left = box_x - width / 2;
	box_top = box_y - height / 2;
	box_right = box_x + width / 2;
	box_bottom = box_y + height / 2;

	circle_x = location.x;
	circle_y = location.y;
	rad = radius;

	//circleの端がボックスの上下左右に入っているか
	if ((circle_x > box_left - rad) &&
		(circle_x < box_right + rad) &&
		(circle_y > box_top - rad) &&
		(circle_y < box_bottom + rad))
	{
		hit_result = true;
		float r = rad * rad;//半径＊半径

		//circleのｘが左より小さかったら
		if (circle_x < box_left)
		{
			//左上の座標より上にいたら
			if (circle_y < box_top)
			{
				//左上の頂点との判定
				if ((DistanceSqrf(box_left, box_top, circle_x, circle_y)) >= r)
				{
					//二乗より大きいので当たってない
					hit_result = false;
				}
			}
			else
			{
				//circleのｘが左下の座標より下にいたら
				if (circle_y > box_bottom)
				{
					//左下の頂点との判定
					if (DistanceSqrf(box_left, box_bottom, circle_x, circle_y) >= r)
					{
						hit_result = false;
					}
				}
			}
		}
		else
		{
			//右
			if (circle_x > box_right)
			{
				//右上
				if (circle_y < box_top)
				{
					if ((DistanceSqrf(box_right, box_top, circle_x, circle_y)) >= r)
					{
						hit_result = false;
					}
				}
				else
				{
					//右下
					if (circle_y > box_bottom)
					{
						if (DistanceSqrf(box_right, box_bottom, circle_x, circle_y) >= r)
						{
							hit_result = false;
						}
					}
				}

			}
		}
	}
	return hit_result;
}

void ResultScene::ChangePizzaAngle()
{
	pizza_angle += 0.01f;

	if (pizza_angle >= 180.0f)
	{
		pizza_angle = 0.0f;
	}
}

void ResultScene::HitCheck()
{
	if (cursor->GetPState() == P_State::attack && cursor->GetCanHit() == true)
	{// ボタン or 星の上でクリックされたか？

		// ボタン
		if (HitBoxCircle(x1, y1, BOX_WIDTH, BOX_HEIGHT, cursor->GetLocation(), cursor->GetRadius()) == true)
		{
			select = 0;
		}
		else
		{
			if (HitBoxCircle(x2, y2, BOX_WIDTH, BOX_HEIGHT, cursor->GetLocation(), cursor->GetRadius()) == true)
			{
				select = 1;
			}
		}

		// 星
		if (HitBoxCircle(star_x[0], star_y[0], STAR_WIDTH, STAR_HEIGHT, cursor->GetLocation(), cursor->GetRadius()))
		{
			if (star_gold[0] == true && star_hp[0] != 0)
			{
				star_hp[0]--;
			}
			else
			{
				//鉄の音
			}
		}
		else if (HitBoxCircle(star_x[1], star_y[1], STAR_WIDTH_2, STAR_HEIGHT_2, cursor->GetLocation(), cursor->GetRadius()))
		{
			if (star_gold[1] == true && star_hp[1] != 0)
			{
				star_hp[1]--;
			}
			else
			{
				//鉄の音
			}
		}
		else if (HitBoxCircle(star_x[2], star_y[2], STAR_WIDTH, STAR_HEIGHT, cursor->GetLocation(), cursor->GetRadius()))
		{
			if (star_gold[2] == true && star_hp[2] != 0)
			{
				star_hp[2]--;
			}
			else
			{
				//鉄の音
			}
		}
	}
	else
	{// カーソルがボタンの上にあるか？

		if (HitBoxCircle(x1, y1, BOX_WIDTH, BOX_HEIGHT, cursor->GetLocation(), cursor->GetRadius()) == true)
		{
			on_button = 0;
		}
		else
		{
			if (HitBoxCircle(x2, y2, BOX_WIDTH, BOX_HEIGHT, cursor->GetLocation(), cursor->GetRadius()) == true)
			{
				on_button = 1;
			}
			else
			{
				on_button = -1;
			}
		}
	}
}

void ResultScene::StarMove()
{
	if (star_hp[0] == 0)
	{
		if (star_x[0] <= -40.0f)
		{
			star_x[0] += 5.0f;
			star_y[0] += 5.0f;

			if (star_x[0] >= STAR_X)
			{
				star_hp[0] = 10;
				star_x[0] = STAR_X;
				star_y[0] = STAR_Y;
			}
		}
		else
		{
			star_x[0] -= 5.0f;
			star_y[0] -= 5.0f;
		}
	}

	if (star_hp[1] == 0)
	{
		star_y[1] -= 5.0f;
	}

	if (star_hp[2] == 0)
	{
		star_x[2] += 5.0f;
		star_y[2] -= 5.0f;
	}
}
