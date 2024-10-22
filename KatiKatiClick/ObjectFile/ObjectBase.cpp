#include "ObjectBase.h"
#include <math.h>

ObjectBase::ObjectBase()
{
	location = { 0.0f };
	radius = 0.0f;
	can_hit = false;
	object_type = ObjectType::null;
}

ObjectBase::~ObjectBase()
{
}

bool ObjectBase::HitCheck(Location other_obj, float other_radius)
{
	float a = location.x - other_obj.x;
	float b = location.y - other_obj.y;
	float check_range = sqrt(a * a + b * b);

	if (check_range <= radius + other_radius)
	{
		//当たってる
		return true;
	}
	else
	{
		//当たっていない
		return false;
	}

}

Location ObjectBase::GetLocation()
{
	return location;
}

ObjectType ObjectBase::GetObjectType()
{
	return object_type;
}

bool ObjectBase::GetCanHit()
{
	return can_hit;
}

float ObjectBase::GetRadius()
{
	return radius;
}
