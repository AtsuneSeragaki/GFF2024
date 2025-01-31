#include "ResultScene.h"
#include "TitleScene.h"
#include "GameMainScene.h"
#include "../UtilityFile/ResourceManager.h"
#include "../UtilityFile/Define.h"
#include "DxLib.h"
#include <math.h>


ResultScene::ResultScene(bool is_game_clear, int goal_num,int enemy_num, int coin_num)
{
	//x1 = 85.0f + 20.0f;
	//x2 = 275.0f - 20.0f;
	//y1 = 570.0f;
	//y2 = 570.0f;

	cursor = new Cursor;
	fade = new Fade();

	select = -1;

	//on_button = -1;

	is_clear = is_game_clear;

	star_num = goal_num;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// 画像データの読み込み
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/Result/star_gold.png",4,4,1,100,100);
	for (int i = 0; i < 4; i++)
	{
		star_gold_images.push_back(tmp[i]);
	}
	tmp = rm->GetImages("Resource/Images/Result/star_silver.png");
	star_silver_image = tmp[0];
	tmp = rm->GetImages("Resource/Images/Result/fire.png");
	fire_image = tmp[0];

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

	tmp = rm->GetImages("Resource/Images/Result/StarEffect1.png", 3, 3, 1, 32, 32);
	for (int i = 0; i < 3; i++)
	{
		gstar_click_effect.push_back(tmp[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		gstar_effect_img[i] = gstar_click_effect[0];
	}

	tmp = rm->GetImages("Resource/Images/Result/Result.png");
	result_img = tmp[0];

	tmp = rm->GetImages("Resource/Images/Result/gameclear.png");
	game_clear_img = tmp[0];

	tmp = rm->GetImages("Resource/Images/Result/gameover.png");
	game_over_img = tmp[0];

	tmp = rm->GetImages("Resource/Images/Timer/Num.png",10, 10, 1, 32, 32);
	for (int i = 0; i < 10; i++)
	{
		num_img.push_back(tmp[i]);
	}

	tmp = rm->GetImages("Resource/Images/Result/kirakira_effect.png",4,4,1,32,32);
	for (int i = 0; i < 4; i++)
	{
		kirakira_img.push_back(tmp[i]);
	}
	
	// 音データ読み込み
	int tmp_bgm;
	tmp_bgm = rm->GetSounds("Resource/Sounds/Title/bgm.mp3");
	bgm = tmp_bgm;

	tmp_bgm = rm->GetSounds("Resource/Sounds/Result/star_silver.mp3");
	star_click_se[0] = tmp_bgm;

	tmp_bgm = rm->GetSounds("Resource/Sounds/Result/star_gold.mp3");
	star_click_se[1] = tmp_bgm;

	tmp_bgm = rm->GetSounds("Resource/Sounds/Result/star_back.mp3");
	star_back_se = tmp_bgm;

	tmp_bgm = rm->GetSounds("Resource/Sounds/Result/fire.mp3");
	fire_se = tmp_bgm;

	// 音量変更
	bgm_volume = 190;
	ChangeVolumeSoundMem(bgm_volume, bgm);

	ChangeVolumeSoundMem(200, fire_se);

	is_bgm_active = false;


	for (int i = 0; i < 3; i++)
	{
		star_hp[i] = -1;
		
		star_gold[i] = false;
		star_back[i] = false;
		fire_extrate[i] = 0.0f;
		star_move[i] = 5.0f;
		star_wait_time[i] = 45;
		is_fire_max[i] = false;
		is_star_min[i] = false;
		is_gstar_click[i] = false;
		gstar_effect_num[i] = 0;
		gstar_effect_change_num[i] = 0;
		star_gold_extrate[i] = 0.0f;
		star_click[i] = true;
		star_unclick_cnt[i] = 0;
		kirakira_alpha[i] = 0;
		kirakira_wait_time[i] = 0;
	}

	//for (int i = 0; i < 4; i++)
	//{
	//	kirakira_alpha[i] = 0;
	//	kirakira_alpha_puls[i] = true;
	//	kirakira_anim_num[i] = 0;
	//	kirakira_anim_cnt[i] = 0;
	//}

	star_x[0] = STAR_X;
	star_gold_x[0] = STAR_X;
	star_x[1] = STAR_X + 85.0f;
	star_gold_x[1] = STAR_X + 85.0f;
	star_x[2] = STAR_X + 170.0f;
	star_gold_x[2] = STAR_X + 170.0f;

	kirakira_alpha_puls[0] = false;
	kirakira_alpha_puls[1] = false;
	kirakira_alpha_puls[2] = false;
	kirakira_alpha_puls[3] = true;


	kirakira_anim_num[0] = 0;
	kirakira_anim_num[1] = 1;
	kirakira_anim_num[2] = 2;


	kirakira_anim_cnt[0] = 0;
	kirakira_anim_cnt[1] = 10;
	kirakira_anim_cnt[2] = 0;
	kirakira_anim_cnt[3] = 10;
	kirakira_anim_cnt[4] = 0;
	kirakira_anim_cnt[5] = 10;

	kirakira_anim_num_puls[0] = true;
	kirakira_anim_num_puls[1] = true;
	kirakira_anim_num_puls[2] = false;
	kirakira_anim_num_puls[3] = true;
	kirakira_anim_num_puls[4] = true;
	kirakira_anim_num_puls[5] = false;

	star_y[0] = STAR_Y;
	star_y[1] = STAR_Y - 40.0f;
	star_y[2] = STAR_Y;

	star_gold_y[0] = STAR_Y;
	star_gold_y[1] = STAR_Y - 40.0f;
	star_gold_y[2] = STAR_Y;

	star_angle[0] = -PI / 180.0f * 15.0f;
	star_angle[1] = 0.0f;
	star_angle[2] = PI / 180.0f * 15.0f;

	star_extrate[0] = 0.75f;
	star_extrate[1] = 1.0f;
	star_extrate[2] = 0.75f;

	for (int i = 0; i < goal_num; i++)
	{
		star_gold[i] = true;
		if (i == 1)
		{
			star_hp[i] = 10;
		}
		else
		{
			star_hp[i] = 5;
		}
		fire_extrate[i] = 0.05f;
	}

	fire_x[0] = 9.0f;
	fire_y[0] = 30.0f;
	fire_x[1] = 0.0f;
	fire_y[1] = 40.0f;
	fire_x[2] = -8.0f;
	fire_y[2] = 30.0f;

	cnt[0] = 2.7f;
	cnt[1] = 5.2f;
	cnt[2] = 2.7f;

	retry_img_num = 0;
	title_img_num = 0;
	change_wait_time = 0;

	// ボタン座標の設定
	retry_x = GET_LANE_WIDTH(2.5f);
	retry_y = GET_LANE_HEIGHT(7.2f) + 50.0f;
	title_x = GET_LANE_WIDTH(7.5f);
	title_y = GET_LANE_HEIGHT(7.2f) + 50.0f;

	change_screen_flg = false;

	star_gold_width[0] = 150.0f;
	star_gold_width[1] = 190.0f;
	star_gold_width[2] = 150.0f;

	star_gold_height[0] = 150.0f;
	star_gold_height[1] = 190.0f;
	star_gold_height[2] = 150.0f;

	gstar_effect_extrate[0] = 2.0f;
	gstar_effect_extrate[1] = 3.0f;
	gstar_effect_extrate[2] = 2.0f;

	get_coin_num = coin_num;
	kill_enemy_num = enemy_num;

	get_coin_num_2 = 0;
	kill_enemy_num_2 = 0;
	score = (kill_enemy_num + get_coin_num) * 10;
	//score = 12355;
	score_2 = 0;

	black_alpha = 255;

	anim_start = false;

	kirakira_extrate = 1.0f;

	star_start_end = false;

	star_img_num[0] = 0;
	star_img_num[1] = 0;
	star_img_num[2] = 0;

	overlap_retry_button_flg = false;
	overlap_title_button_flg = false;
}

ResultScene::~ResultScene()
{
	delete cursor;
	delete fade;
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

	// プレイヤーがボタンをクリックしたか？
	if (star_start_end == true && select != -1)
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
				bgm_volume -= 6;

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
	else
	{
		overlap_retry_button_flg = false;
		overlap_title_button_flg = false;
	}

	if (black_alpha > 0)
	{
		black_alpha -= 5;

		if (black_alpha <= 0)
		{
			black_alpha = 0;
		}
	}

	if (anim_start == true)
	{
		for (int i = 0; i < 3; i++)
		{
			if (is_star_min[i] == false && star_num > i)
			{
				ChangeStarSize(i);
			}
		}

		if (star_num == 0)
		{
			if (star_start_end == false)
			{
				star_start_end = true;
			}
		}
		else
		{
			if (is_star_min[star_num - 1] == true && star_start_end == false)
			{
				star_start_end = true;
			}
		}
		
		StarMove();

		// ボタンとカーソルの当たり判定
		ButtonHitCheck();

		// 星とカーソルの当たり判定
		StarHitCheck();

		GStarClickEffect();

		AddNum();

		StarUnClickCount();

		ChangeKirakiraAlpha();

		KirakiraAnimControl();
	}
	else
	{
		if (black_alpha <= 10)
		{
			anim_start = true;
			star_gold_extrate[0] = 2.55f;
			star_gold_extrate[1] = 2.5f;
			star_gold_extrate[2] = 2.55f;
		}
	}
}

void ResultScene::Draw() const
{
	// 背景描画
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x072246,TRUE);

	// ゲームクリア、ゲームオーバーの描画
	if (is_clear == true)
	{
		DrawGraph(60, 65, game_clear_img, TRUE);
		
	}
	else
	{
		DrawGraph(60, 65, game_over_img, TRUE);
	}

	// 星の数に応じた星の描画
	switch (star_num)
	{
	case 1:
		// 銀の星描画
		for (int i = 0; i < 3; i++)
		{
			DrawRotaGraph2F(star_x[i], star_y[i], 50.0f, 50.0f, star_extrate[i], star_angle[i], star_silver_image, TRUE);
		}

		// 火の描画
		for (int i = 0; i < star_num; i++)
		{
			if (star_hp[i] == 0 && star_back[i] == false)
			{
				DrawRotaGraph2F(star_gold_x[i] + fire_x[i], star_gold_y[i] + fire_y[i], 250.0f, 363.5f, fire_extrate[i], star_angle[i], fire_image, TRUE);
			}

			//DrawRotaGraph2F(star_gold_x[i] + fire_x[i], star_gold_y[i] + fire_y[i], 250.0f, 363.5f, fire_extrate[i], star_angle[i], fire_image, TRUE);
		}

		// 金の星描画
	    DrawRotaGraph2F(star_gold_x[0], star_gold_y[0], 50.0f, 50.0f, star_gold_extrate[0], star_angle[0], star_gold_images[star_img_num[0]], TRUE);

		//if (star_click[0] == false && star_x[0] == star_gold_x[0] && star_hp[0] > 0)
		//{
		//	// 描画ブレンドモードをアルファブレンドにする
		//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kirakira_alpha[0]);
		//	DrawRotaGraph2F(star_gold_x[0] - 30.0f, star_gold_y[0] - 3.0f, 16.0f, 16.0f, 0.8f, star_angle[0], kirakira_img[kirakira_anim_num[0]], TRUE);
		//	DrawRotaGraph2F(star_gold_x[0] + 32.0f, star_gold_y[0] + 20.0f, 16.0f, 16.0f, 0.8f, star_angle[0], kirakira_img[kirakira_anim_num[1]], TRUE);
		//	// 描画ブレンドモードをノーブレンドにする
		//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//}

		break;

	case 2:
		// 銀の星描画
		for (int i = 0; i < 3; i++)
		{
			DrawRotaGraph2F(star_x[i], star_y[i], 50.0f, 50.0f, star_extrate[i], star_angle[i], star_silver_image, TRUE);
		}

		// 火の描画
		for (int i = 0; i < star_num; i++)
		{
			if (star_hp[i] == 0 && star_back[i] == false)
			{
				DrawRotaGraph2F(star_gold_x[i] + fire_x[i], star_gold_y[i] + fire_y[i], 250.0f, 363.5f, fire_extrate[i], star_angle[i], fire_image, TRUE);
			}

			//DrawRotaGraph2F(star_gold_x[i] + fire_x[i], star_gold_y[i] + fire_y[i], 250.0f, 363.5f, fire_extrate[i], star_angle[i], fire_image, TRUE);
		}

		// 金の星描画
		for (int i = 0; i < star_num; i++)
		{
			if (i >= 1 && is_star_min[i - 1] == true)
			{
				DrawRotaGraph2F(star_gold_x[i], star_gold_y[i], 50.0f, 50.0f, star_gold_extrate[i], star_angle[i], star_gold_images[star_img_num[i]], TRUE);
			}
			else
			{
				DrawRotaGraph2F(star_gold_x[0], star_gold_y[0], 50.0f, 50.0f, star_gold_extrate[0], star_angle[0], star_gold_images[star_img_num[0]], TRUE);
			}
		}

		//if (star_click[0] == false && star_x[0] == star_gold_x[0] && star_hp[0] > 0)
		//{
		//	// 描画ブレンドモードをアルファブレンドにする
		//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kirakira_alpha[0]);
		//	DrawRotaGraph2F(star_gold_x[0] - 30.0f, star_gold_y[0] - 3.0f, 16.0f, 16.0f, 0.8f, star_angle[0], kirakira_img[kirakira_anim_num[0]], TRUE);
		//	DrawRotaGraph2F(star_gold_x[0] + 32.0f, star_gold_y[0] + 20.0f, 16.0f, 16.0f, 0.8f, star_angle[0], kirakira_img[kirakira_anim_num[1]], TRUE);
		//	// 描画ブレンドモードをノーブレンドにする
		//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//}

		//if (star_click[1] == false && star_x[1] == star_gold_x[1] && star_hp[1] > 0)
		//{
		//	// 描画ブレンドモードをアルファブレンドにする
		//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kirakira_alpha[1]);
		//	DrawRotaGraph2F(star_gold_x[1] - 38.0f, star_gold_y[1] - 10.0f, 16.0f, 16.0f, 1.0f, star_angle[1], kirakira_img[kirakira_anim_num[2]], TRUE);
		//	DrawRotaGraph2F(star_gold_x[1] + 34.0f, star_gold_y[1] + 37.0f, 16.0f, 16.0f, 1.0f, star_angle[1], kirakira_img[kirakira_anim_num[3]], TRUE);
		//	// 描画ブレンドモードをノーブレンドにする
		//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//}

		break;

	case 3:

		for (int i = 0; i < 3; i++)
		{
			// 銀の星描画
			DrawRotaGraph2F(star_x[i], star_y[i], 50.0f, 50.0f, star_extrate[i], star_angle[i], star_silver_image, TRUE);

			// 火の描画
			if (star_hp[i] == 0 && star_back[i] == false)
			{
				DrawRotaGraph2F(star_gold_x[i] + fire_x[i], star_gold_y[i] + fire_y[i], 250.0f, 363.5f, fire_extrate[i], star_angle[i], fire_image, TRUE);
			}

			//DrawRotaGraph2F(star_gold_x[i] + fire_x[i], star_gold_y[i] + fire_y[i], 250.0f, 363.5f, fire_extrate[i], star_angle[i], fire_image, TRUE);

			// 金の星描画
			if (i >= 1 && is_star_min[i - 1] == true)
			{
				DrawRotaGraph2F(star_gold_x[i], star_gold_y[i], 50.0f, 50.0f, star_gold_extrate[i], star_angle[i], star_gold_images[star_img_num[i]], TRUE);
			}
			else
			{
				DrawRotaGraph2F(star_gold_x[0], star_gold_y[0], 50.0f, 50.0f, star_gold_extrate[0], star_angle[0], star_gold_images[star_img_num[0]], TRUE);
			}

			// キラキラの描画
			//if (star_click[0] == false && star_x[0] == star_gold_x[0] && star_hp[0] > 0)
			//{
			//	//// 描画ブレンドモードをアルファブレンドにする
			//	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, kirakira_alpha[0]);
			//	//DrawRotaGraph2F(star_gold_x[0] - 30.0f, star_gold_y[0] - 3.0f, 16.0f, 16.0f, 0.8f, star_angle[0], kirakira_img[kirakira_anim_num[0]], TRUE);
			//	//DrawRotaGraph2F(star_gold_x[0] + 32.0f, star_gold_y[0] + 20.0f, 16.0f, 16.0f, 0.8f, star_angle[0], kirakira_img[kirakira_anim_num[1]], TRUE);
			//	//// 描画ブレンドモードをノーブレンドにする
			//	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			//	//DrawBox();
			//}
			
			//if (star_click[0] == false && star_x[0] == star_gold_x[0] && star_hp[0] > 0)
			//{
			//	// 描画ブレンドモードをアルファブレンドにする
			//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kirakira_alpha[0]);
			//	DrawRotaGraph2F(star_gold_x[0] - 30.0f, star_gold_y[0] - 3.0f, 16.0f, 16.0f, 0.8f, star_angle[0], kirakira_img[kirakira_anim_num[0]], TRUE);
			//	DrawRotaGraph2F(star_gold_x[0] + 32.0f, star_gold_y[0] + 20.0f, 16.0f, 16.0f, 0.8f, star_angle[0], kirakira_img[kirakira_anim_num[1]], TRUE);
			//	// 描画ブレンドモードをノーブレンドにする
			//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			//}

			//if (star_click[1] == false && star_x[1] == star_gold_x[1] && star_hp[1] > 0)
			//{
			//	// 描画ブレンドモードをアルファブレンドにする
			//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kirakira_alpha[1]);
			//	DrawRotaGraph2F(star_gold_x[1] - 38.0f, star_gold_y[1] - 10.0f, 16.0f, 16.0f, 1.0f, star_angle[1], kirakira_img[kirakira_anim_num[2]], TRUE);
			//	DrawRotaGraph2F(star_gold_x[1] + 34.0f, star_gold_y[1] + 37.0f, 16.0f, 16.0f, 1.0f, star_angle[1], kirakira_img[kirakira_anim_num[3]], TRUE);
			//	// 描画ブレンドモードをノーブレンドにする
			//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			//}

			//if (star_click[2] == false && star_x[2] == star_gold_x[2] && star_hp[2] > 0)
			//{
			//	// 描画ブレンドモードをアルファブレンドにする
			//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kirakira_alpha[2]);
			//	DrawRotaGraph2F(star_gold_x[2] - 25.0f, star_gold_y[2] - 20.0f, 16.0f, 16.0f, 0.8f, star_angle[2], kirakira_img[kirakira_anim_num[4]], TRUE);
			//	DrawRotaGraph2F(star_gold_x[2] + 22.0f, star_gold_y[2] + 34.0f, 16.0f, 16.0f, 0.8f, star_angle[2], kirakira_img[kirakira_anim_num[5]], TRUE);
			//	// 描画ブレンドモードをノーブレンドにする
			//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			//}
		}


		break;

	default:
		// 銀の星描画
		for (int i = 0; i < 3; i++)
		{
			DrawRotaGraph2F(star_x[i], star_y[i], 50.0f, 50.0f, star_extrate[i], star_angle[i], star_silver_image, TRUE);
		}
		break;
	}

	// リザルト結果表示ゾーンの描画
	DrawGraph(30, 300 + 20, result_img, TRUE);

	// 数字画像の色変更
	// 描画輝度のセット
	SetDrawBright(253, 236, 166);

	// 倒した敵の数の描画
	if (kill_enemy_num < 10)
	{
		DrawExtendGraph(228, 323 + 20, 228 + 25, 323 + 25 + 20, num_img[kill_enemy_num_2], TRUE);
	}
	else if (kill_enemy_num < 100)
	{
		DrawExtendGraph(218, 323 + 20, 218 + 25, 323 + 25 + 20, num_img[kill_enemy_num_2 / 10], TRUE);
		DrawExtendGraph(238, 323 + 20, 238 + 25, 323 + 25 + 20, num_img[kill_enemy_num_2 % 10], TRUE);
	}
	else
	{
		DrawExtendGraph(208, 323 + 20, 208 + 25, 323 + 25 + 20, num_img[kill_enemy_num_2 / 100], TRUE);
		DrawExtendGraph(228, 323 + 20, 228 + 25, 323 + 25 + 20, num_img[kill_enemy_num_2 % 100 / 10], TRUE);
		DrawExtendGraph(248, 323 + 20, 248 + 25, 323 + 25 + 20, num_img[kill_enemy_num_2 % 100 % 10], TRUE);
	}

	// 獲得したコインの枚数の描画
	if (get_coin_num < 10)
	{
		DrawExtendGraph(272, 385 + 20, 272 + 25, 385 + 25 + 20, num_img[get_coin_num_2], TRUE);
	}
	else if (get_coin_num < 100)
	{
		DrawExtendGraph(262, 385 + 20, 262 + 25, 385 + 25 + 20, num_img[get_coin_num_2 / 10], TRUE);
		DrawExtendGraph(282, 385 + 20, 282 + 25, 385 + 25 + 20, num_img[get_coin_num_2 % 10], TRUE);
	}
	else
	{
		DrawExtendGraph(252, 385 + 20, 252 + 25, 385 + 25 + 20, num_img[get_coin_num_2 / 100], TRUE);
		DrawExtendGraph(272, 385 + 20, 272 + 25, 385 + 25 + 20, num_img[get_coin_num_2 % 100 / 10], TRUE);
		DrawExtendGraph(292, 385 + 20, 292 + 25, 385 + 25 + 20, num_img[get_coin_num_2 % 100 % 10], TRUE);
	}

	// スコアの描画
	if (score < 10)
	{
		DrawExtendGraph(217, 445 + 20, 217 + 32, 445 + 32 + 20, num_img[score_2], TRUE);
	}
	else if (score < 100)
	{
		DrawExtendGraph(200, 445 + 20, 200 + 32, 445 + 32 + 20, num_img[score_2 / 10], TRUE);
		DrawExtendGraph(230, 445 + 20, 230 + 32, 445 + 32 + 20, num_img[score_2 % 10], TRUE);
	}
	else if(score < 1000)
	{
		DrawExtendGraph(185, 445 + 20, 185 + 32, 445 + 32 + 20, num_img[score_2 / 100], TRUE);
		DrawExtendGraph(215, 445 + 20, 215 + 32, 445 + 32 + 20, num_img[score_2 % 100 / 10], TRUE);
		DrawExtendGraph(245, 445 + 20, 245 + 32, 445 + 32 + 20, num_img[score_2 % 100 % 10], TRUE);
	}
	else if (score < 10000)
	{
		DrawExtendGraph(170, 445 + 20, 170 + 32, 445 + 32 + 20, num_img[score_2 / 1000], TRUE);
		DrawExtendGraph(200, 445 + 20, 200 + 32, 445 + 32 + 20, num_img[score_2 % 1000 / 100], TRUE);
		DrawExtendGraph(230, 445 + 20, 230 + 32, 445 + 32 + 20, num_img[score_2 % 1000 % 100 / 10], TRUE);
		DrawExtendGraph(260, 445 + 20, 260 + 32, 445 + 32 + 20, num_img[score_2 % 1000 % 100 % 10], TRUE);
	}
	else 
	{
		DrawExtendGraph(167, 445 + 20, 167 + 32, 445 + 32 + 20, num_img[score_2 / 10000], TRUE);
		DrawExtendGraph(192, 445 + 20, 192 + 32, 445 + 32 + 20, num_img[score_2 % 10000 / 1000], TRUE);
		DrawExtendGraph(217, 445 + 20, 217 + 32, 445 + 32 + 20, num_img[score_2 % 10000 % 1000 / 100], TRUE);
		DrawExtendGraph(242, 445 + 20, 242 + 32, 445 + 32 + 20, num_img[score_2 % 10000 % 1000 % 100 / 10], TRUE);
		DrawExtendGraph(267, 445 + 20, 267 + 32, 445 + 32 + 20, num_img[score_2 % 10000 % 1000 % 100 % 10], TRUE);

	}

	// 描画輝度を元に戻す
	SetDrawBright(255, 255, 255);

	// ボタンの描画
	DrawButton();


	for (int i = 0; i < star_num; i++)
	{
		if (is_gstar_click[i] == true)
		{
			DrawRotaGraph2F(star_x[i], star_y[i], 16.0f, 16.0f, gstar_effect_extrate[i], star_angle[i], gstar_effect_img[i], TRUE);
		}
	}

	// カーソル描画
	cursor->Draw();

	// プレイヤーがボタンをクリックしたか？
	if (select != -1 && change_wait_time > 40)
	{
		fade->Draw();
	}

	if (is_clear == true)
	{
		// 描画ブレンドモードをアルファブレンドにする
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, black_alpha);
		DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xffffff, TRUE);
		// 描画ブレンドモードをノーブレンドにする
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		// 描画ブレンドモードをアルファブレンドにする
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, black_alpha);
		DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x000000, TRUE);
		// 描画ブレンドモードをノーブレンドにする
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	/*DrawBox(star_x[0] , star_y[0] , star_x[0] + STAR_WIDTH , star_y[0] + STAR_HEIGHT, 0x000000, FALSE);*/
	/*DrawCircle(STAR_GOLD_X, STAR_GOLD_Y, 2, 0x000000, TRUE);
	DrawCircle(star_gold_x[1], star_gold_y[1], 2, 0x000000, TRUE);
	DrawCircle(star_gold_x[2], star_gold_y[2], 2, 0x000000, TRUE);

	DrawRotaGraph(0, 0, 1.0f, 0, star_gold_images[0], TRUE);*/
	//DrawFormatString(0, 0, 0x000000, "%d", kirakira_alpha[0]);
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

			TitleScene::is_bgm_active = false;
			TitleScene::is_fade = true;

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

// 星とカーソルの当たり判定
void ResultScene::StarHitCheck()
{
	if (cursor->GetPState() == P_State::attack && cursor->GetCanHit() == true)
	{
		// プレイヤーがクリックしたとき、星の上でクリックされたか？
		if (HitBoxCircle(star_x[0], star_y[0], STAR_WIDTH, STAR_HEIGHT, cursor->GetLocation(), cursor->GetRadius()))
		{
			star_click[0] = true;
			kirakira_alpha[0] = 0;
			star_unclick_cnt[0] = 0;

			if (star_gold[0] == true && is_star_min[0] == true && star_hp[0] >= 1)
			{
				star_hp[0]--;

				is_gstar_click[0] = true;

				if (star_hp[0] == 0)
				{
					PlaySoundMem(fire_se, DX_PLAYTYPE_BACK, TRUE);
				}

				PlaySoundMem(star_click_se[1], DX_PLAYTYPE_BACK, TRUE);
			}
			else if(star_num > 0  && is_star_min[0] == true)
			{
				if (star_hp[0] == 0 && star_gold_y[0] <= STAR_Y - 40.0f)
				{
					//鉄の音
					PlaySoundMem(star_click_se[0], DX_PLAYTYPE_BACK, TRUE);
				}
				else
				{
					is_gstar_click[0] = true;
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
			star_click[1] = true;
			kirakira_alpha[1] = 0;
			star_unclick_cnt[1] = 0;

			if (star_gold[1] == true && is_star_min[1] == true && star_hp[1] >= 1)
			{
				star_hp[1]--;

				is_gstar_click[1] = true;
	
				if (star_hp[1] == 0)
				{
					PlaySoundMem(fire_se, DX_PLAYTYPE_BACK, TRUE);
				}

				PlaySoundMem(star_click_se[1], DX_PLAYTYPE_BACK, TRUE);
			}
			else if (star_num > 1 && is_star_min[1] == true)
			{
				if (star_hp[1] == 0 && star_gold_y[1] <= (STAR_Y - 40.0f) - 40.0f)
				{
					//鉄の音
					PlaySoundMem(star_click_se[0], DX_PLAYTYPE_BACK, TRUE);
				}
				else
				{
					is_gstar_click[1] = true;
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
			star_click[2] = true;
			kirakira_alpha[2] = 0;
			star_unclick_cnt[2] = 0;

			if (star_gold[2] == true && is_star_min[2] == true && star_hp[2] >= 1)
			{
				star_hp[2]--;

				is_gstar_click[2] = true;

				if (star_hp[2] == 0)
				{
					PlaySoundMem(fire_se, DX_PLAYTYPE_BACK, TRUE);
				}

				PlaySoundMem(star_click_se[1], DX_PLAYTYPE_BACK, TRUE);
			}
			else if(star_num > 2 && is_star_min[2] == true)
			{
				if (star_hp[2] == 0 && star_gold_y[2] <= STAR_Y - 40.0f)
				{
					//鉄の音
					PlaySoundMem(star_click_se[0], DX_PLAYTYPE_BACK, TRUE);
				}
				else
				{
					is_gstar_click[2] = true;
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
				PlaySoundMem(star_back_se, DX_PLAYTYPE_BACK, TRUE);
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
				PlaySoundMem(star_back_se, DX_PLAYTYPE_BACK, TRUE);
				star_hp[1] = 10;
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
				PlaySoundMem(star_back_se, DX_PLAYTYPE_BACK, TRUE);
				star_hp[2] = 5;
				star_gold_x[2] = STAR_X + 170.0f;
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
	if (HitBoxCircle(retry_x, retry_y, BUTTON_WIDTH, BUTTON_HEIGHT, cursor->GetLocation(), cursor->GetRadius()) == true)
	{
		overlap_retry_button_flg = true;

		if (cursor->GetCanHit() == true)
		{
			// リトライボタンをクリックした
			select = 0;
		}
	}
	else
	{
		if (HitBoxCircle(title_x, title_y, BUTTON_WIDTH, BUTTON_HEIGHT, cursor->GetLocation(), cursor->GetRadius()) == true)
		{
			overlap_title_button_flg = true;

			if (cursor->GetCanHit() == true)
			{
				// タイトルボタンをクリックした
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
	if (overlap_retry_button_flg == true)
	{
		// リトライボタンを暗くする
		// 描画輝度のセット
		SetDrawBright(128, 128, 128);
		// リトライボタン画像の描画
		DrawRotaGraphF(retry_x, retry_y, 1.0, 0.0, retry_button_img[retry_img_num], TRUE);
		// 描画輝度を元に戻す
		SetDrawBright(255, 255, 255);

		// タイトルボタン画像の描画
		DrawRotaGraphF(title_x, title_y, 1.0, 0.0, title_button_img[title_img_num], TRUE);
	}
	else if (overlap_title_button_flg == true)
	{
		// リトライボタン画像の描画
		DrawRotaGraphF(retry_x, retry_y, 1.0, 0.0, retry_button_img[retry_img_num], TRUE);

		// タイトルボタンを暗くする
		// 描画輝度のセット
		SetDrawBright(128, 128, 128);
		// タイトルボタン画像の描画
		DrawRotaGraphF(title_x, title_y, 1.0, 0.0, title_button_img[title_img_num], TRUE);
		// 描画輝度を元に戻す
		SetDrawBright(255, 255, 255);
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
		if (star_gold_extrate[i] <= 0.75f)
		{
			is_star_min[i] = true;
			is_gstar_click[i] = true;
			star_click[i] = true;
			kirakira_alpha[i] = 0;
			star_unclick_cnt[i] = 0;
			PlaySoundMem(star_click_se[1], DX_PLAYTYPE_BACK, TRUE);
			star_gold_extrate[i] = 0.75f;
		}
		else
		{
			star_gold_extrate[i] -= 0.14f;
		}

		break;

	case 1:
		if (star_gold_extrate[i] <= 1.0f)
		{
			is_star_min[i] = true;
			is_gstar_click[i] = true;
			star_click[i] = true;
			kirakira_alpha[i] = 0;
			star_unclick_cnt[i] = 0;
			PlaySoundMem(star_click_se[1], DX_PLAYTYPE_BACK, TRUE);
			star_gold_extrate[i] = 1.0f;
		}
		else if(is_star_min[i - 1] == true)
		{
			star_gold_extrate[i] -= 0.14f;
		}

		break;
	case 2:
		if (star_gold_extrate[i] <= 0.75f)
		{
			is_star_min[i] = true;
			is_gstar_click[i] = true;
			star_click[i] = true;
			kirakira_alpha[i] = 0;
			star_unclick_cnt[i] = 0;
			PlaySoundMem(star_click_se[1], DX_PLAYTYPE_BACK, TRUE);
			star_gold_extrate[i] = 0.75f;
		}
		else if (is_star_min[i - 1] == true)
		{
			star_gold_extrate[i] -= 0.14f;
		}
		break;
	default:
		break;
	}
}

void ResultScene::GStarClickEffect()
{
	for (int i = 0; i < 3; i++)
	{
		if (is_gstar_click[i] == true)
		{
			if (gstar_effect_num[i] >= 2)
			{
				gstar_effect_change_num[i]++;

				if (gstar_effect_change_num[i] >= 5)
				{
					gstar_effect_change_num[i] = 0;
					is_gstar_click[i] = false;
					gstar_effect_num[i] = 0;
					gstar_effect_img[i] = gstar_click_effect[gstar_effect_num[i]];
				}
			}
			else
			{
				gstar_effect_change_num[i]++;

				if (gstar_effect_change_num[i] >= 5)
				{
					gstar_effect_change_num[i] = 0;
					gstar_effect_num[i]++;
					gstar_effect_img[i] = gstar_click_effect[gstar_effect_num[i]];
				}
			}
		}
	}
}

void ResultScene::AddNum()
{
	if (get_coin_num_2 != get_coin_num)
	{
		if (get_coin_num < 100)
		{
			get_coin_num_2++;
		}
		else
		{
			get_coin_num_2 += 3;
		}

		if (get_coin_num_2 >= get_coin_num)
		{
			get_coin_num_2 = get_coin_num;
		}
	}


	if (kill_enemy_num_2 != kill_enemy_num)
	{
		if (kill_enemy_num < 100)
		{
			kill_enemy_num_2++;
		}
		else
		{
			kill_enemy_num_2 += 3;
		}

		if (kill_enemy_num_2 >= kill_enemy_num)
		{
			kill_enemy_num_2 = kill_enemy_num;
		}
	}


	if (score_2 != score)
	{
		if (score < 100)
		{
			score_2++;
		}
		else if(score < 1000)
		{
			score_2 += 35;
		}
		else
		{
			score_2 += 145;
		}

		if (score_2 >= score)
		{
			score_2 = score;
		}
	}

}

void ResultScene::ChangeKirakiraAlpha()
{
	for (int i = 0; i < 3; i++)
	{
		if (star_click[i] == false && star_hp[i] > 0)
		{

				if (kirakira_alpha[i] != 255)
				{
					kirakira_alpha[i]++;

					if (kirakira_alpha[i] >= 255)
					{
						kirakira_alpha[i] = 255;
					}
				}
			
		}
	}
}

void ResultScene::KirakiraAnimControl()
{
	for (int i = 0; i < 3; i++)
	{
		kirakira_anim_cnt[i]++;

		if (kirakira_anim_cnt[i] > 10)
		{
			/*if (star_img_num[i] > 0)
			{
				if (star_img_num[i] < 3)
				{
					star_img_num[i]++;
				}
				else
				{
					star_img_num[i] = 0;
				}
				
				kirakira_anim_cnt[i] = 0;
			}
			else
			{
				kirakira_wait_time[i]++;

				if (kirakira_wait_time[i] > 20)
				{
					star_img_num[i] = 1;
					kirakira_wait_time[i] = 0;
				}
			}*/

			if (star_img_num[i] < 3)
			{
				star_img_num[i]++;
			}
			else
			{
				star_img_num[i] = 0;
			}
			kirakira_anim_cnt[i] = 0;
		}
	}
}

void ResultScene::StarUnClickCount()
{
	for (int i = 0; i < 3; i++)
	{
		if (star_click[i] == true && star_hp[i] > 0)
		{
			star_unclick_cnt[i]++;
		}

		switch (i)
		{
		case 0:
			if (star_unclick_cnt[0] > 120)
			{
				star_unclick_cnt[0] = 0;
				star_click[0] = false;
			}
			break;
		case 1:
			if (star_unclick_cnt[1] > 70)
			{
				star_unclick_cnt[1] = 0;
				star_click[1] = false;
			}
			break;
		case 2:
			if (star_unclick_cnt[2] > 150)
			{
				star_unclick_cnt[2] = 0;
				star_click[2] = false;
			}
			break;
		default:
			break;
		}
		
	}
}