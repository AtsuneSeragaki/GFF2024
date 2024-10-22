#include "AttackSkill.h"

#include "DxLib.h"

AttackSkill::AttackSkill()
{
	location.x = 0.0f;
	location.y = 0.0f;
	object_type = ObjectType::skill;
	radius = 10.0f;
	can_hit = true;
}

AttackSkill::~AttackSkill()
{
}

void AttackSkill::Update()
{
}

void AttackSkill::Draw() const
{
	DrawCircleAA(location.x, location.y, radius, 32, 0x00ffff, TRUE);
}

void AttackSkill::HitReaction(ObjectBase* character)
{
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:
		break;
	default:
		break;
	}
}