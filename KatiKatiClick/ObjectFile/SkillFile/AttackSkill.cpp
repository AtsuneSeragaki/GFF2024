#include "AttackSKill.h"

#include "DxLib.h"

AttackSkill::AttackSkill()
{
	can_hit = true;
	location.x = 0.0f;
	location.y = 0.0f;
	object_type = ObjectType::attackskill;
	shape = Shape::square;
	can_delete = false;
	height = 30.0f;
	width = 15.0f;
	disp_flg = false;
}

AttackSkill::~AttackSkill()
{
}

void AttackSkill::Update()
{
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