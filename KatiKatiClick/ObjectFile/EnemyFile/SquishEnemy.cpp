#include "SquishEnemy.h"

SquishEnemy::SquishEnemy()
{
	location.x = 320.0f;
	location.y = 0.0f;
	hp = 30;
	radius = 30.0f;
	speed = 2.0f;
	can_hit = true;
	object_type = ObjectType::enemy;
}

SquishEnemy::~SquishEnemy()
{
}

void SquishEnemy::Initialize()
{
}

void SquishEnemy::Update()
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

void SquishEnemy::Draw() const
{
	DrawCircleAA(location.x, location.y, radius, 32, 0xffffff, TRUE);
	DrawFormatString((int)location.x, (int)location.y-40, 0xe9967a, "hp:%d", hp);
}

void SquishEnemy::HitReaction(ObjectBase* character)
{
	
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:
		hp -= 10;
		break;
	default:
		break;
	}
}
