#include "SnakeEnemy.h"
#include "../../UtilityFile/Define.h"
#define _USE_MATH_DEFINES
#include <math.h>

SnakeEnemy::SnakeEnemy()
{
	location.x = 320.0f;
	location.y = 0.0f;
	hp = 30;
	width = 70.0f;
	height = 70.0f;
	speed = 1.5f;
	can_hit = false;
	object_type = ObjectType::enemy;
	shape = Shape::square;
	angle = 0;
	radian = 0.0f;
	result = 0.0f;
}

SnakeEnemy::~SnakeEnemy()
{
}

void SnakeEnemy::Initialize()
{
}

void SnakeEnemy::Update()
{
	switch (state)
	{
	case State::wait:

		if (wait_time-- < 0)
		{
			state = State::move;
		}

		break;
	case State::move:
		location.y += speed;
		
		//cos動き
		angle+=2;
		if (angle > 360)
		{
			angle = 0;
		}
		radian = (float)angle * (float)M_PI / 180.0f;
		result = cosf(radian);
		location.x += result;

		//UIより上か下だったら当たり判定をしない
		if (location.y < ONE_LANE_HEIGHT)
		{
			can_hit = false;
		}
		else
		{
			can_hit = true;
		}

		//hpが0以下になったら消す
		if (hp <= 0)
		{
			// 敵がつぶれるSE再生
			state = State::death;
		}

		break;
	case State::goal:
		if (location.y < 720)
		{
			location.y += speed;
		}
		else {
			//720より下に行ったら削除
			can_delete = true;
		}

		break;
	case State::death:
		can_delete = true;
		break;
	default:
		break;
	}
}

void SnakeEnemy::Draw() const
{
	DrawBox((int)location.x - (int)width / 2, (int)location.y - (int)height / 2, (int)location.x + (int)width / 2, (int)location.y + (int)height / 2, 0x9932cc, TRUE);
	DrawFormatString((int)location.x, (int)location.y - 40, 0xe9967a, "hp:%d", hp);

	if (can_hit == true)
	{
		DrawFormatString((int)location.x, (int)location.y - 20, 0xe9967a, "true");
	}
	else
	{
		DrawFormatString((int)location.x, (int)location.y - 20, 0xe9967a, "false");
	}


	DrawCircleAA(location.x, location.y, 3, 32, 0x00ffff, TRUE);
}

void SnakeEnemy::HitReaction(ObjectBase* character)
{
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:
		// 敵が押された時SE再生
		hp -= 10;
		width -= 10.0f;
		height -= 10.0f;
		hit_cursor = true;
		break;
	case ObjectType::goal:
		can_hit = false;
		state = State::goal;
		speed = 3;
		break;
	default:
		break;
	}
}
