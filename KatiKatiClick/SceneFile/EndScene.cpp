#include "EndScene.h"

#include "../UtilityFile/ResourceManager.h"
#include "DxLib.h"

EndScene::EndScene()
{
	cnt = 0;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();

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
}

void EndScene::Update()
{
	if (is_bgm_active == false)
	{
		is_bgm_active = true;
		// BGM再生
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);
	}

	cnt++;
}

void EndScene::Draw() const
{
	if (cnt <= 350)
	{
		DrawString(85, 750 - cnt, "Thank you for playing!", 0xffffff);
	}
	else
	{
		DrawString(85, 400, "Thank you for playing!", 0xffffff);
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
