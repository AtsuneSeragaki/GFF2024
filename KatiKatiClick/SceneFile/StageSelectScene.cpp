#include "StageSelectScene.h"

#include "TitleScene.h"
#include "GameMainScene.h"
#include "../UtilityFile/ResourceManager.h"
#include "../UtilityFile/Define.h"
#include "DxLib.h"

StageSelectScene::StageSelectScene()
{
	fade = new Fade();
	cursor = new Cursor();
	select = -1;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();

	int tmp_bgm;
	tmp_bgm = rm->GetSounds("Resource/Sounds/Result/bgm.mp3");
	bgm = tmp_bgm;

	is_bgm_active = false;

	// 音量変更
	bgm_volume = 200;
	ChangeVolumeSoundMem(bgm_volume, bgm);

	std::vector<int> tmp = rm->GetImages("Resource/Images/Result/TitleButton.png", 3, 3, 1, 130, 70);
	for (int i = 0; i < 3; i++)
	{
		stage1_button_img.push_back(tmp[i]);
	}

	tmp = rm->GetImages("Resource/Images/Result/TitleButton.png", 3, 3, 1, 130, 70);
	for (int i = 0; i < 3; i++)
	{
		stage2_button_img.push_back(tmp[i]);
	}

	tmp = rm->GetImages("Resource/Images/Result/TitleButton.png", 3, 3, 1, 130, 70);
	for (int i = 0; i < 3; i++)
	{
		stage3_button_img.push_back(tmp[i]);
	}

	// タイトルボタン画像の読み込み
	tmp = rm->GetImages("Resource/Images/Result/TitleButton.png", 3, 3, 1, 130, 70);
	for (int i = 0; i < 3; i++)
	{
		title_button_img.push_back(tmp[i]);
	}

	stage1_img_num = 0;	
	stage2_img_num = 0;
	stage3_img_num = 0;

	overlap_stage1_button_flg = false;
	overlap_stage2_button_flg = false;
	overlap_stage3_button_flg = false;

	stage1_x = 180.0f;
	stage1_y = 150.0f;
	stage2_x = 180.0f;
	stage2_y = 150.0f + 180.0f;
	stage3_x = 180.0f;
	stage3_y = 150.0f + 180.0f + 180.0f;

	//text_img;                       // ステージ選択文字の画像               

	title_img_num = 0;
	change_wait_time = 0;
	title_x = SCREEN_WIDTH / 2.0f;
	title_y = 650.0f;
	change_screen_flg = false;
	overlap_title_button_flg = false;
}

StageSelectScene::~StageSelectScene()
{
	delete cursor;
	delete fade;
}

void StageSelectScene::Update()
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
		overlap_stage1_button_flg = false;
		overlap_stage2_button_flg = false;
		overlap_stage3_button_flg = false;
		overlap_title_button_flg = false;
	}

	// ボタンとカーソルの当たり判定
	ButtonHitCheck();

}

void StageSelectScene::Draw() const
{
	// 背景色
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x072246, TRUE);

	//Draw;
	DrawString(130, 30, "STAGE SELECT", 0xffffff);

	if (overlap_stage1_button_flg == true)
	{// ステージ1ボタンを選択中

		// ステージ1ボタンを暗くする
		// 描画輝度のセット
		SetDrawBright(128, 128, 128);
		// ステージ1ボタン画像の描画
		//DrawRotaGraphF(stage1_x, stage1_y, 1.0, 0.0, stage1_button_img[stage1_img_num], TRUE);
		DrawBox(stage1_x - STAGE_BUTTON_WIDTH / 2, stage1_y - STAGE_BUTTON_HEIGHT / 2, stage1_x + STAGE_BUTTON_WIDTH / 2, stage1_y + STAGE_BUTTON_HEIGHT / 2, 0xff0000, TRUE);
		// 描画輝度を元に戻す
		SetDrawBright(255, 255, 255);

		// ステージ2ボタン画像の描画
		//DrawRotaGraphF(stage2_x, stage2_y, 1.0, 0.0, stage2_button_img[stage2_img_num], TRUE);
		DrawBox(stage2_x - STAGE_BUTTON_WIDTH / 2, stage2_y - STAGE_BUTTON_HEIGHT / 2, stage2_x + STAGE_BUTTON_WIDTH / 2, stage2_y + STAGE_BUTTON_HEIGHT / 2, 0x00ff00, TRUE);

		// ステージ3ボタン画像の描画
		//DrawRotaGraphF(stage3_x, stage3_y, 1.0, 0.0, stage3_button_img[stage3_img_num], TRUE);
		DrawBox(stage3_x - STAGE_BUTTON_WIDTH / 2, stage3_y - STAGE_BUTTON_HEIGHT / 2, stage3_x + STAGE_BUTTON_WIDTH / 2, stage3_y + STAGE_BUTTON_HEIGHT / 2, 0x0000ff, TRUE);

		// タイトルボタン画像の描画
		DrawRotaGraphF(title_x, title_y, 1.0, 0.0, title_button_img[title_img_num], TRUE);

		DrawString(stage1_x, stage1_y, "STAGE1", 0xffffff);
		DrawString(stage2_x, stage2_y, "STAGE2", 0xffffff);
		DrawString(stage3_x, stage3_y, "STAGE3", 0xffffff);

	}
	else if (overlap_stage2_button_flg == true)
	{// ステージ2ボタンを選択中

		// ステージ1ボタン画像の描画
		//DrawRotaGraphF(stage1_x, stage1_y, 1.0, 0.0, stage1_button_img[stage1_img_num], TRUE);
		DrawBox(stage1_x - STAGE_BUTTON_WIDTH / 2, stage1_y - STAGE_BUTTON_HEIGHT / 2, stage1_x + STAGE_BUTTON_WIDTH / 2, stage1_y + STAGE_BUTTON_HEIGHT / 2, 0xff0000, TRUE);

		// ステージ2ボタンを暗くする
		// 描画輝度のセット
		SetDrawBright(128, 128, 128);
		// ステージ2ボタン画像の描画
		//DrawRotaGraphF(stage2_x, stage2_y, 1.0, 0.0, stage2_button_img[stage2_img_num], TRUE);
		DrawBox(stage2_x - STAGE_BUTTON_WIDTH / 2, stage2_y - STAGE_BUTTON_HEIGHT / 2, stage2_x + STAGE_BUTTON_WIDTH / 2, stage2_y + STAGE_BUTTON_HEIGHT / 2, 0x00ff00, TRUE);
		// 描画輝度を元に戻す
		SetDrawBright(255, 255, 255);

		// ステージ3ボタン画像の描画
		//DrawRotaGraphF(stage3_x, stage3_y, 1.0, 0.0, stage3_button_img[stage3_img_num], TRUE);
		DrawBox(stage3_x - STAGE_BUTTON_WIDTH / 2, stage3_y - STAGE_BUTTON_HEIGHT / 2, stage3_x + STAGE_BUTTON_WIDTH / 2, stage3_y + STAGE_BUTTON_HEIGHT / 2, 0x0000ff, TRUE);

		// タイトルボタン画像の描画
		DrawRotaGraphF(title_x, title_y, 1.0, 0.0, title_button_img[title_img_num], TRUE);

	}
	else if (overlap_stage3_button_flg == true)
	{// ステージ3ボタンを選択中

		// ステージ1ボタン画像の描画
		//DrawRotaGraphF(stage1_x, stage1_y, 1.0, 0.0, stage1_button_img[stage1_img_num], TRUE);
		DrawBox(stage1_x - STAGE_BUTTON_WIDTH / 2, stage1_y - STAGE_BUTTON_HEIGHT / 2, stage1_x + STAGE_BUTTON_WIDTH / 2, stage1_y + STAGE_BUTTON_HEIGHT / 2, 0xff0000, TRUE);

		// ステージ2ボタン画像の描画
		//DrawRotaGraphF(stage2_x, stage2_y, 1.0, 0.0, stage2_button_img[stage2_img_num], TRUE);
		DrawBox(stage2_x - STAGE_BUTTON_WIDTH / 2, stage2_y - STAGE_BUTTON_HEIGHT / 2, stage2_x + STAGE_BUTTON_WIDTH / 2, stage2_y + STAGE_BUTTON_HEIGHT / 2, 0x00ff00, TRUE);

		// ステージ3ボタンを暗くする
		// 描画輝度のセット
		SetDrawBright(128, 128, 128);
		// ステージ3ボタン画像の描画
		//DrawRotaGraphF(stage3_x, stage3_y, 1.0, 0.0, stage3_button_img[stage3_img_num], TRUE);
		DrawBox(stage3_x - STAGE_BUTTON_WIDTH / 2, stage3_y - STAGE_BUTTON_HEIGHT / 2, stage3_x + STAGE_BUTTON_WIDTH / 2, stage3_y + STAGE_BUTTON_HEIGHT / 2, 0x0000ff, TRUE);
		// 描画輝度を元に戻す
		SetDrawBright(255, 255, 255);

		// タイトルボタン画像の描画
		DrawRotaGraphF(title_x, title_y, 1.0, 0.0, title_button_img[title_img_num], TRUE);

	}
	else if (overlap_title_button_flg == true)
	{// タイトルボタンを選択中

		// ステージ1ボタン画像の描画
		//DrawRotaGraphF(stage1_x, stage1_y, 1.0, 0.0, stage1_button_img[stage1_img_num], TRUE);
		DrawBox(stage1_x - STAGE_BUTTON_WIDTH / 2, stage1_y - STAGE_BUTTON_HEIGHT / 2, stage1_x + STAGE_BUTTON_WIDTH / 2, stage1_y + STAGE_BUTTON_HEIGHT / 2, 0xff0000, TRUE);

		// ステージ2ボタン画像の描画
		//DrawRotaGraphF(stage2_x, stage2_y, 1.0, 0.0, stage2_button_img[stage2_img_num], TRUE);
		DrawBox(stage2_x - STAGE_BUTTON_WIDTH / 2, stage2_y - STAGE_BUTTON_HEIGHT / 2, stage2_x + STAGE_BUTTON_WIDTH / 2, stage2_y + STAGE_BUTTON_HEIGHT / 2, 0x00ff00, TRUE);

		// ステージ3ボタン画像の描画
		//DrawRotaGraphF(stage3_x, stage3_y, 1.0, 0.0, stage3_button_img[stage3_img_num], TRUE);
		DrawBox(stage3_x - STAGE_BUTTON_WIDTH / 2, stage3_y - STAGE_BUTTON_HEIGHT / 2, stage3_x + STAGE_BUTTON_WIDTH / 2, stage3_y + STAGE_BUTTON_HEIGHT / 2, 0x0000ff, TRUE);

		// タイトルボタンを暗くする
		// 描画輝度のセット
		SetDrawBright(128, 128, 128);
		// タイトルボタン画像の描画
		DrawRotaGraphF(title_x, title_y, 1.0, 0.0, title_button_img[title_img_num], TRUE);
		// 描画輝度を元に戻す
		SetDrawBright(255, 255, 255);
	}
	else
	{// 何も選択されていないとき

		// ステージ1ボタン画像の描画
		//DrawRotaGraphF(stage1_x, stage1_y, 1.0, 0.0, stage1_button_img[stage1_img_num], TRUE);
		DrawBox(stage1_x - STAGE_BUTTON_WIDTH / 2, stage1_y - STAGE_BUTTON_HEIGHT / 2, stage1_x + STAGE_BUTTON_WIDTH / 2, stage1_y + STAGE_BUTTON_HEIGHT / 2, 0xff0000, TRUE);

		// ステージ2ボタン画像の描画
		//DrawRotaGraphF(stage2_x, stage2_y, 1.0, 0.0, stage2_button_img[stage2_img_num], TRUE);
		DrawBox(stage2_x - STAGE_BUTTON_WIDTH / 2, stage2_y - STAGE_BUTTON_HEIGHT / 2, stage2_x + STAGE_BUTTON_WIDTH / 2, stage2_y + STAGE_BUTTON_HEIGHT / 2, 0x00ff00, TRUE);

		// ステージ3ボタン画像の描画
		//DrawRotaGraphF(stage3_x, stage3_y, 1.0, 0.0, stage3_button_img[stage3_img_num], TRUE);
		DrawBox(stage3_x - STAGE_BUTTON_WIDTH / 2, stage3_y - STAGE_BUTTON_HEIGHT / 2, stage3_x + STAGE_BUTTON_WIDTH / 2, stage3_y + STAGE_BUTTON_HEIGHT / 2, 0x0000ff, TRUE);

		// タイトルボタン画像の描画
		DrawRotaGraphF(title_x, title_y, 1.0, 0.0, title_button_img[title_img_num], TRUE);
	}

	// カーソル描画
	cursor->Draw();

	// プレイヤーがボタンをクリックしたか？
	if (select != -1 && change_wait_time > 40)
	{
		fade->Draw();
	}
}

AbstractScene* StageSelectScene::Change()
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

			// ゲームメイン画面に遷移
			return new GameMainScene();
			break;

		case 2:
			// BGMを止める
			StopSoundMem(bgm);
			is_bgm_active = false;

			// ゲームメイン画面に遷移
			return new GameMainScene();
			break;

		case 3:
			// BGMを止める
			StopSoundMem(bgm);
			is_bgm_active = false;

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

float StageSelectScene::DistanceSqrf(float box_x, float box_y, float circle_x, float circle_y)
{
	float dx = circle_x - box_x;
	float dy = circle_y - box_y;

	return (dx * dx) + (dy * dy);
}

bool StageSelectScene::HitBoxCircle(float box_x, float box_y, float width, float height, Vector2D location, float radius)
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

void StageSelectScene::ButtonHitCheck()
{
	if (HitBoxCircle(stage1_x, stage1_y, STAGE_BUTTON_WIDTH, STAGE_BUTTON_HEIGHT, cursor->GetLocation(), cursor->GetRadius()) == true)
	{
		overlap_stage1_button_flg = true;

		if (cursor->GetCanHit() == true)
		{
			// ステージ1ボタンをクリックした
			select = 0;
		}
	}
	else if (HitBoxCircle(stage2_x, stage2_y, STAGE_BUTTON_WIDTH, STAGE_BUTTON_HEIGHT, cursor->GetLocation(), cursor->GetRadius()) == true)
	{
		overlap_stage2_button_flg = true;

		if (cursor->GetCanHit() == true)
		{
			// ステージ2ボタンをクリックした
			select = 1;
		}
	}
	else if (HitBoxCircle(stage3_x, stage3_y, STAGE_BUTTON_WIDTH, STAGE_BUTTON_HEIGHT, cursor->GetLocation(), cursor->GetRadius()) == true)
	{
		overlap_stage3_button_flg = true;

		if (cursor->GetCanHit() == true)
		{
			// ステージ3ボタンをクリックした
			select = 2;
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
				select = 3;
			}
		}
	}
}

void StageSelectScene::ButtonAnimation()
{
	switch (select)
	{
	case 0:
		if (change_wait_time < 8)
		{
			// ステージ1ボタンの画像切り替え
			stage1_img_num = change_wait_time / 4 + 1;
		}
		else
		{
			stage1_img_num = 1;
		}
		break;

	case 1:
		if (change_wait_time < 8)
		{
			// ステージ2ボタンの画像切り替え
			stage2_img_num = change_wait_time / 4 + 1;
		}
		else
		{
			stage2_img_num = 1;
		}
		break;

	case 2:
		if (change_wait_time < 8)
		{
			// ステージ3ボタンの画像切り替え
			stage3_img_num = change_wait_time / 4 + 1;
		}
		else
		{
			stage3_img_num = 1;
		}
		break;

	default:
		if (change_wait_time < 8)
		{
			// タイトルボタンの画像切り替え
			title_img_num = change_wait_time / 4 + 1;
		}
		else
		{
			title_img_num = 1;
		}
		break;
	}
}
