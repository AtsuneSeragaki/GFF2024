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

	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp_img;

	//敵画像の読み込み
	tmp_img = rm->GetSoftImages("Resource/Images/Characters/Enemy/square.png");
	enemy_image.push_back(tmp_img[2]);

	int tmp;
	tmp = rm->GetSounds("Resource/Sounds/Click/hitenemy_c.mp3");
	se[0] = tmp;
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
		radian = (float)angle * (float)M_PI / 180.0f;
		result = sinf(radian);
		location.y += result;

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

void FrogEnemy::Draw() const
{
	//DrawBox((int)location.x - (int)width / 2, (int)location.y - (int)height / 2, (int)location.x + (int)width / 2, (int)location.y + (int)height / 2, 0x3cb371, FALSE);
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
	//DrawRotaGraph((int)location.x, (int)location.y, 2.0, 0, enemy_image[0], 0);
	DrawExtendGraph((int)location.x - (int)width / 2, (int)location.y - (int)height / 2, (int)location.x + (int)width / 2, (int)location.y + (int)height / 2, enemy_image[0], TRUE);

}

void FrogEnemy::HitReaction(ObjectBase* character)
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
		break;
	case ObjectType::goal:
		can_hit = false;
		state = State::goal;
		speed = 3;
		break;
	case ObjectType::circlezone:
		// 敵が押された時SE再生
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);
		hp -= 10;
		width -= 10.0f;
		height -= 10.0f;
		break;
	case ObjectType::attackskill:
		hp -= 20;
		break;
	default:
		break;
	}
}
