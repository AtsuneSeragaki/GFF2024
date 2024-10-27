#include "BurstEnemy.h"

BurstEnemy::BurstEnemy()
{
	location.x = 400.0f;
	location.y = 0.0f;
	hp = 70;
	radius = 10.0f;
	speed = 2.0f;
	can_hit = true;
	object_type = ObjectType::enemy;

}

BurstEnemy::~BurstEnemy()
{
}

void BurstEnemy::Initialize()
{
}

void BurstEnemy::Update()
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

void BurstEnemy::Draw() const
{
	DrawCircleAA(location.x, location.y, radius, 32, 0xffffff, TRUE);
	DrawFormatString((int)location.x, (int)location.y, 0xe9967a, "hp:%d", hp);
}

void BurstEnemy::HitReaction(ObjectBase* character)
{
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:
		hp -= 10;
		hit_cursor = true;
		radius += 10.0f;
		break;
	default:
		break;
	}
}
