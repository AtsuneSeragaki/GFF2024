#include "ResultScene.h"
#include "TitleScene.h"
#include "GameMainScene.h"
#include "../UtilityFile/ResourceManager.h"
#include "../UtilityFile/Define.h"
#include "DxLib.h"
#include <math.h>


ResultScene::ResultScene(bool is_game_clear, int goal_num)
{
	//x1 = 85.0f + 20.0f;
	//x2 = 275.0f - 20.0f;
	//y1 = 570.0f;
	//y2 = 570.0f;

	cursor = new Cursor;

	select = -1;

	//on_button = -1;

	is_clear = is_game_clear;

	star_num = goal_num;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// 画像データの読み込み
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/Result/star_silver.png");
	star_images[0] = tmp[0];
	tmp = rm->GetImages("Resource/Images/Result/star_gold.png");
	star_images[1] = tmp[0];
	tmp = rm->GetImages("Resource/Images/Result/fire.png");
	fire_image = tmp[0];
	tmp = rm->GetImages("Resource/Images/Opening/pizza_margherita.png");
	pizza_image = tmp[0];
	// リトライボタン画像の読み込み
	tmp = rm->GetImages("Resource/Images/Result/RetryButton.png", 3, 3, 1, 130, 70);
	for (int i = 0; i < 3; i++)
	{
		retry_button_img.push_back(tmp[i]);
	}
	// タイトルボタン画像の読み込み
	tmp = rm->GetImages("Resource/Images/Result/TitleButton.png", 3, 3, 1, 130, 70);
	for (int i = 0; i < 3; i++)
	{
		title_button_img.push_back(tmp[i]);
	}

	// 音データ読み込み
	int tmp_bgm;
	tmp_bgm = rm->GetSounds("Resource/Sounds/Title/bgm.mp3");
	bgm = tmp_bgm;

	tmp_bgm = rm->GetSounds("Resource/Sounds/Result/star_silver.mp3");
	star_click_se[0] = tmp_bgm;

	tmp_bgm = rm->GetSounds("Resource/Sounds/Result/star_gold.mp3");
	star_click_se[1] = tmp_bgm;

	// 音量変更
	ChangeVolumeSoundMem(190, bgm);

	is_bgm_active = false;

	pizza_angle = 0.0f;

	for (int i = 0; i < 3; i++)
	{
		star_hp[i] = -1;
		star_x[i] = STAR_X + 85.0f * (float)i;
		star_gold_x[i] = STAR_X + 85.0f * (float)i;
		star_gold[i] = false;
		star_back[i] = false;
		fire_extrate[i] = 0.0f;
		star_move[i] = 5.0f;
		star_wait_time[i] = 45;
		is_fire_max[i] = false;
		is_star_min[i] = false;
	}

	star_y[0] = STAR_Y;
	star_y[1] = STAR_Y - 40.0f;
	star_y[2] = STAR_Y;

	star_gold_y[0] = STAR_Y;
	star_gold_y[1] = STAR_Y - 40.0f;
	star_gold_y[2] = STAR_Y;

	star_angle[0] = -PI / 180.0f * 15.0f;
	star_angle[1] = 0.0f;
	star_angle[2] = PI / 180.0f * 15.0f;

	star_extrate[0] = 0.15f;
	star_extrate[1] = 0.2f;
	star_extrate[2] = 0.15f;

	// テスト用
	/*star_gold_extrate[0] = 0.15f;
	star_gold_extrate[1] = 0.2f;
	star_gold_extrate[2] = 0.15f;*/

	// 実際に使うやつ
	star_gold_extrate[0] = 0.55f;
	star_gold_extrate[1] = 0.6f;
	star_gold_extrate[2] = 0.55f;

	for (int i = 0; i < goal_num; i++)
	{
		star_gold[i] = true;
		star_hp[i] = 5;
		fire_extrate[i] = 0.05f;
	}

	fire_x[0] = 9.0f;
	fire_y[0] = 30.0f;
	fire_x[1] = 0.0f;
	fire_y[1] = 40.0f;
	fire_x[2] = -9.0f;
	fire_y[2] = 30.0f;

	cnt[0] = 2.7f;
	cnt[1] = 5.2f;
	cnt[2] = 2.7f;

	retry_img_num = 0;
	title_img_num = 0;
	change_wait_time = 0;

	// ボタン座標の設定
	retry_x = GET_LANE_WIDTH(2.5f);
	retry_y = GET_LANE_HEIGHT(7.2f);
	title_x = GET_LANE_WIDTH(7.5f);
	title_y = GET_LANE_HEIGHT(7.2f);

	change_screen_flg = false;

	star_gold_width[0] = 150.0f;
	star_gold_width[1] = 190.0f;
	star_gold_width[2] = 150.0f;

	star_gold_height[0] = 150.0f;
	star_gold_height[1] = 190.0f;
	star_gold_height[2] = 150.0f;
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

	// カーソル更新処理
	cursor->Update();

	ChangePizzaAngle();

	for (int i = 0; i < 3; i++)
	{
		if (is_star_min[i] == false && star_num > i)
		{
			ChangeStarSize(i);
		}
	}
	
	StarMove();

	// プレイヤーがボタンをクリックしたか？
	if (select != -1)
	{
		change_wait_time++;
		if (change_wait_time < 60)
		{
			if (change_wait_time < 10)
			{
				// ボタン押下アニメション
				ButtonAnimation();
			}
		}
		else
		{
			// 画面遷移して良い
			change_screen_flg = true;
		}

		return;
	}

	// ボタンとカーソルの当たり判定
	ButtonHitCheck();

	// 星とカーソルの当たり判定
	StarHitCheck();
}

void ResultScene::Draw() const
{
	// 背景描画
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x333333,TRUE);

	DrawString(160, 75, "RESULT", 0xffffff);

	//DrawFormatString(0, 0, 0xffffff,"%f", star_gold_y[0]);

	// ゲームクリア、ゲームオーバーの描画
	if (is_clear == true)
	{
		DrawString(140, 110, "GAME CLEAR", 0xffffff);
	}
	else
	{
		DrawString(145, 120, "GAME OVER", 0xffffff);
	}

	// 星の数に応じた星の描画
	switch (star_num)
	{
	case 1:
		// 銀の星描画
		for (int i = 0; i < 3; i++)
		{
			DrawRotaGraph2F(star_x[i], star_y[i], 250.0f, 250.0f, star_extrate[i], star_angle[i], star_images[0], TRUE);
		}

		//DrawBox(star_x[0] - STAR_WIDTH / 2,star_y[0] - STAR_HEIGHT / 2, star_x[0] + STAR_WIDTH / 2, star_y[0] + STAR_HEIGHT / 2, 0xffffff, TRUE);

		// 火の描画
		for (int i = 0; i < star_num; i++)
		{
			if (star_hp[i] == 0 && star_back[i] == false)
			{
				DrawRotaGraph2F(star_gold_x[i] + fire_x[i], star_gold_y[i] + fire_y[i], 250.0f, 363.5f, fire_extrate[i], star_angle[i], fire_image, TRUE);
			}
		}

		//if (is_star_min[0] == false)
		//{
		//	// 金の星描画
		//	for (int i = 0; i < star_num; i++)
		//	{
		//		DrawRotaGraph2F(star_gold_width[i], star_gold_height[i], 250.0f, 250.0f, star_gold_extrate[i], star_angle[i], star_images[1], TRUE);
		//	}
		//}
		//else
		//{
		//	// 金の星描画
		//	for (int i = 0; i < star_num; i++)
		//	{
		//		DrawRotaGraph2F(star_gold_x[i], star_gold_y[i], 250.0f, 250.0f, star_gold_extrate[i], star_angle[i], star_images[1], TRUE);
		//	}
		//}

		// 金の星描画
	    DrawRotaGraph2F(star_gold_x[0], star_gold_y[0], 250.0f, 250.0f, star_gold_extrate[0], star_angle[0], star_images[1], TRUE);
		break;

	case 2:
		// 銀の星描画
		for (int i = 0; i < 3; i++)
		{
			DrawRotaGraph2F(star_x[i], star_y[i], 250.0f, 250.0f, star_extrate[i], star_angle[i], star_images[0], TRUE);
		}

		//DrawBox(star_x[0] - STAR_WIDTH / 2,star_y[0] - STAR_HEIGHT / 2, star_x[0] + STAR_WIDTH / 2, star_y[0] + STAR_HEIGHT / 2, 0xffffff, TRUE);

		// 火の描画
		for (int i = 0; i < star_num; i++)
		{
			if (star_hp[i] == 0 && star_back[i] == false)
			{
				DrawRotaGraph2F(star_gold_x[i] + fire_x[i], star_gold_y[i] + fire_y[i], 250.0f, 363.5f, fire_extrate[i], star_angle[i], fire_image, TRUE);
			}
		}

		// 金の星描画
		for (int i = 0; i < star_num; i++)
		{
			if (i >= 1 && is_star_min[i - 1] == true)
			{
				DrawRotaGraph2F(star_gold_x[i], star_gold_y[i], 250.0f, 250.0f, star_gold_extrate[i], star_angle[i], star_images[1], TRUE);
			}
			else
			{
				DrawRotaGraph2F(star_gold_x[0], star_gold_y[0], 250.0f, 250.0f, star_gold_extrate[0], star_angle[0], star_images[1], TRUE);
			}
		}
		break;

	case 3:

		// 銀の星描画
		for (int i = 0; i < 3; i++)
		{
			DrawRotaGraph2F(star_x[i], star_y[i], 250.0f, 250.0f, star_extrate[i], star_angle[i], star_images[0], TRUE);
		}

		//DrawBox(star_x[0] - STAR_WIDTH / 2,star_y[0] - STAR_HEIGHT / 2, star_x[0] + STAR_WIDTH / 2, star_y[0] + STAR_HEIGHT / 2, 0xffffff, TRUE);

		// 火の描画
		for (int i = 0; i < star_num; i++)
		{
			if (star_hp[i] == 0 && star_back[i] == false)
			{
				DrawRotaGraph2F(star_gold_x[i] + fire_x[i], star_gold_y[i] + fire_y[i], 250.0f, 363.5f, fire_extrate[i], star_angle[i], fire_image, TRUE);
			}
		}

		// 金の星描画
		for (int i = 0; i < star_num; i++)
		{
			if (i >= 1 && is_star_min[i - 1] == true)
			{
				DrawRotaGraph2F(star_gold_x[i], star_gold_y[i], 250.0f, 250.0f, star_gold_extrate[i], star_angle[i], star_images[1], TRUE);
			}
			else
			{
				DrawRotaGraph2F(star_gold_x[0], star_gold_y[0], 250.0f, 250.0f, star_gold_extrate[0], star_angle[0], star_images[1], TRUE);
			}
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

	// リザルト結果表示ゾーンの描画
	DrawBox(40, 300, 320, 500, 0xffffff, TRUE);

	// ボタンの描画
	DrawButton();

	// ピザの描画
	DrawRotaGraph2(183, 690, 250, 250, 0.2f, pizza_angle, pizza_image, TRUE);

	// カーソル描画
	cursor->Draw();
}

AbstractScene* ResultScene::Change()
{
	if (change_screen_flg)
	{
		switch (select)
		{
		case 0:
			// BGMを止める
			StopSoundMem(bgm);
			is_bgm_active = false;

			// ゲームメイン画面に遷移
			return new GameMainScene();
			break;

		case 1:
			// BGMを止める
			StopSoundMem(bgm);
			is_bgm_active = false;

			// タイトル画面に遷移
			return new TitleScene();
			break;

		default:
			return this;
			break;
		}
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

// 星とカーソルの当たり判定
void ResultScene::StarHitCheck()
{
	if (cursor->GetPState() == P_State::attack && cursor->GetCanHit() == true)
	{
		// プレイヤーがクリックしたとき、星の上でクリックされたか？
		if (HitBoxCircle(star_x[0], star_y[0], STAR_WIDTH, STAR_HEIGHT, cursor->GetLocation(), cursor->GetRadius()))
		{
			if (star_gold[0] == true && is_star_min[0] == true && star_hp[0] >= 1)
			{
				star_hp[0]--;

				PlaySoundMem(star_click_se[1], DX_PLAYTYPE_BACK, TRUE);
			}
			else if(star_num > 0  && is_star_min[0] == true)
			{
				if (star_hp[0] == 0 && star_gold_y[0] <= STAR_Y - 50.0f)
				{
					//鉄の音
					PlaySoundMem(star_click_se[0], DX_PLAYTYPE_BACK, TRUE);
				}
				else
				{
					PlaySoundMem(star_click_se[1], DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else
			{
				//鉄の音
				PlaySoundMem(star_click_se[0], DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (HitBoxCircle(star_x[1], star_y[1], STAR_WIDTH_2, STAR_HEIGHT_2, cursor->GetLocation(), cursor->GetRadius()))
		{
			if (star_gold[1] == true && is_star_min[1] == true && star_hp[1] >= 1)
			{
				star_hp[1]--;

				PlaySoundMem(star_click_se[1], DX_PLAYTYPE_BACK, TRUE);
			}
			else if (star_num > 1 && is_star_min[1] == true)
			{
				if (star_hp[1] == 0 && star_gold_y[1] <= (STAR_Y - 40.0f) - 50.0f)
				{
					//鉄の音
					PlaySoundMem(star_click_se[0], DX_PLAYTYPE_BACK, TRUE);
				}
				else
				{
					PlaySoundMem(star_click_se[1], DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else
			{
				//鉄の音
				PlaySoundMem(star_click_se[0], DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (HitBoxCircle(star_x[2], star_y[2], STAR_WIDTH, STAR_HEIGHT, cursor->GetLocation(), cursor->GetRadius()))
		{
			if (star_gold[2] == true && is_star_min[2] == true && star_hp[2] >= 1)
			{
				star_hp[2]--;

				PlaySoundMem(star_click_se[1], DX_PLAYTYPE_BACK, TRUE);
			}
			else if(star_num > 2 && is_star_min[2] == true)
			{
				if (star_hp[2] == 0 && star_gold_y[2] <= STAR_Y - 50.0f)
				{
					//鉄の音
					PlaySoundMem(star_click_se[0], DX_PLAYTYPE_BACK, TRUE);
				}
				else
				{
					PlaySoundMem(star_click_se[1], DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else
			{
				//鉄の音
				PlaySoundMem(star_click_se[0], DX_PLAYTYPE_BACK, TRUE);
			}
		}
	}
}

void ResultScene::StarMove()
{
	// 1番目の星の処理
	if (star_hp[0] == 0 && star_wait_time[0] <= 0)
	{
		if (star_back[0] == true)
		{
			star_gold_x[0] = (star_x[0] - 36.0f) + sin(PI * 2.0f / 90.0f * cnt[0]) * 36.0f;
			star_gold_y[0] += (2.0f - star_move[0]);

			if (star_move[0] < 1.8f)
			{
				star_move[0] += 0.001f;
			}

			StarBackAnim(0);

			if (star_gold_y[0] >= STAR_Y)
			{
				star_hp[0] = 5;
				star_gold_x[0] = STAR_X;
				star_gold_y[0] = STAR_Y;
				star_back[0] = false;
				is_fire_max[0] = false;
				fire_extrate[0] = 0.0f;
				star_wait_time[0] = 45;
				cnt[0] = 2.7f;
				star_move[0] = 0.0f;
			}
		}
		else
		{
			star_gold_x[0] -= (5.0f - star_move[0]);
			star_gold_y[0] -= (5.0f - star_move[0]);

			if (star_move[0] > 0.0f)
			{
				star_move[0] -= 0.5f;
			}
		
			if (star_gold_y[0] <= -300.0f)
			{
				star_back[0] = true;
				star_move[0] = 0.0f;
			}
		}
	}
	else if (star_hp[0] == 0 && is_fire_max[0] == false)
	{
		fire_extrate[0] += 0.004f;

		if (fire_extrate[0] >= 0.09f)
		{
			is_fire_max[0] = true;
		}
	}
	else if (is_fire_max[0] == true && star_wait_time[0] > 0)
	{
		star_wait_time[0]--;
	}

	// 2番目の星の処理
	if (star_hp[1] == 0 && star_wait_time[1] <= 0)
	{
		if (star_back[1] == true)
		{
			star_gold_x[1] = star_x[1] + sin(PI * 2.0f / 90.0f * cnt[1]) * 20.0f;
			star_gold_y[1] += (2.0f - star_move[1]);

			if (star_move[1] < 1.8f)
			{
				star_move[1] += 0.001f;
			}

			StarBackAnim(1);

			if (star_gold_y[1] >= (STAR_Y - 40.0f))
			{
				star_hp[1] = 5;
				star_gold_x[1] = STAR_X + 85.0f;
				star_gold_y[1] = STAR_Y - 40.0f;
				star_back[1] = false;
				is_fire_max[1] = false;
				fire_extrate[1] = 0.0f;
				star_wait_time[1] = 45;
				cnt[1] = 5.2f;
				star_move[1] = 0.0f;
			}
		}
		else
		{
			star_gold_y[1] -= (5.0f - star_move[1]);

			if (star_move[1] > 0.0f)
			{
				star_move[1] -= 0.5f;
			}

			if (star_gold_y[1] <= -305.0f)
			{
				star_back[1] = true;
				star_move[1] = 0.0f;
			}
		}
	}
	else if (star_hp[1] == 0 && is_fire_max[1] == false)
	{
		fire_extrate[1] += 0.004f;

		if (fire_extrate[1] >= 0.1f)
		{
			is_fire_max[1] = true;
		}
	}
	else if (is_fire_max[1] == true && star_wait_time[1] > 0)
	{
		star_wait_time[1]--;
	}

	// 3番目の星の処理
	if (star_hp[2] == 0 && star_wait_time[2] <= 0)
	{
		if (star_back[2] == true)
		{
			star_gold_x[2] = (star_x[2] + 36.0f) + sin(PI * 2.0f / 90.0f * cnt[2]) * 36.0f;
			star_gold_y[2] += (2.0f + star_move[2]);

			if (star_move[2] < 1.8f)
			{
				star_move[2] += 0.001f;
			}

			StarBackAnim(2);

			if (star_gold_y[2] >= STAR_Y)
			{
				star_hp[2] = 5;
				star_gold_x[2] = STAR_X + 85.0f * 2.0f;
				star_gold_y[2] = STAR_Y;
				star_back[2] = false;
				is_fire_max[2] = false;
				fire_extrate[2] = 0.0f;
				star_wait_time[2] = 45;
				cnt[2] = 2.7f;
				star_move[2] = 0.0f;
			}
		}
		else
		{
			star_gold_x[2] += (5.0f - star_move[2]);
			star_gold_y[2] -= (5.0f - star_move[2]);

			if (star_move[2] > 0.0f)
			{
				star_move[2] -= 0.5f;
			}

			if (star_gold_y[2] <= -300.0f)
			{
				star_back[2] = true;
				star_move[2] = 0.0f;
			}
		}
	}
	else if (star_hp[2] == 0 && is_fire_max[2] == false)
	{
		fire_extrate[2] += 0.004f;

		if (fire_extrate[2] >= 0.09f)
		{
			is_fire_max[2] = true;
		}
	}
	else if (is_fire_max[2] == true && star_wait_time[2] > 0)
	{
		star_wait_time[2]--;
	}
}

void ResultScene::StarBackAnim(int i)
{
	if (cnt[i] >= 90.0f)
	{
		cnt[i] = 0.0f;
	}
	else
	{
		cnt[i] += 1.0f;
	}
}

// ボタンとカーソルの当たり判定
void ResultScene::ButtonHitCheck()
{
	if (cursor->GetPState() == P_State::attack && cursor->GetCanHit() == true)
	{
		// リトライボタンをクリックしたか調べる
		if (HitBoxCircle(retry_x, retry_y, BUTTON_WIDTH, BUTTON_HEIGHT, cursor->GetLocation(), cursor->GetRadius()) == true)
		{
			select = 0;
		}
		else
		{
			if (HitBoxCircle(title_x, title_y, BUTTON_WIDTH, BUTTON_HEIGHT, cursor->GetLocation(), cursor->GetRadius()) == true)
			{
				// タイトルボタンをクリックしたか調べる
				select = 1;
			}
		}
	}
}

// ボタン押下アニメション処理
void ResultScene::ButtonAnimation()
{
	if (select == 0)
	{
		if (change_wait_time < 8)
		{
			// リトライボタンの画像切り替え
			retry_img_num = change_wait_time / 4 + 1;
		}
		else
		{
			retry_img_num = 1;
		}
	}
	else
	{
		if (change_wait_time < 8)
		{
			// タイトルボタンの画像切り替え
			title_img_num = change_wait_time / 4 + 1;
		}
		else
		{
			title_img_num = 1;
		}
	}

}

// ボタンの描画
void ResultScene::DrawButton() const
{
	if (change_wait_time > 8)
	{
		switch (select)
		{
		case 0:
			// リトライボタンを暗くする
			// 描画輝度のセット
			SetDrawBright(128, 128, 128);
			// リトライボタン画像の描画
			DrawRotaGraphF(retry_x, retry_y, 1.0, 0.0, retry_button_img[retry_img_num], TRUE);
			// 描画輝度を元に戻す
			SetDrawBright(255, 255, 255);

			// タイトルボタン画像の描画
			DrawRotaGraphF(title_x, title_y, 1.0, 0.0, title_button_img[title_img_num], TRUE);
			break;

		case 1:
			// リトライボタン画像の描画
			DrawRotaGraphF(retry_x, retry_y, 1.0, 0.0, retry_button_img[retry_img_num], TRUE);

			// タイトルボタンを暗くする
			// 描画輝度のセット
			SetDrawBright(128, 128, 128);
			// タイトルボタン画像の描画
			DrawRotaGraphF(title_x, title_y, 1.0, 0.0, title_button_img[title_img_num], TRUE);
			// 描画輝度を元に戻す
			SetDrawBright(255, 255, 255);
			break;

		default:
			break;
		}
	}
	else
	{
		// リトライボタン画像の描画
		DrawRotaGraphF(retry_x, retry_y, 1.0, 0.0, retry_button_img[retry_img_num], TRUE);
		// タイトルボタン画像の描画
		DrawRotaGraphF(title_x, title_y, 1.0, 0.0, title_button_img[title_img_num], TRUE);
	}
}

void ResultScene::ChangeStarSize(int i)
{
	switch (i)
	{
	case 0:
		if (star_gold_extrate[i] <= 0.15f)
		{
			is_star_min[i] = true;
			star_gold_extrate[i] = 0.15f;
		}
		else
		{
			star_gold_extrate[i] -= 0.028f;
		}

		break;

	case 1:
		if (star_gold_extrate[i] <= 0.2f)
		{
			is_star_min[i] = true;
			star_gold_extrate[i] = 0.2f;
		}
		else if(is_star_min[i - 1] == true)
		{
			star_gold_extrate[i] -= 0.028f;
		}

		break;
	case 2:
		if (star_gold_extrate[i] <= 0.15f)
		{
			is_star_min[i] = true;
			star_gold_extrate[i] = 0.15f;
		}
		else if (is_star_min[i - 1] == true)
		{
			star_gold_extrate[i] -= 0.028f;
		}
		break;
	default:
		break;
	}
}
