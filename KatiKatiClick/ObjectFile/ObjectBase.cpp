#include "ObjectBase.h"
#include <math.h>

ObjectBase::ObjectBase()
{
	location = { 0.0f };
	radius = 0.0f;
	can_hit = false;
	object_type = ObjectType::null;
	shape = Shape::null;
	can_delete = false;
	width = 0.0f;
	height = 0.0f;
	can_create_zone = false;
}

ObjectBase::~ObjectBase()
{

}

bool ObjectBase::HitCircle(Vector2D other_obj, float other_radius)
{
	float a = location.x - other_obj.x;
	float b = location.y - other_obj.y;
	float check_range = sqrtf(a * a + b * b);

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

bool ObjectBase::HitBox(Vector2D other_obj, float other_height, float other_width)
{
	//x座標の相手と自分の距離を絶対値で測る
	float distance_x = fabsf(location.x - other_obj.x);
	float distance_y = fabsf(location.y - other_obj.y);
	//幅をたした値を2で割る
	float width_size = (width + other_width) / 2.0f;
	float height_size = (height + other_height) / 2.0f;

	//サイズの和と距離を比較する
	if (distance_x < width_size && distance_y < height_size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ObjectBase::HitBoxCircle(ObjectBase* object)
{
	float box_left, box_right, box_top, box_bottom;
	float circle_x, circle_y;
	float rad;//半径
	bool hit_result = false;//当たったか

	//自分が円形だったら
	if (shape == Shape::circle)
	{
		circle_x = location.x;
		circle_y = location.y;
		rad = radius;

		box_left = object->GetLocation().x - object->GetWidth()/2;
		box_top = object->GetLocation().y - object->GetHeight()/2;
		box_right = object->GetLocation().x + object->GetWidth()/2;
		box_bottom = object->GetLocation().y + object->GetHeight()/2;
	}
	else
	{
		//自分が四角だったら
		box_left = location.x - width / 2;
		box_top = location.y - height / 2;
		box_right = location.x + width / 2;
		box_bottom = location.y + height / 2;

		circle_x = object->GetLocation().x;
		circle_y = object->GetLocation().y;
		rad = object->GetRadius();
	}


	//circleの端がボックスの上下左右に入っているか
	if ((circle_x > box_left - rad) &&
		(circle_x < box_right + rad) &&
		(circle_y > box_top - rad) &&
		(circle_y < box_bottom + rad))
	{
		hit_result = true;
		float r = rad * rad;//半径＊半径

		//circleのｘが左より小さかったら
		if (circle_x < box_left)
		{
			//左上の座標より上にいたら
			if (circle_y < box_top)
			{
				//左上の頂点との判定
				if ((DistanceSqrf(box_left, box_top, circle_x, circle_y)) >= r)
				{
					//二乗より大きいので当たってない
					hit_result = false;
				}
			}
			else
			{
				//circleのｘが左下の座標より下にいたら
				if (circle_y > box_bottom)
				{
					//左下の頂点との判定
					if (DistanceSqrf(box_left, box_bottom, circle_x, circle_y) >= r)
					{
						hit_result = false;
					}
				}
			}
		}
		else
		{
			//右
			if(circle_x > box_right)
			{
				//右上
				if (circle_y < box_top)
				{
					if ((DistanceSqrf(box_right, box_top, circle_x, circle_y)) >= r)
					{
						hit_result = false;
					}
				}
				else
				{
					//右下
					if (circle_y > box_bottom)
					{
						if (DistanceSqrf(box_right, box_bottom, circle_x, circle_y) >= r)
						{
							hit_result = false;
						}
					}
				}

			}
		}


	}
	return hit_result;
}

float ObjectBase::DistanceSqrf(float box_x, float box_y, float circle_x, float circle_y)
{
	float dx = circle_x - box_x;
	float dy = circle_y - box_y;

	return (dx * dx) + (dy * dy);
}

ObjectType ObjectBase::GetObjectType()
{
	return object_type;
}

Shape ObjectBase::GetShape()
{
	return shape;
}

bool ObjectBase::GetCanHit()
{
	return can_hit;
}

float ObjectBase::GetRadius()
{
	return radius;
}

float ObjectBase::GetWidth()
{
	return width;
}

float ObjectBase::GetHeight()
{
	return height;
}

bool ObjectBase::GetIsDelete()
{
	return can_delete;
}

const Vector2D& ObjectBase::GetLocation() const
{
	return location;
}

void ObjectBase::SetLocation(const Vector2D& location)
{
	this->location = location;
}

bool ObjectBase::GetCanCreateZone()
{
	return can_create_zone;
}
