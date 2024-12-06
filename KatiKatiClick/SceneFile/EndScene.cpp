#include "EndScene.h"

#include "../UtilityFile/ResourceManager.h"
#include "../UtilityFile/Define.h"
#include "DxLib.h"

EndScene::EndScene()
{
	crackenemy = new CrackEnemy();

	crackenemy->SetLocation(Vector2D(180.0f, 50.0f));

	crackenemy->SetSpeed(0.5f);

	cnt = 0;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	//画像読込
	std::vector<int> tmp_img;
	// 雲画像読み込み
	tmp_img = rm->GetImages("Resource/Images/Opening/cloud.png");
	cloud_img.push_back(tmp_img[0]);

	tmp_img = rm->GetImages("Resource/Images/End/end.png");
	end_img = tmp_img[0];

	// 音データ読み込み
	int tmp_bgm;
	tmp_bgm = rm->GetSounds("Resource/Sounds/End/bgm.mp3");
	bgm = tmp_bgm;

	is_bgm_active = false;

	// 音量変更
	ChangeVolumeSoundMem(190, bgm);

	anim_start = false;
	black_alpha = 255;
}

EndScene::~EndScene()
{
	delete crackenemy;
}

void EndScene::Update()
{
	if (is_bgm_active == false)
	{
		is_bgm_active = true;
		// BGM再生
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);
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
		if (cnt <= 410)
		{
			crackenemy->Update();
		}

		cnt++;
	}
	else
	{
		if (black_alpha <= 150)
		{
			anim_start = true;
		}
	}

	
}

void EndScene::Draw() const
{
	// 背景色（水色）
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x686f82, TRUE);
	// 背景の雲
	//DrawRotaGraph(60, GET_LANE_HEIGHT(4), 2, 0, cloud_img[0], TRUE);
	//DrawRotaGraph(LANE_WIDTH * 3 - 60, GET_LANE_HEIGHT(2), 2, 0, cloud_img[0], TRUE);

	crackenemy->Draw();

	//DrawGraph(60, 400, end_img, TRUE);

	if (cnt <= 350)
	{
		//DrawString(85, 750 - cnt, "Thank you for playing!", 0x000000);
		DrawGraph(60, 750 - cnt, end_img, TRUE);
	}
	else
	{
		//DrawString(85, 400, "Thank you for playing!", 0x000000);
		DrawGraph(60, 400, end_img, TRUE);
	}

	// 描画ブレンドモードをアルファブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, black_alpha);
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x000000, TRUE);
	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

AbstractScene* EndScene::Change()
{
	if (cnt == 420)
	{
		StopSoundMem(bgm);
		is_bgm_active = false;
		return nullptr;
	}

	return this;
}
