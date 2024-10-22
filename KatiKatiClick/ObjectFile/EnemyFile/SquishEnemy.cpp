#include "SquishEnemy.h"

SquishEnemy::SquishEnemy()
{
	location.x = 320.0f;
	location.y = 0.0f;
	hp = 0;
	radius = 30.0f;
	speed = 2.0f;
	can_hit = true;
	object_type = ObjectType::enemy;
}

SquishEnemy::~SquishEnemy()
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
}

void SquishEnemy::Draw() const
{
	DrawCircleAA(location.x, location.y, radius, 32, 0xffffff, TRUE);
}

void SquishEnemy::HitReaction(ObjectBase* character)
{
	
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:
		break;
	default:
		break;
	}
}
