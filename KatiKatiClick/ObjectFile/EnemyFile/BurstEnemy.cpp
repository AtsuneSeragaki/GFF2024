#include "BurstEnemy.h"
#include "../../UtilityFile/Define.h"
#include "../../UtilityFile/ResourceManager.h"

BurstEnemy::BurstEnemy()
{
	enemy_color = 0x0095d9;
	location.x =0.0f;
	location.y = 0.0f;
	hp = 30;
	radius = 20.0f;
	default_speed = 1.0f;
	speed = default_speed;
	angle = 0;
	radian = 0.0f;
	result = 0.0f;
	can_hit = true;
	object_type = ObjectType::enemy;
	shape = Shape::circle;
	state = State::wait;
	hit_slowdown_skill = false;

	hit_attackskill = false;

	ResourceManager* rm = ResourceManager::GetInstance();
	int tmp;
	tmp = rm->GetSounds("Resource/Sounds/GameMain/Click/hitenemy_b.mp3");
	se[0] = tmp;

	tmp = rm->GetSounds("Resource/Sounds/GameMain/Click/enemy_b.mp3");
	se[1] = tmp;

	std::vector<int> tmp_img;
	tmp_img = rm->GetImages("Resource/Images/Characters/Enemy/Burst.png",4,4,1,32,32);
	for (int i = 0; i < 4; i++)
	{
		enemy_image.push_back(tmp_img[i]);
	}

	death_cnt = 2;
}

BurstEnemy::~BurstEnemy()
{
}

void BurstEnemy::Initialize()
{
	/*ResourceManager* rm = ResourceManager::GetInstance();
	int tmp;
	tmp = rm->GetSounds("Resource/Sounds/Click/hitenemy_b.mp3");
	se[0] = tmp;

	tmp = rm->GetSounds("Resource/Sounds/Click/enemy_b.mp3");
	se[1] = tmp;*/
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


		//cos動き
		angle += 2;
		if (angle > 360)
		{
			angle = 0;
		}
		radian = (float)angle * (float)M_PI / 180.0f;
		result = cosf(radian);
		location.x += result;


		//UIより上か下だったら当たり判定をしない
		if ( location.y > SCREEN_HEIGHT - GET_LANE_HEIGHT(2))
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
			can_hit = false;

			state = State::death;
		}

		break;
	case State::goal:
		if (wait_time-- < 0)
		{
			if (location.y < 720)
			{
				location.y += speed;
			}
			else {
				//720より下に行ったら削除
				can_delete = true;
			}
		}
		break;
	case State::death:
		if (hit_attackskill == false) {
			can_create_zone = true;
		}
		if (death_cnt-- < 0)
		{
			can_delete = true;
		}
		can_hit = false;
		break;
	default:
		break;
	}


}

void BurstEnemy::Draw() const
{
	

	//int ex_rate = radius / 10;
	//DrawRotaGraph(location.x, location.y, (double)ex_rate, 0, enemy_image[chenge_img], TRUE);

	int left_top_x = (int)location.x - (int)radius;
	int left_top_y = (int)location.y - (int)radius;
	int right_bottom_x = (int)location.x + (int)radius;
	int right_bottom_y = (int)location.y + (int)radius;
	DrawExtendGraph(left_top_x + shape_change_x, left_top_y - shape_change_y, right_bottom_x - shape_change_x, right_bottom_y, enemy_image[change_img], TRUE);

	//当たり判定表示用
	//DrawCircleAA(location.x, location.y, radius, 32, 0xffffff, FALSE);

	//DrawFormatString((int)location.x, (int)location.y - 5, 0xe9967a, "flg:%d", hit_slowdown_skill);
	//DrawFormatString((int)location.x, (int)location.y + 5, 0xe9967a, "speed:%f", speed);

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
		radius += 15.0f;
		change_img++;
		hit_cursor = true;
		create_damage_effect = true;
		break;
	case ObjectType::wall:
		if (character->GetCanHit() != false)
		{
			can_hit = false;
			state = State::death;
			create_wall_effect = true;
		}
		break;
	case ObjectType::attackskill:
		hp -= 30;
		create_damage_effect = true;
		state = State::death;
		change_img=3;
		radius += 30.0f;
		hit_attackskill = true;
		break;
	case ObjectType::slowdownskill:
		if (speed >= default_speed)
		{
			speed -= 0.7f;
		}
		hit_slowdown_skill = true;
		break;
	default:
		break;
	}
}
