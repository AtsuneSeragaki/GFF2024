#include "BurstEnemy.h"
#include "../../UtilityFile/Define.h"

BurstEnemy::BurstEnemy()
{
	location.x = 400.0f;
	location.y = 0.0f;
	hp = 60;
	radius = 10.0f;
	speed = 1.0f;
	can_hit = true;
	object_type = ObjectType::enemy;
	shape = Shape::circle;

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
		//720より下に行ったら削除
		can_delete = true;
	}

	//UIより上か下だったら当たり判定をしない
	if (location.y < ONE_LANE_HEIGHT || location.y > SCREEN_HEIGHT - GET_LANE_HEIGHT(2))
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
		can_delete = true;
	}
}

void BurstEnemy::Draw() const
{
	DrawCircleAA(location.x, location.y, radius, 32, 0xffffff, TRUE);
	DrawFormatString((int)location.x, (int)location.y, 0xe9967a, "hp:%d", hp);

	if (can_hit == true)
	{
		DrawFormatString((int)location.x, (int)location.y-20, 0xe9967a, "true");
	}
	else
	{
		DrawFormatString((int)location.x, (int)location.y - 20, 0xe9967a, "false");
	}
}

void BurstEnemy::HitReaction(ObjectBase* character)
{
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:
		//カーソルに当たったらスピードを下げ半径を大きくする
		hp -= 10;
		if (speed > 0.3f) {
			speed -= 0.3f;
		}
		radius += 5.0f;
		hit_cursor = true;
		break;
	case ObjectType::goal:
		can_hit = false;
		break;
	default:
		break;
	}
}
