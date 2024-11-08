#include "HitCircleZone.h"
#include "DxLib.h"

HitCircleZone::HitCircleZone()
{
	can_hit = true;
	object_type = ObjectType::circlezone;
	shape = Shape::circle;
	count = 0;
}

HitCircleZone::~HitCircleZone()
{
}

void HitCircleZone::Initialize()
{
}

void HitCircleZone::Update()
{
	if (count++ > 1)
	{
		can_delete = true;
	}
}

void HitCircleZone::Draw() const
{
	DrawCircleAA(location.x, location.y, radius, 32, 0xff0000, TRUE);
}

void HitCircleZone::HitReaction(ObjectBase* character)
{
	can_hit = false;
	can_delete = true;
}
