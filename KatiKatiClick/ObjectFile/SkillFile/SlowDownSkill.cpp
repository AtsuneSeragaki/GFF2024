#include "SlowDownSkill.h"

#include "DxLib.h"

SlowDownSkill::SlowDownSkill()
{
	can_hit = true;
	object_type = ObjectType::slowdownskill;
	shape = Shape::square;
	can_delete = false;
	height = 100.0f;
	width = 100.0f;
	disp_flg = true;
}

SlowDownSkill::~SlowDownSkill()
{
}

void SlowDownSkill::Update()
{
	cnt++;
	if (cnt >= 300)
	{
		can_delete = true;
		cnt = 0;
	}
}

void SlowDownSkill::Initialize()
{
}

void SlowDownSkill::Draw() const
{
	DrawBoxAA(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, 0xffffff, TRUE);
}

void SlowDownSkill::Finalize()
{
}

void SlowDownSkill::HitReaction(ObjectBase* character)
{
}
