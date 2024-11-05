#include "UITimer.h"
#include "../../UtilityFile/ResourceManager.h"
#include "DxLib.h"

UITimer::UITimer()
{
	fps_count = 0;
	seconds = 60;

	// 数字画像を読み込む
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/num.png", 10, 10, 1, 32, 32);
	for (int i = 0; i < 10; i++)
	{
		images_data.push_back(tmp[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		image_num[i] = 0;
	}
}

UITimer::~UITimer()
{

}

void UITimer::Update()
{
	if (fps_count < 60)
	{
		fps_count++;
	}
	else
	{
		seconds--;
		fps_count = 0;
	}

	if (seconds < 0)
	{
		seconds = 0;
	}

	int tmp_seconds = seconds;

	for (int i = 0; i < 2; i++)
	{
		if (tmp_seconds > 0)
		{
			// 小さい位の数字から求める
			image_num[i] = tmp_seconds % 10;
			// 上の位
			tmp_seconds /= 10;
		}
	}

	if (seconds <= 9)
	{
		image_num[1] = 0;
	}

}

void UITimer::Draw() const
{
	DrawBox(10, 10, 130, 50, 0x000000, TRUE);
	DrawFormatString(20, 20, 0xffffff, "timer:");

	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraph(110 - i * 20, 30, 1.0, 0.0, images_data[image_num[i]], TRUE);
	}

}

// 秒数の取得
int UITimer::GetSeconds() const
{
	return seconds;
}

int UITimer::GetSecondsImage() const
{
	return image_num[0];
}
