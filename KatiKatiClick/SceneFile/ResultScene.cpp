#include "ResultScene.h"
#include "TitleScene.h"
#include "GameMainScene.h"
#include "../UtilityFile/ResourceManager.h"
#include "../UtilityFile/Define.h"
#include "DxLib.h"
#include <math.h>


ResultScene::ResultScene(bool is_game_clear, int goal_num)
{
	x1 = 85.0f;
	x2 = 275.0f;
	y1 = 600.0f;
	y2 = 600.0f;

	cursor = new Cursor;

	select = -1;

	on_button = -1;

	is_clear = is_game_clear;

	star_num = goal_num;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();

	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Result/star_silver.png");
	images.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Result/star_gold.png");
	images.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Result/fire.png");
	images.push_back(tmp[0]);

	// 音データ読み込み
	int tmp_bgm;
	tmp_bgm = rm->GetSounds("Resource/Sounds/Title/bgm.mp3");
	bgm = tmp_bgm;

	is_bgm_active = false;

	// 音量変更
	ChangeVolumeSoundMem(190, bgm);
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

	if (cursor->GetPState() == P_State::attack && cursor->GetCanHit()==true)
	{
		if (HitBoxCircle(x1, y1, cursor->GetLocation(), cursor->GetRadius()) == true)
		{
			select = 0;
		}
		else
		{
			if (HitBoxCircle(x2, y2, cursor->GetLocation(), cursor->GetRadius()) == true)
			{
				select = 1;
			}
		}
	}
	else
	{
		if (HitBoxCircle(x1, y1, cursor->GetLocation(), cursor->GetRadius()) == true)
		{
			on_button = 0;
		}
		else
		{
			if (HitBoxCircle(x2, y2, cursor->GetLocation(), cursor->GetRadius()) == true)
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

void ResultScene::Draw() const
{
	DrawString(160, 100, "RESULT", 0xffffff);

	// ゲームクリア、ゲームオーバーの表示
	if (is_clear == true)
	{
		DrawString(140, 160, "GAME CLEAR", 0xffffff);
	}
	else
	{
		DrawString(145, 160, "GAME OVER", 0xffffff);
	}

	// 星の表示
	switch (star_num)
	{
	case 1:
		DrawCircle(50 + 45, 260, 40, 0xffff00, TRUE);
		DrawCircle(140 + 45, 240, 40, 0xffffff, TRUE);
		DrawCircle(230 + 45, 260, 40, 0xffffff, TRUE);
		break;

	case 2:
		DrawCircle(50 + 45, 260, 40, 0xffff00, TRUE);
		DrawCircle(140 + 45, 240, 40, 0xffff00, TRUE);
		DrawCircle(230 + 45, 260, 40, 0xffffff, TRUE);
		break;

	case 3:
		DrawCircle(50 + 45, 260, 40, 0xffff00, TRUE);
		DrawCircle(140 + 45, 240, 40, 0xffff00, TRUE);
		DrawCircle(230 + 45, 260, 40, 0xffff00, TRUE);
		break;

	default:
		DrawCircle(50 + 45, 260, 40, 0xffffff, TRUE);
		DrawCircle(140 + 45, 240, 40, 0xffffff, TRUE);
		DrawCircle(230 + 45, 260, 40, 0xffffff, TRUE);
		break;
	}

	// ボタンの表示
	switch (on_button)
	{
	case 0:
		DrawBoxAA(x1 - (float)BOX_WIDTH / 2, y1 - (float)BOX_HEIGHT / 2, x1 + (float)BOX_WIDTH / 2, y1 + (float)BOX_HEIGHT / 2, 0x999999, TRUE);
		DrawString((x1 - (float)BOX_WIDTH / 2) + 30, (y1 - (float)BOX_HEIGHT / 2) + 20, "RETRY", 0x000000);
		DrawBoxAA(x2 - (float)BOX_WIDTH / 2, y2 - (float)BOX_HEIGHT / 2, x2 + (float)BOX_WIDTH / 2, y2 + (float)BOX_HEIGHT / 2, 0xffffff, TRUE);
		DrawString((x2 - (float)BOX_WIDTH / 2) + 30, (y2 - (float)BOX_HEIGHT / 2) + 20, "TITLE", 0x000000);
		break;

	case 1:
		DrawBoxAA(x1 - (float)BOX_WIDTH / 2, y1 - (float)BOX_HEIGHT / 2, x1 + (float)BOX_WIDTH / 2, y1 + (float)BOX_HEIGHT / 2, 0xffffff, TRUE);
		DrawString((x1 - (float)BOX_WIDTH / 2) + 30, (y1 - (float)BOX_HEIGHT / 2) + 20, "RETRY", 0x000000);
		DrawBoxAA(x2 - (float)BOX_WIDTH / 2, y2 - (float)BOX_HEIGHT / 2, x2 + (float)BOX_WIDTH / 2, y2 + (float)BOX_HEIGHT / 2, 0x999999, TRUE);
		DrawString((x2 - (float)BOX_WIDTH / 2) + 30, (y2 - (float)BOX_HEIGHT / 2) + 20, "TITLE", 0x000000);
		break;

	default:
		DrawBoxAA(x1 - (float)BOX_WIDTH / 2, y1 - (float)BOX_HEIGHT / 2, x1 + (float)BOX_WIDTH / 2, y1 + (float)BOX_HEIGHT / 2, 0xffffff, TRUE);
		DrawString((x1 - (float)BOX_WIDTH / 2) + 30, (y1 - (float)BOX_HEIGHT / 2) + 20, "RETRY", 0x000000);
		DrawBoxAA(x2 - (float)BOX_WIDTH / 2, y2 - (float)BOX_HEIGHT / 2, x2 + (float)BOX_WIDTH / 2, y2 + (float)BOX_HEIGHT / 2, 0xffffff, TRUE);
		DrawString((x2 - (float)BOX_WIDTH / 2) + 30, (y2 - (float)BOX_HEIGHT / 2) + 20, "TITLE", 0x000000);
		break;
	}

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

bool ResultScene::HitBoxCircle(float box_x, float box_y, Vector2D location, float radius)
{
	float box_left, box_right, box_top, box_bottom;
	float circle_x, circle_y;
	float rad;//半径
	bool hit_result = false;//当たったか

	//自分が四角だったら
	box_left = box_x - BOX_WIDTH / 2;
	box_top = box_y - BOX_HEIGHT / 2;
	box_right = box_x + BOX_WIDTH / 2;
	box_bottom = box_y + BOX_HEIGHT / 2;

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
