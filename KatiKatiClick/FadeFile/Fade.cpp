#include "Fade.h"
#include "DxLib.h"
#include "../UtilityFile/ResourceManager.h"
#include "../UtilityFile/Define.h"

Fade::Fade()
{
	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();

	//画像読込
	std::vector<int> tmp_img;

	// 雲画像読み込み
	tmp_img = rm->GetImages("Resource/Images/Explanation/enemy.png");
	enm_img.push_back(tmp_img[0]);

	int tmp_se;
	tmp_se = rm->GetSounds("Resource/Sounds/Transition/trans.mp3");
	fade_se = tmp_se;

	// 音量変更
	ChangeVolumeSoundMem(180, fade_se);

	bool fade_in;//trueだったらフェードイン

	upperbox_down_y = -110.0f;
	bottombox_up_y = (float)SCREEN_HEIGHT+110.0f;
	rightbox_shiftx = (float)SCREEN_WIDTH+230.0f;
	leftbox_shiftx = -230.0f;

	enm_display_flg = true;
	fade_end = false;
	wait_time = 30;
}

Fade::~Fade()
{
	DeleteMaskScreen();
}

void Fade::Update()
{
	if (upperbox_down_y == -110.0f)
	{
		PlaySoundMem(fade_se, DX_PLAYTYPE_BACK, TRUE);
	}

	//400/10->40fぐらいでつく
	upperbox_down_y += 15.0f;
	bottombox_up_y -= 15.0f;
	//180->
	rightbox_shiftx -= 12.0f;
	leftbox_shiftx += 12.0f;

	if (leftbox_shiftx > 150)
	{
		enm_display_flg = false;
	}

	if (leftbox_shiftx > SCREEN_WIDTH / 2)
	{
		wait_time--;
	}

	if (leftbox_shiftx > SCREEN_WIDTH / 2 && wait_time<0)
	{
		fade_end = true;
	}
}

void Fade::Draw() const
{
	//upper
	DrawBoxAA(0, 0, SCREEN_WIDTH, upperbox_down_y, 0x000000, TRUE);

	//bottom
	DrawBoxAA(0, bottombox_up_y, SCREEN_WIDTH, SCREEN_HEIGHT, 0x000000, TRUE);

	//right
	DrawBoxAA(rightbox_shiftx, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x000000, TRUE);

	//bottom
	DrawBoxAA(0,0,leftbox_shiftx, SCREEN_HEIGHT, 0x000000, TRUE);
	if (enm_display_flg == true) {
		//エネミーの透過画像表示
		DrawExtendGraph(leftbox_shiftx, upperbox_down_y, rightbox_shiftx, bottombox_up_y, enm_img[0], TRUE);
	}
}
