#include "SlowDownSkill.h"

#include "DxLib.h"

SlowDownSkill::SlowDownSkill()
{
	location.x = 0.0f;
	location.y = 0.0f;
	object_type = ObjectType::skill;
	radius = 10.0f;
	can_hit = true;
}

SlowDownSkill::~SlowDownSkill()
{
}

void SlowDownSkill::Update()
{
}

void SlowDownSkill::Draw() const
{
	DrawCircleAA(location.x, location.y, radius, 32, 0x00ffff, TRUE);
}

void SlowDownSkill::HitReaction(ObjectBase* character)
{
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:
		break;
	default:
		break;
	}
}