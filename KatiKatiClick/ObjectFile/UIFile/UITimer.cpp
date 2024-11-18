#include "UITimer.h"
#include "../../UtilityFile/ResourceManager.h"
#include "DxLib.h"

UITimer::UITimer()
{
	location.x = 30.0f;
	location.y = 590.0f;
	fps_count = 0;
	seconds = 60;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// タイマー画像の読み込み
	tmp = rm->GetImages("Resource/Images/Timer/Timer03.png");
	timer_image.push_back(tmp[0]);

	// コロン画像の読み込み
	tmp = rm->GetImages("Resource/Images/Timer/Colon.png");
	colon_image.push_back(tmp[0]);

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
		}

		fps_count = 0;
	}

	// 表示する数字画像を調べる
	CheckDisplayNumImage();
}

void UITimer::Draw() const
{
	//DrawBox(10, 10, 150, 60, 0xfff4b3, TRUE);
	//DrawBoxAA(10.0f, 10.0f, 150.0f, 60.0f, 0x000000, FALSE, 2.0f);

	// タイマー画像の描画
	DrawRotaGraphF(location.x, location.y, 2.5, 0.0, timer_image[0], TRUE);
	// 分の数字画像の描画
	DrawRotaGraphF(location.x + 35.0f, location.y, 1.0, 0.0, num_image[image_minutes_num], TRUE);
	// コロン画像の描画
	DrawRotaGraphF(location.x + 50.0f, location.y, 1.0, 0.0, colon_image[0], TRUE);

	for (int i = 0; i < 2; i++)
	{
		// 数字画像の描画
		DrawRotaGraphF((location.x + 90.0f) - i * 20, location.y, 1.0, 0.0, num_image[image_seconds_num[i]], TRUE);
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
