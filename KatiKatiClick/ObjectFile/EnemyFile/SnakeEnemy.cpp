#include "SnakeEnemy.h"
#include "../../UtilityFile/Define.h"
#include "../../UtilityFile/ResourceManager.h"
#define _USE_MATH_DEFINES
#include <math.h>

SnakeEnemy::SnakeEnemy()
{
	enemy_color = 0x7F4DA6;
	location.x = 320.0f;
	location.y = 0.0f;
	hp = 10;
	width = 50.0f;
	height = 50.0f;
	speed = 1.5f;
	can_hit = false;
	object_type = ObjectType::enemy;
	shape = Shape::square;
	angle = 0;
	radian = 0.0f;
	result = 0.0f;

	face_num = 4;

	ResourceManager* rm = ResourceManager::GetInstance();

	std::vector<int> tmp_img;

	//敵画像の読み込み
	tmp_img = rm->GetSoftImages("Resource/Images/Characters/Enemy/square.png");
	enemy_image.push_back(tmp_img[1]);
	//敵画像死ぬアニメーション読み込み
	tmp_img = rm->GetSoftImages("Resource/Images/Characters/Enemy/square_death.png", 4, 4, 1, 64, 32);
	//4~7
	for (int i = 4; i <= 7; i++)
	{
		enemy_image.push_back(tmp_img[i]);
	}

	int tmp;
	tmp = rm->GetSounds("Resource/Sounds/GameMain/Click/hitenemy_c.mp3");
	se[0] = tmp;
}

SnakeEnemy::~SnakeEnemy()
{
}

void SnakeEnemy::Initialize()
{
	/*ResourceManager* rm = ResourceManager::GetInstance();
	int tmp;
	tmp = rm->GetSounds("Resource/Sounds/Click/hitenemy_b.mp3");
	se[0] = tmp;

	tmp = rm->GetSounds("Resource/Sounds/Click/enemy_b.mp3");
	se[1] = tmp;*/
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
		if (location.y > SCREEN_HEIGHT - GET_LANE_HEIGHT(2))
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

		if (count_img++ > 2)
		{
			count_img = 0;
			change_img++;

			if (change_img > 4)
			{
				//アニメーションが終わったら
				can_delete = true;
			}
		}
		break;
	default:
		break;
	}
}

void SnakeEnemy::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 2.0, 0, enemy_image[change_img], TRUE);
	if (state != State::death)
	{
		DrawRotaGraph((int)location.x, (int)location.y + face_shift_y, 2, 0, face_image[face_num], TRUE);
	}

}

void SnakeEnemy::HitReaction(ObjectBase* character)
{
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:
		// 敵が押された時SE再生
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

		hp -= 10;
		width -= 10.0f;
		height -= 10.0f;
		hit_cursor = true;
		create_damage_effect = true;
		break;
	case ObjectType::wall:
		can_hit = false;
		state = State::death;
		create_wall_effect = true;
		break;
	case ObjectType::circlezone:
		// 敵が押された時SE再生
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);
		hp -= 10;
		break;
	case ObjectType::attackskill:
		// 敵が押された時SE再生
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);
		hp -= 20;
		break;
	case ObjectType::slowdownskill:
		if (speed >= 1.5f)
		{
			speed -= 0.7f;
		}
		break;
	default:
		break;
	}
}
