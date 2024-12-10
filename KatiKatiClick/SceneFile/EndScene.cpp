#include "EndScene.h"

#include "../UtilityFile/ResourceManager.h"
#include "../UtilityFile/Define.h"
#include "DxLib.h"

EndScene::EndScene()
{
	crackenemy = new CrackEnemy();

	crackenemy->SetLocation(Vector2D(180.0f, 0.0f));

	crackenemy->SetSpeed(1.2f);

	cnt = 0;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	//画像読込
	std::vector<int> tmp_img;
	// 雲画像読み込み
	tmp_img = rm->GetImages("Resource/Images/Opening/cloud.png");
	cloud_img.push_back(tmp_img[0]);

	tmp_img = rm->GetImages("Resource/Images/End/text.png");
	end_img[0] = tmp_img[0];

	tmp_img = rm->GetImages("Resource/Images/End/fukidashi.png");
	end_img[1] = tmp_img[0];

	tmp_img = rm->GetImages("Resource/Images/Opening/character_hime_01_pink_brown.png");
	woman_img = tmp_img[0];

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

	if (cnt <= 320)
	{
		//crackenemy->Update();
	}

	if (anim_start == true)
	{
		if (cnt <= 410)
		{
			/*crackenemy->Update();*/
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
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x072246, TRUE);
	// 背景の雲
	//DrawRotaGraph(60, GET_LANE_HEIGHT(4), 2, 0, cloud_img[0], TRUE);
	//DrawRotaGraph(LANE_WIDTH * 3 - 60, GET_LANE_HEIGHT(2), 2, 0, cloud_img[0], TRUE);

	//crackenemy->Draw();

	//DrawGraph(60, 400, end_img, TRUE);

	/*DrawRotaGraph(180, 0 + 200 * 2, 0.5f, 0, woman_img, TRUE);
	DrawRotaGraph(140, 355, 0.1f, 0, end_img[1], TRUE);*/

	/*DrawExtendGraph(30, 250, 30 + 300, 250 + 122, end_img[1], TRUE);
	DrawExtendGraph(40, 260, 40 + 280, 260 + 30, end_img[0], TRUE);*/


	if (cnt >= 200)
	{
		DrawRotaGraph(185, 0 + 200 * 2, 0.5f, 0, woman_img, TRUE);
		DrawRotaGraph(142, 355, 0.1f, 0, end_img[1], TRUE);
	}
	else
	{
		DrawRotaGraph(185, 0 + cnt * 2, 0.5f, 0, woman_img, TRUE);
	}

	// 描画ブレンドモードをアルファブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, black_alpha);
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x000000, TRUE);
	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

AbstractScene* EndScene::Change()
{
	if (cnt == 417)
	{
		StopSoundMem(bgm);
		is_bgm_active = false;
		return nullptr;
	}

	return this;
}
