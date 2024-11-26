#include "FrogEnemy.h"
#include "../../UtilityFile/Define.h"
#include "../../UtilityFile/ResourceManager.h"
#define _USE_MATH_DEFINES
#include <math.h>

FrogEnemy::FrogEnemy()
{
	location.x = 320.0f;
	location.y = 0.0f;
	hp = 20;
	width = 70.0f;
	height = 70.0f;
	speed = 1.5f;
	can_hit = false;
	object_type = ObjectType::enemy;
	shape = Shape::square;
	angle = 0;
	radian = 0.0f;
	result = 0.0f;

	img_cnt = 0;
	img_num = 0;
	old_location = { 0 };
	old_height = 0.0f;
	old_width = 0.0f;
	hit_damage = false;

	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp_img;

	//敵画像の読み込み
	tmp_img = rm->GetSoftImages("Resource/Images/Characters/Enemy/square.png");
	enemy_image.push_back(tmp_img[2]);
	//敵画像死ぬアニメーション読み込み
	tmp_img = rm->GetSoftImages("Resource/Images/Characters/Enemy/square_death.png", 4, 4, 1, 64, 32);
	//8~11
	for (int i = 8; i <= 11; i++)
	{
		enemy_image.push_back(tmp_img[i]);
	}

	int tmp;
	tmp = rm->GetSounds("Resource/Sounds/GameMain/Click/hitenemy_c.mp3");
	se[0] = tmp;

	face_num = 1;
}

FrogEnemy::~FrogEnemy()
{
}

void FrogEnemy::Initialize()
{
	/*ResourceManager* rm = ResourceManager::GetInstance();
	int tmp;
	tmp = rm->GetSounds("Resource/Sounds/Click/hitenemy_b.mp3");
	se[0] = tmp;

	tmp = rm->GetSounds("Resource/Sounds/Click/enemy_b.mp3");
	se[1] = tmp;*/
}

void FrogEnemy::Update()
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


		//sin動き
		angle += 2;
		if (angle > 360)
		{
			angle = 0;
		}


		if (angle < 25)
		{
		}
		else {
			shape_change_x = 5;
			shape_change_y = 5;
			face_num = 3;
		}


		radian = (float)angle * (float)M_PI / 180.0f;
		result = sinf(radian);
		if (result < -0.5)
		{
			shape_change_x = 0;
			face_num = 1;
		}
		location.y += result;



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


	if (hit_damage == true)
	{
		if (img_cnt++ > 2)
		{
			img_cnt = 0;
			img_num++;

			if (img_num > 4)
			{
				hit_damage = false;
			}
		}
	}

}

void FrogEnemy::Draw() const
{
	if (state == State::wait)
	{
		DrawExtendGraph((int)location.x - (int)width / 2, (int)location.y - (int)height / 4, (int)location.x + (int)width / 2, (int)location.y + (int)height / 2, enemy_image[change_img], TRUE);
	}
	else
	{
		int left_top_x = (int)location.x - (int)width / 2;
		int left_top_y = (int)location.y - (int)height / 2;
		int right_bottom_x = (int)location.x + (int)width / 2;
		int right_bottom_y = (int)location.y + (int)height / 2;
		DrawExtendGraph(left_top_x + shape_change_x, left_top_y - shape_change_y, right_bottom_x - shape_change_x, right_bottom_y, enemy_image[change_img], TRUE);
	}

	if (state != State::death) {
		DrawRotaGraph((int)location.x, (int)location.y + face_shift_y, face_exrate, 0, face_image[face_num], TRUE);
	}

	if (hit_damage == true)
	{
		DrawExtendGraph((int)old_location.x - (int)old_width / 2, (int)old_location.y - (int)old_height / 2, (int)old_location.x + (int)old_width / 2, (int)old_location.y + (int)old_height / 2, enemy_image[img_num], TRUE);
	}


}

void FrogEnemy::HitReaction(ObjectBase* character)
{
	if (hit_damage == false&&hp>=20)
	{
		old_location = location;
	}
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:
		// 敵が押された時SE再生
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

		if (hit_damage == false && hp >= 20)
		{
			hit_damage = true;
			old_width = width+10.0f;
			old_height = height+10.0f;

		}

		hp -= 10;
		if (hp >= 10)
		{
			width -= 20.0f;
			height -= 20.0f;
			face_exrate = 1.5;
			face_shift_y = 13;
		}
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
		if (hit_damage == false && hp >= 20)
		{
			hit_damage = true;
			old_width = width + 10.0f;
			old_height = height + 10.0f;
		}

		hp -= 10;
		width -= 20.0f;
		height -= 20.0f;


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
