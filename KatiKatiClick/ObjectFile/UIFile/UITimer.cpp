#include "UITimer.h"

UITimer::UITimer()
{
	fps_count = 0;
	seconds = 60;
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
}

void UITimer::Draw() const
{
	DrawFormatString(20, 20, 0xcc0000, "timer : %d", seconds);
}

// 秒数の取得
int UITimer::GetSeconds() const
{
	return seconds;
}