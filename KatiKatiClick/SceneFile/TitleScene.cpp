#include "TitleScene.h"
#include "EndScene.h"
#include "GameMainScene.h"
#include "../UtilityFile/ResourceManager.h"
#include "../UtilityFile/Define.h"
#include "DxLib.h"
#include <math.h>

bool TitleScene::is_fade = false;

TitleScene::TitleScene()
{
	cursor = new Cursor;
	opening_anim = new OpeningAnim;
	fade = new Fade();
	select = -1;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// 音データ読み込み
	int tmp_bgm;
	tmp_bgm = rm->GetSounds("Resource/Sounds/Result/bgm.mp3");
	bgm = tmp_bgm;

	//画像読込
	std::vector<int> tmp_img;
	// タイトルロゴ画像読込
	tmp_img = rm->GetImages("Resource/Images/Opening/TitleLogo.png");
	titlelogo_img.push_back(tmp_img[0]);

	tmp_img = rm->GetImages("Resource/Images/Explanation/select.png");
	select_img.push_back(tmp_img[0]);

	// 雲画像読み込み
	tmp_img = rm->GetImages("Resource/Images/Opening/cloud.png");
	cloud_img.push_back(tmp_img[0]);

	// スタートボタン画像の読み込み
	tmp_img = rm->GetImages("Resource/Images/Opening/PlayButton.png", 3, 3, 1, 130, 70);
	for (int i = 0; i < 3; i++)
	{
		start_button_img.push_back(tmp_img[i]);
	}

	// エンドボタン画像の読み込み
	tmp_img = rm->GetImages("Resource/Images/Opening/EndButton.png", 3, 3, 1, 130, 70);
	for (int i = 0; i < 3; i++)
	{
		end_button_img.push_back(tmp_img[i]);
	}

	is_bgm_active = false;
	
	start_img_num = 0;
	end_img_num = 0;
	change_wait_time = 0;

	// ボタン座標の設定
	start_x = SCREEN_WIDTH / 4.2;
	start_y = GET_LANE_HEIGHT(6.5f);
	end_x = SCREEN_WIDTH / 1.3;
	end_y = GET_LANE_HEIGHT(6.5f);

	//雲の配置
	cloud_pos.x = SCREEN_WIDTH+100;
	cloud_pos.y = GET_LANE_HEIGHT(1);
	cloud_pos2.x = -100;
	cloud_pos2.y = GET_LANE_HEIGHT(8);

	change_screen_flg = false;

	// 音量変更
	bgm_volume = 200;
	ChangeVolumeSoundMem(bgm_volume, bgm);

	anim_start = false;
	black_alpha = 255;
}

TitleScene::~TitleScene()
{
	delete cursor;
	delete fade;
}

void TitleScene::Update()
{

	if (is_bgm_active == false)
	{
		is_bgm_active = true;
		// BGM再生
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);
	}

	// カーソルの更新処理
	cursor->Update();

	if (black_alpha > 0)
	{
		black_alpha -= 5;

		if (black_alpha <= 0)
		{
			black_alpha = 0;
			is_fade = false;
		}
	}

	if (anim_start == true)
	{
		if (opening_anim->GetAnimEnd() == false)
		{
			// オープニング更新処理
			opening_anim->Update();
			return;
		}
	}
	else
	{
		if (black_alpha <= 160)
		{
			anim_start = true;
		}
	}

	//雲の移動
	if (cloud_pos.x < -100) {
		cloud_pos.x = SCREEN_WIDTH+100;
	}
	cloud_pos.x -= 0.4;

	if (cloud_pos2.x > SCREEN_WIDTH+100)
	{
		cloud_pos2.x = -100;
	}
	cloud_pos2.x += 0.4;

	// プレイヤーがボタンをクリックしたか？
	if (select != -1)
	{
		change_wait_time++;
		if (change_wait_time < 40)
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
			fade->Update();

			// BGMを徐々に小さく
			if (bgm_volume != 0)
			{
				bgm_volume -= 7;

				if (bgm_volume <= 0)
				{
					bgm_volume = 0;
				}

				ChangeVolumeSoundMem(bgm_volume, bgm);
			}

			if (fade->CheckFadeEnd() == true)
			{
				change_screen_flg = true;
			}
		}

		return;
	}

	// カーソルとボタンの当たり判定
	if (cursor->GetPState() == P_State::attack && cursor->GetCanHit() == true)
	{
		if (HitBoxCircle(start_x, start_y, cursor->GetLocation(), cursor->GetRadius()) == true)
		{
			// スタートボタンがクリックされた
			select = 0;
		}
		else
		{
			if (HitBoxCircle(end_x, end_y, cursor->GetLocation(), cursor->GetRadius()) == true)
			{
				// エンドボタンがクリックされた
				select = 1;
			}
		}
	}
}

void TitleScene::Draw() const
{
	// 背景色（水色）
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x072246, TRUE);


	double logo_size = 1.0;

	if (opening_anim->GetAnimEnd() == false)
	{
		int disp_num = opening_anim->GetDisplay_num();
		switch (disp_num)
		{
		case 1:
			// タイトルロゴ
			DrawRotaGraph(SCREEN_WIDTH / 2, GET_LANE_HEIGHT(2.8), logo_size, 0, titlelogo_img[0], TRUE);
			
			break;
		case 2:
			// タイトルロゴ
			DrawRotaGraph(SCREEN_WIDTH / 2, GET_LANE_HEIGHT(2.8), logo_size, 0, titlelogo_img[0], TRUE);
			// スタートボタン画像の描画
			DrawRotaGraphF(start_x, start_y, 1.0, 0.0, start_button_img[start_img_num], TRUE);

			break;
		case 3:
			// タイトルロゴ
			DrawRotaGraph(SCREEN_WIDTH / 2, GET_LANE_HEIGHT(2.8),logo_size, 0, titlelogo_img[0], TRUE);
			// スタートボタン画像の描画
			DrawRotaGraphF(start_x, start_y, 1.0, 0.0, start_button_img[start_img_num], TRUE);
			// エンドボタン画像の描画
			DrawRotaGraphF(end_x, end_y, 1.0, 0.0, end_button_img[end_img_num], TRUE);
			//選択の文字
			DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50, 2, 0, select_img[0], TRUE);

			break;
		default:
			break;
		}

		opening_anim->Draw();
	}
	else
	{
		//選択の文字
		DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50, 2, 0, select_img[0], TRUE);

		// 描画ブレンドモードをアルファブレンドにする
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		// 背景の雲
		DrawRotaGraph(cloud_pos.x, cloud_pos.y, 4, 0, cloud_img[0], TRUE);
		DrawRotaGraph(cloud_pos2.x, cloud_pos2.y, 4, 0, cloud_img[0], TRUE);
		// 描画ブレンドモードをノーブレンドにする
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


		// タイトルロゴ
		DrawRotaGraph(SCREEN_WIDTH / 2, GET_LANE_HEIGHT(2.8), logo_size, 0, titlelogo_img[0], TRUE);
		
		// ボタンの描画
		DrawButton();


		cursor->Draw();
	}

	// プレイヤーがボタンをクリックしたか？
	if (select != -1 && change_wait_time > 40)
	{
		fade->Draw();
	}

	if (is_fade == true)
	{
		// 描画ブレンドモードをアルファブレンドにする
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, black_alpha);
		DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x000000, TRUE);
		// 描画ブレンドモードをノーブレンドにする
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

AbstractScene* TitleScene::Change()
{
	if (change_screen_flg)
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
			return new EndScene();
			break;

		default:
			return this;
			break;
		}
	}

	return this;
}

float TitleScene::DistanceSqrf(float box_x, float box_y, float circle_x, float circle_y)
{
	float dx = circle_x - box_x;
	float dy = circle_y - box_y;

	return (dx * dx) + (dy * dy);
}

bool TitleScene::HitBoxCircle(float box_x, float box_y, Vector2D location, float radius)
{
	float box_left, box_right, box_top, box_bottom;
	float circle_x, circle_y;
	float rad;//半径
	bool hit_result = false;//当たったか

	//自分が四角だったら
	box_left = box_x - BUTTON_WIDTH / 2;
	box_top =  box_y - BUTTON_HEIGHT / 2;
	box_right = box_x + BUTTON_WIDTH / 2;
	box_bottom = box_y + BUTTON_HEIGHT / 2;

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

// ボタン押下アニメション処理
void TitleScene::ButtonAnimation()
{
	if (select == 0)
	{
		if (change_wait_time < 8)
		{
			// スタートボタンの画像切り替え
			start_img_num = change_wait_time / 4 + 1;
		}
		else
		{
			start_img_num = 1;
		}
	}
	else
	{
		if (change_wait_time < 8)
		{
			// エンドボタンの画像切り替え
			end_img_num = change_wait_time / 4 + 1;
		}
		else
		{
			end_img_num = 1;
		}
	}
}

// ボタンの描画
void TitleScene::DrawButton() const
{
	if (change_wait_time > 8)
	{
		switch (select)
		{
		case 0:
			// スタートボタンを暗くする
			// 描画輝度のセット
			SetDrawBright(128, 128, 128);
			// スタートボタン画像の描画
			DrawRotaGraphF(start_x, start_y, 1.0, 0.0, start_button_img[start_img_num], TRUE);
			// 描画輝度を元に戻す
			SetDrawBright(255, 255, 255);

			// エンドボタン画像の描画
			DrawRotaGraphF(end_x, end_y, 1.0, 0.0, end_button_img[end_img_num], TRUE);
			break;

		case 1:
			// スタートボタン画像の描画
			DrawRotaGraphF(start_x, start_y, 1.0, 0.0, start_button_img[start_img_num], TRUE);

			// エンドボタンを暗くする
			// 描画輝度のセット
			SetDrawBright(128, 128, 128);
			// エンドボタン画像の描画
			DrawRotaGraphF(end_x, end_y, 1.0, 0.0, end_button_img[end_img_num], TRUE);
			// 描画輝度を元に戻す
			SetDrawBright(255, 255, 255);
			break;

		default:
			break;
		}
	}
	else
	{
		// スタートボタン画像の描画
		DrawRotaGraphF(start_x, start_y, 1.0, 0.0, start_button_img[start_img_num], TRUE);
		// エンドボタン画像の描画
		DrawRotaGraphF(end_x, end_y, 1.0, 0.0, end_button_img[end_img_num], TRUE);
	}
}
