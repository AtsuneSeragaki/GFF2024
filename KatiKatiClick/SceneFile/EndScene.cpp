#include "EndScene.h"

#include "../UtilityFile/ResourceManager.h"
#include "../UtilityFile/Define.h"
#include "DxLib.h"

EndScene::EndScene()
{
	crackenemy = new CrackEnemy();

	crackenemy->SetLocation(Vector2D(70.0f, 0.0f));

	crackenemy->SetSpeed(0.5f);

	cnt = 0;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	//画像読込
	std::vector<int> tmp_img;
	// 雲画像読み込み
	tmp_img = rm->GetImages("Resource/Images/Opening/cloud.png");
	cloud_img.push_back(tmp_img[0]);

	// 音データ読み込み
	int tmp_bgm;
	tmp_bgm = rm->GetSounds("Resource/Sounds/End/bgm.mp3");
	bgm = tmp_bgm;

	is_bgm_active = false;

	// 音量変更
	ChangeVolumeSoundMem(190, bgm);
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

	crackenemy->Update();

	cnt++;
}

void EndScene::Draw() const
{
	// 背景色（水色）
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xbdf4ff, TRUE);
	// 背景の雲
	//DrawRotaGraph(60, GET_LANE_HEIGHT(4), 2, 0, cloud_img[0], TRUE);
	//DrawRotaGraph(LANE_WIDTH * 3 - 60, GET_LANE_HEIGHT(2), 2, 0, cloud_img[0], TRUE);

	crackenemy->Draw();

	if (cnt <= 350)
	{
		DrawString(85, 750 - cnt, "Thank you for playing!", 0x000000);
	}
	else
	{
		DrawString(85, 400, "Thank you for playing!", 0x000000);
	}
}

AbstractScene* EndScene::Change()
{
	if (cnt == 430)
	{
		StopSoundMem(bgm);
		is_bgm_active = false;
		return nullptr;
	}

	return this;
}
