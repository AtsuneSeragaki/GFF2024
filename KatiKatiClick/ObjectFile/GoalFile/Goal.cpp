#include "Goal.h"
#include "DxLib.h"
#include "../../UtilityFile/Define.h"

Goal::Goal()
{
	location.x = (float)SCREEN_WIDTH / 2.0f;
	width = (float)SCREEN_WIDTH;
	height = (float)ONE_LANE_HEIGHT/10.0f;
	shape = Shape::square;
	object_type = ObjectType::goal;
	goal_cnt = 3;
	can_hit = true;
}

Goal::~Goal()
{
}

void Goal::Initialize()
{
}

void Goal::Update()
{
}

void Goal::Draw() const
{
	DrawBox((int)location.x - (int)width / 2, (int)location.y - (int)height / 2, (int)location.x + (int)width / 2, (int)location.y + (int)height / 2, 0xffff00, TRUE);
	DrawFormatString((int)location.x, (int)location.y, 0x000000, "goal_HP:%d", goal_cnt);

	//ゴール仮幅
	//DrawBox(0, SCREEN_HEIGHT - GET_LANE_HEIGHT(2), SCREEN_WIDTH, SCREEN_HEIGHT - GET_LANE_HEIGHT(2) + 5, 0xffff00, TRUE);

}

void Goal::HitReaction(ObjectBase* character)
{
	if (character->GetObjectType() == ObjectType::enemy)
	{
		goal_cnt--;
	}
}
