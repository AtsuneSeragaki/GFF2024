#include "UIGoal.h"
#include "DxLib.h"
#include "../../UtilityFile/Define.h"

UIGoal::UIGoal()
{
	goal_hp = 0;
}

UIGoal::~UIGoal()
{
}

void UIGoal::Update()
{
}

void UIGoal::Draw() const
{
	for (int i = 0; i < 3; i++)
	{
		
		DrawBox(LANE_WIDTH_HALF/2 + LANE_WIDTH * i, SCREEN_HEIGHT - GET_LANE_HEIGHT(2), LANE_WIDTH_HALF/2 + 50 + LANE_WIDTH * i, 20 + SCREEN_HEIGHT - GET_LANE_HEIGHT(2), 0xff0000, TRUE);
	}
	for (int i = 0; i < goal_hp; i++)
	{
		
		DrawBox(LANE_WIDTH_HALF/2 + LANE_WIDTH*i, SCREEN_HEIGHT - GET_LANE_HEIGHT(2), LANE_WIDTH_HALF/2 + 50 + LANE_WIDTH * i, 20 + SCREEN_HEIGHT - GET_LANE_HEIGHT(2), 0x00ff00, TRUE);
	}
}
