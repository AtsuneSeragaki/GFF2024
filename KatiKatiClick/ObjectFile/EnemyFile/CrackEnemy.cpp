#include "CrackEnemy.h"

CrackEnemy::CrackEnemy()
{
	location.x = 320.0f;
	location.y = 0.0f;
	hp = 30;
	width = 60.0f;
	height = 60.0f;
	speed = 2.0f;
	can_hit = true;
	object_type = ObjectType::enemy;
	shape = Shape::square;
}

CrackEnemy::~CrackEnemy()
{
}

void CrackEnemy::Initialize()
{
}

void CrackEnemy::Update()
{
	if (location.y < 720)
	{
		location.y += speed;
	}
	else {
		location.y = 0.0f;
	}
	
	//hpが0以下になったら消す
	if (hp <= 0)
	{
		can_delete = true;
	}
}

void CrackEnemy::Draw() const
{

	DrawBox((int)location.x - (int)width / 2, (int)location.y - (int)height / 2, (int)location.x + (int)width / 2, (int)location.y + (int)height / 2, 0xffffff, TRUE);
	DrawFormatString((int)location.x, (int)location.y-40, 0xe9967a, "hp:%d", hp);
}

void CrackEnemy::HitReaction(ObjectBase* character)
{
	
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:
		hp -= 10;
		hit_cursor = true;
		break;
	default:
		break;
	}
}
