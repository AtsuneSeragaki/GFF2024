#include "SplitEnemy.h"
#include "../../UtilityFile/Define.h"
#include "../../UtilityFile/ResourceManager.h"

SplitEnemy::SplitEnemy()
{
	enemy_color = 0xCE6161;
	location.x = 320.0f;
	location.y = 0.0f;
	hp = 20;
	width = 70.0f;
	height = 70.0f;
	default_speed = 1.0f;
	speed = default_speed;
	can_hit = false;
	object_type = ObjectType::enemy;
	shape = Shape::square;
	hit_slowdown_skill = false;
	check_hp = false;

	count_img = 0;
	change_img = 0;
	shape_change_x = 0;
	shape_change_y = 0;
	shape_change_cnt = 0;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp_img;

	//敵画像の読み込み
	tmp_img = rm->GetSoftImages("Resource/Images/Characters/Enemy/square.png");
	enemy_image.push_back(tmp_img[3]);
	//敵画像死ぬアニメーション読み込み
	tmp_img = rm->GetSoftImages("Resource/Images/Characters/Enemy/square_death.png", 4, 4, 1, 64, 32);
	//12~15
	for (int i = 12; i <= 15; i++)
	{
		enemy_image.push_back(tmp_img[i]);
	}
	int tmp;
	tmp = rm->GetSounds("Resource/Sounds/GameMain/Click/hitenemy_c.mp3");
	se[0] = tmp;

	tmp = rm->GetSounds("Resource/Sounds/GameMain/Click/hitenemy_c.mp3");
	se[1] = tmp;

}

SplitEnemy::~SplitEnemy()
{
}

void SplitEnemy::Initialize()
{
}

void SplitEnemy::Update()
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

		//５カウントずつ幅の大きさを変えて歩いているように
		MoveShapeChange();


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
			if (location.y < SCREEN_HEIGHT + height)
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
			else if (change_img > 3)
			{
				if (check_hp == true)
				{
					check_hp = false;
					can_create_mini = true;
				}
			}
		}

		break;
	default:
		break;
	}

}

void SplitEnemy::Draw() const
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

	if (state != State::death)
	{
		DrawRotaGraph((int)location.x, (int)location.y + face_shift_y, face_exrate, 0, face_image[face_num], TRUE);
	}

	//DrawFormatString((int)location.x, (int)location.y - 5, 0xe9967a, "flg:%d", hit_slowdown_skill);
	//DrawFormatString((int)location.x, (int)location.y + 5, 0xe9967a, "speed:%f", speed);

}

void SplitEnemy::HitReaction(ObjectBase* character)
{
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:

		// 敵が押された時SE再生
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

		if (hp >= 20)
		{
			check_hp = true;
			width -= 30.0f;
			height -= 30.0f;
		}
		hp -= 20;
		hit_cursor = true;
		create_damage_effect = true;//ダメージエフェクト生成
		break;
	case ObjectType::wall:
		if (character->GetCanHit() != false)
		{
			can_hit = false;
			state = State::death;
			create_wall_effect = true;//壁にぶつかったときのエフェクト生成
		}
		break;
	case ObjectType::circlezone:
		// 敵が押された時SE再生
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

		if (hp >= 10) {
			width -= 10;
			height -= 10;
			hp -= 10;
			face_shift_y -= 5;
		}
		create_damage_effect = true;//ダメージエフェクト生成

		break;
	case ObjectType::attackskill:
		// 敵が押された時SE再生
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);
		hp -= 20;
		create_damage_effect = true;//ダメージエフェクト生成

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
