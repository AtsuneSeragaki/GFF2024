#include "TitleScene.h"
#include "EndScene.h"
#include "GameMainScene.h"
#include "../UtilityFile/ResourceManager.h"
#include "../UtilityFile/Define.h"
#include "DxLib.h"
#include <math.h>

TitleScene::TitleScene()
{
	//x1 = 85.0f;
	//x2 = 275.0f;
	//y1 = 300.0f;
	//y2 = 300.0f;

	cursor = new Cursor;
	opening_anim = new OpeningAnim;

	select = -1;

	//on_button = -1;

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

	// 雲画像読み込み
	tmp_img = rm->GetImages("Resource/Images/Opening/cloud.png");
	cloud_img.push_back(tmp_img[0]);

	// スタートボタン画像の読み込み
	tmp_img = rm->GetImages("Resource/Images/Opening/StartButton.png", 2, 2, 1, 130, 70);
	for (int i = 0; i < 2; i++)
	{
		start_button_img.push_back(tmp_img[i]);
	}

	// エンドボタン画像の読み込み
	tmp_img = rm->GetImages("Resource/Images/Opening/EndButton.png", 2, 2, 1, 130, 70);
	for (int i = 0; i < 2; i++)
	{
		end_button_img.push_back(tmp_img[i]);
	}

	is_bgm_active = false;
	
	start_img_num = 0;
	end_img_num = 0;
	button_anim_count = 0;

	// ボタン座標の設定
	start_x = SCREEN_WIDTH / 2;
	start_y = GET_LANE_HEIGHT(6);
	end_x = SCREEN_WIDTH / 2;
	end_y = GET_LANE_HEIGHT(7.5f);

	change_screen_flg = false;

	// 音量変更
	ChangeVolumeSoundMem(220, bgm);
}

TitleScene::~TitleScene()
{
	delete cursor;
	delete opening_anim;
}

void TitleScene::Update()
{
	if (is_bgm_active == false)
	{
		is_bgm_active = true;
		// BGM再生
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);
	}
	if (opening_anim->GetAnimEnd() == false)
	{
		opening_anim->Update();
		return;
	}
	if (select != -1)
	{
		button_anim_count++;
		if (button_anim_count < 10)
		{
			if (select == 0)
			{
				// スタートボタンの画像切り替え
				start_img_num = 1;
			}
			else
			{
				// エンドボタンの画像切り替え
				end_img_num = 1;
			}
		}
		else
		{
			// 画面遷移して良い
			change_screen_flg = true;
		}
	}

	cursor->Update();

	//if (cursor->GetPState() == P_State::attack && cursor->GetCanHit() == true)
	//{
	//	if (HitBoxCircle(x1, y1, cursor->GetLocation(), cursor->GetRadius()) == true)
	//	{
	//		// startがクリックされた
	//		select = 0;
	//	}
	//	else
	//	{
	//		if (HitBoxCircle(x2, y2, cursor->GetLocation(), cursor->GetRadius()) == true)
	//		{
	//			// endがクリックされた
	//			select = 1;
	//		}
	//	}
	//}
	//else
	//{
	//	if (HitBoxCircle(x1, y1, cursor->GetLocation(), cursor->GetRadius()) == true)
	//	{
	//		// startの上にカーソルがある
	//		on_button = 0;
	//	}
	//	else
	//	{
	//		if (HitBoxCircle(x2, y2, cursor->GetLocation(), cursor->GetRadius()) == true)
	//		{
	//			// endの上にカーソルがある
	//			on_button = 1;
	//		}
	//		else
	//		{
	//			on_button = -1;
	//		}
	//	}
	//}

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
	//else
	//{
	//	if (HitBoxCircle(start_x, start_y, cursor->GetLocation(), cursor->GetRadius()) == true)
	//	{
	//		// startの上にカーソルがある
	//		on_button = 0;
	//	}
	//	else
	//	{
	//		if (HitBoxCircle(end_x, end_y, cursor->GetLocation(), cursor->GetRadius()) == true)
	//		{
	//			// endの上にカーソルがある
	//			on_button = 1;
	//		}
	//		else
	//		{
	//			on_button = -1;
	//		}
	//	}
	//}

}

void TitleScene::Draw() const
{
	// 背景色（水色）
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xbdf4ff, TRUE);
	// 背景の雲
	DrawRotaGraph(60, GET_LANE_HEIGHT(4), 2, 0, cloud_img[0], TRUE);
	DrawRotaGraph(LANE_WIDTH * 3 - 60, GET_LANE_HEIGHT(2), 2, 0, cloud_img[0], TRUE);


	if (opening_anim->GetAnimEnd() == false)
	{
		int disp_num = opening_anim->GetDisplay_num();
		switch (disp_num)
		{
		case 1:
			// タイトルロゴ
			DrawRotaGraph(SCREEN_WIDTH / 2, GET_LANE_HEIGHT(3), 1, 0, titlelogo_img[0], TRUE);
			
			break;
		case 2:
			// タイトルロゴ
			DrawRotaGraph(SCREEN_WIDTH / 2, GET_LANE_HEIGHT(3), 1, 0, titlelogo_img[0], TRUE);
			// スタートボタン画像の描画
			DrawRotaGraphF(start_x, start_y, 1.0, 0.0, start_button_img[start_img_num], TRUE);

			break;
		case 3:
			// タイトルロゴ
			DrawRotaGraph(SCREEN_WIDTH / 2, GET_LANE_HEIGHT(3), 1, 0, titlelogo_img[0], TRUE);
			// スタートボタン画像の描画
			DrawRotaGraphF(start_x, start_y, 1.0, 0.0, start_button_img[start_img_num], TRUE);
			// エンドボタン画像の描画
			DrawRotaGraphF(end_x, end_y, 1.0, 0.0, end_button_img[end_img_num], TRUE);

			break;
		default:
			break;
		}

		opening_anim->Draw();
	}
	else
	{
		// 背景の雲
		//DrawRotaGraph(60, GET_LANE_HEIGHT(4), 2, 0, cloud_img[0], TRUE);
		//DrawRotaGraph(LANE_WIDTH * 3 - 60, GET_LANE_HEIGHT(2), 2, 0, cloud_img[0], TRUE);

		// タイトルロゴ
		DrawRotaGraph(SCREEN_WIDTH / 2, GET_LANE_HEIGHT(3), 1, 0, titlelogo_img[0], TRUE);

		// スタートボタン画像の描画
		DrawRotaGraphF(start_x, start_y, 1.0, 0.0, start_button_img[start_img_num], TRUE);
		// エンドボタン画像の描画
		DrawRotaGraphF(end_x, end_y, 1.0, 0.0, end_button_img[end_img_num], TRUE);


		//switch (on_button)
		//{
		//case 0:
		//	// スタートにカーソルが重なっているとき
		//	DrawBoxAA(x1 - (float)BOX_WIDTH / 2, y1 - (float)BOX_HEIGHT / 2, x1 + (float)BOX_WIDTH / 2, y1 + (float)BOX_HEIGHT / 2, 0x999999, TRUE);
		//	DrawString((x1 - (float)BOX_WIDTH / 2) + 30, (y1 - (float)BOX_HEIGHT / 2) + 20, "START", 0x000000);
		//	DrawBoxAA(x2 - (float)BOX_WIDTH / 2, y2 - (float)BOX_HEIGHT / 2, x2 + (float)BOX_WIDTH / 2, y2 + (float)BOX_HEIGHT / 2, 0xffffff, TRUE);
		//	DrawString((x2 - (float)BOX_WIDTH / 2) + 35, (y2 - (float)BOX_HEIGHT / 2) + 20, "END", 0x000000);

		//	// スタートボタンにカーソルが重なっているとき
		//	// 描画輝度のセット
		//	SetDrawBright(128, 128, 128);
		//	//  スタートボタンボタン画像の描画
		//	//DrawRotaGraphF(start_x, start_y, 1.0, 0.0, start_button_img[start_img_num], TRUE);
		//	// 描画輝度を元に戻す
		//	SetDrawBright(255, 255, 255);

		//	break;

		//case 1:
		//	// エンドにカーソルが重なっているとき
		//	DrawBoxAA(x1 - (float)BOX_WIDTH / 2, y1 - (float)BOX_HEIGHT / 2, x1 + (float)BOX_WIDTH / 2, y1 + (float)BOX_HEIGHT / 2, 0xffffff, TRUE);
		//	DrawString((x1 - (float)BOX_WIDTH / 2) + 30, (y1 - (float)BOX_HEIGHT / 2) + 20, "START", 0x000000);
		//	DrawBoxAA(x2 - (float)BOX_WIDTH / 2, y2 - (float)BOX_HEIGHT / 2, x2 + (float)BOX_WIDTH / 2, y2 + (float)BOX_HEIGHT / 2, 0x999999, TRUE);
		//	DrawString((x2 - (float)BOX_WIDTH / 2) + 35, (y2 - (float)BOX_HEIGHT / 2) + 20, "END", 0x000000);

		//	// エンドボタンにカーソルが重なっているとき
		//	// 描画輝度のセット
		//	SetDrawBright(128, 128, 128);
		//	// エンドボタンボタン画像の描画
		//	//DrawRotaGraphF(end_x, end_y, 1.0, 0.0, end_button_img[end_img_num], TRUE);
		//	// 描画輝度を元に戻す
		//	SetDrawBright(255, 255, 255);

		//	break;

		//default:
		//	// ボタンの上にカーソルが重なっていないとき
		//	DrawBoxAA(x1 - (float)BOX_WIDTH / 2, y1 - (float)BOX_HEIGHT / 2, x1 + (float)BOX_WIDTH / 2, y1 + (float)BOX_HEIGHT / 2, 0xffffff, TRUE);
		//	DrawString((x1 - (float)BOX_WIDTH / 2) + 30, (y1 - (float)BOX_HEIGHT / 2) + 20, "START", 0x000000);
		//	DrawBoxAA(x2 - (float)BOX_WIDTH / 2, y2 - (float)BOX_HEIGHT / 2, x2 + (float)BOX_WIDTH / 2, y2 + (float)BOX_HEIGHT / 2, 0xffffff, TRUE);
		//	DrawString((x2 - (float)BOX_WIDTH / 2) + 35, (y2 - (float)BOX_HEIGHT / 2) + 20, "END", 0x000000);
		//	break;
		//}

		cursor->Draw();
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
	box_left = box_x - BUTTON_BOX_WIDTH / 2;
	box_top =  box_y - BUTTON_BOX_HEIGHT / 2;
	box_right = box_x + BUTTON_BOX_WIDTH / 2;
	box_bottom = box_y + BUTTON_BOX_HEIGHT / 2;

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