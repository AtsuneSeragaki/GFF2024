#include "UITimer.h"

UITimer::UITimer()
{
	fps_count = 0;
	seconds = 60;
}

UITimer::~UITimer()
{
	GetRefreshRate();
}

void UITimer::Update()
{

}

void UITimer::Draw() const
{
	DrawFormatString(20, 20, 0xff0000, "timer : %d", seconds);
}