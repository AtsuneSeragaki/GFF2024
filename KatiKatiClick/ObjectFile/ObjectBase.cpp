#include "ObjectBase.h"
#include <math.h>

ObjectBase::ObjectBase()
{
	location = { 0.0f };
	radius = 0.0f;
	can_hit = false;
	object_type = ObjectType::null;
	is_delete = false;
}

ObjectBase::~ObjectBase()
{

}

bool ObjectBase::HitCheck(Vector2D other_obj, float other_radius)
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

bool ObjectBase::GetIsDelete()
{
	return is_delete;
}

const Vector2D& ObjectBase::GetLocation() const
{
	return location;
}

void ObjectBase::SetLocation(const Vector2D& location)
{
	this->location = location;
}
