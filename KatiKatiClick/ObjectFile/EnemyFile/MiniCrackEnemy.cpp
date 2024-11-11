#include "MiniCrackEnemy.h"
#include "../../UtilityFile/Define.h"
#include "../../UtilityFile/ResourceManager.h"

MiniCrackEnemy::MiniCrackEnemy()
{
	hp = 10;
	speed = 1.5f;
	can_hit = false;
	object_type = ObjectType::enemy;
	shape = Shape::square;

	ResourceManager* rm = ResourceManager::GetInstance();
	int tmp;
	tmp = rm->GetSounds("Resource/Sounds/Click/hitenemy_c.mp3");
	se[0] = tmp;

	tmp = rm->GetSounds("Resource/Sounds/Click/hitenemy_c.mp3");
	se[1] = tmp;

}

MiniCrackEnemy::~MiniCrackEnemy()
{
}

void MiniCrackEnemy::Initialize()
{
}

void MiniCrackEnemy::Update()
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
			// 効果音の再生を止める
			StopSoundMem(se[0]);

			// 敵がつぶれるSE再生
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

void MiniCrackEnemy::Draw() const
{
}

void MiniCrackEnemy::HitReaction(ObjectBase* character)
{
}
