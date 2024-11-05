#include "SlowDownSkill.h"

#include "DxLib.h"

SlowDownSkill::SlowDownSkill()
{
	can_hit = true;
	location.x = 0.0f;
	location.y = 0.0f;
	object_type = ObjectType::slowdownskill;
	shape = Shape::square;
	can_delete = false;
	height = 30.0f;
	width = 15.0f;
	disp_flg = false;
}

SlowDownSkill::~SlowDownSkill()
{
}

void SlowDownSkill::Update()
{
}

void SlowDownSkill::Initialize()
{
}

void SlowDownSkill::Draw() const
{
	DrawBoxAA(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, 0xffffff, FALSE);
}

void SlowDownSkill::Finalize()
{
}