#include "AttackSKill.h"

#include "DxLib.h"

AttackSkill::AttackSkill()
{
	can_hit = true;
	object_type = ObjectType::attackskill;
	shape = Shape::square;
	can_delete = false;
	height = 100.0f;
	width = 100.0f;
	disp_flg = true;
}

AttackSkill::~AttackSkill()
{
}

void AttackSkill::Update()
{
	cnt++;
	if (cnt >= 60)
	{
		can_delete = true;
		cnt = 0;
	}
}

void AttackSkill::Initialize()
{
}

void AttackSkill::Draw() const
{
	DrawBoxAA(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, 0xffffff,FALSE);
}

void AttackSkill::Finalize()
{
}

void AttackSkill::HitReaction(ObjectBase* character)
{
}
