#include "UITimer.h"
#include "../../UtilityFile/ResourceManager.h"
#include "DxLib.h"

UITimer::UITimer()
{
	location.x = 25.0f;
	location.y = 590.0f;
	fps_count = 0;
	seconds = 60;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// タイマー画像の読み込み
	tmp = rm->GetImages("Resource/Images/Timer/Timer.png");
	timer_image.push_back(tmp[0]);

	// 数字画像を読み込む
	tmp = rm->GetImages("Resource/Images/Timer/Num.png", 10, 10, 1, 32, 32);
	for (int i = 0; i < 10; i++)
	{
		num_image.push_back(tmp[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		image_seconds_num[i] = 0;
	}
	image_minutes_num = 1;

	time_bar_length = 305.0f;
	now_time_bar_length = time_bar_length;

}

UITimer::~UITimer()
{

}

void UITimer::Update()
{
	// 秒数の計算
	if (fps_count < 60)
	{
		fps_count++;
	}
	else
	{
		if (seconds > 0)
		{
			seconds--;

			now_time_bar_length = (float)seconds * 5.0f;
		}

		fps_count = 0;
	}

	// 表示する数字画像を調べる
	CheckDisplayNumImage();
}

void UITimer::Draw() const
{
	// 描画ブレンドモードをアルファブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	// 白色四角
	DrawBoxAA(location.x - 20.0f, location.y - 20.0f, 355.0f, location.y + 20.0f, 0xffffff, TRUE);
	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// 黒色四角枠
	DrawBoxAA(location.x - 20.0f, location.y - 20.0f, 355.0f, location.y + 20.0f, 0x000000, FALSE, 3.0f);

	// バーの描画
	DrawBoxAA(50.0f, location.y - 20.0f, 50.0f + now_time_bar_length, location.y + 20.0f, 0xff0000, TRUE);
	DrawBoxAA(48.0f, location.y - 20.0f, 50.0f + time_bar_length, location.y + 20.0f, 0x000000, FALSE, 3.0f);

	// タイマー画像の描画
	DrawRotaGraphF(location.x + 3.0f, location.y, 1.0, 0.0, timer_image[0], TRUE);

	// 描画輝度のセット
	SetDrawBright(0, 0, 0);
	// 分の数字画像の描画
	DrawRotaGraphF(location.x + 35.0f, location.y, 1.0, 0.0, num_image[image_minutes_num], TRUE);
	// 描画輝度を元に戻す
	SetDrawBright(255, 255, 255);

	// コロンを黒色四角で描画
	DrawBoxAA(location.x + 50.0f, location.y - 10.0f, location.x + 55.0f, location.y - 5.0f, 0x000000, TRUE);
	DrawBoxAA(location.x + 50.0f, location.y + 10.0f, location.x + 55.0f, location.y + 5.0f, 0x000000, TRUE);

	for (int i = 0; i < 2; i++)
	{
		// 描画輝度のセット
		SetDrawBright(0, 0, 0);
		// 数字画像の描画
		DrawRotaGraphF((location.x + 90.0f) - i * 20, location.y, 1.0, 0.0, num_image[image_seconds_num[i]], TRUE);
		// 描画輝度を元に戻す
		SetDrawBright(255, 255, 255);
	}
}

// 秒数の取得
int UITimer::GetSeconds() const
{
	return seconds;
}

// 表示する数字画像を調べる
void UITimer::CheckDisplayNumImage()
{
	int tmp_seconds = seconds;

	for (int i = 0; i < 2; i++)
	{
		if (tmp_seconds < 60 && tmp_seconds > 0)
		{
			// 分の画像
			image_minutes_num = 0;

			// 秒の画像
			// 小さい位の数字から求める
			image_seconds_num[i] = tmp_seconds % 10;
			// 上の位
			tmp_seconds /= 10;
		}
		else
		{
			image_seconds_num[i] = 0;
		}
	}
}
