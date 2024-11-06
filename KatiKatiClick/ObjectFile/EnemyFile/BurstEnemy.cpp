#include "BurstEnemy.h"
#include "../../UtilityFile/Define.h"
#include "../../UtilityFile/ResourceManager.h"

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
	state = State::move;

	ResourceManager* rm = ResourceManager::GetInstance();
	int tmp;
	tmp = rm->GetSounds("Resource/Sounds/Click/hitenemy_b.mp3");
	se[0] = tmp;

	tmp = rm->GetSounds("Resource/Sounds/Click/enemy_b.mp3");
	se[1] = tmp;
}

BurstEnemy::~BurstEnemy()
{
}

void BurstEnemy::Initialize()
{
}

void BurstEnemy::Update()
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
			// 効果音の再生を止める
			StopSoundMem(se[0]);

			// 敵が破裂するSE再生
			PlaySoundMem(se[1], DX_PLAYTYPE_BACK, TRUE);

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

		// 敵が押された時SE再生
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

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
		state = State::goal;
		speed = 3;
		break;
	default:
		break;
	}
}
