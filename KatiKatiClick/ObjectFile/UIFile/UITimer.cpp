#include "UITimer.h"
#include "../../UtilityFile/ResourceManager.h"
#include "DxLib.h"

UITimer::UITimer()
{
	fps_count = 0;
	seconds = 60;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// タイマー画像の読み込み
	tmp = rm->GetImages("Resource/Images/Timer/Timer.png");
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
	DrawBox(10, 10, 160, 60, 0x000000, TRUE);
	//DrawFormatString(20, 20, 0xffffff, "timer:");

	// タイマー画像の描画
	DrawRotaGraph(40, 35, 1.0, 0.0, timer_image[0], TRUE);
	// 分の数字画像の描画
	DrawRotaGraph(80, 35, 1.0, 0.0, num_image[image_minutes_num], TRUE);
	// コロン画像の描画
	DrawRotaGraph(100, 35, 1.0, 0.0, colon_image[0], TRUE);

	for (int i = 0; i < 2; i++)
	{
		// 数字画像の描画
		DrawRotaGraph(140 - i * 20, 35, 1.0, 0.0, num_image[image_seconds_num[i]], TRUE);
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
