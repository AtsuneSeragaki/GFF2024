#include "CrackEnemy.h"
#include "../../UtilityFile/Define.h"

CrackEnemy::CrackEnemy()
{
	location.x = 320.0f;
	location.y = 0.0f;
	hp = 30;
	width = 70.0f;
	height = 70.0f;
	speed = 1.5f;
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

void CrackEnemy::Draw() const
{

	DrawBox((int)location.x - (int)width / 2, (int)location.y - (int)height / 2, (int)location.x + (int)width / 2, (int)location.y + (int)height / 2, 0xffffff, TRUE);
	DrawFormatString((int)location.x, (int)location.y-40, 0xe9967a, "hp:%d", hp);

	if (can_hit == true)
	{
		DrawFormatString((int)location.x, (int)location.y - 20, 0xe9967a, "true");
	}
	else
	{
		DrawFormatString((int)location.x, (int)location.y - 20, 0xe9967a, "false");
	}
}

void CrackEnemy::HitReaction(ObjectBase* character)
{
	
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:
		hp -= 10;
		width -= 10.0f;
		height -= 10.0f;
		hit_cursor = true;
		break;
	default:
		break;
	}
}
