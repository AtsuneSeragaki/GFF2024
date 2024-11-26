#include "CrackEnemy.h"
#include "../../UtilityFile/Define.h"
#include "../../UtilityFile/ResourceManager.h"

CrackEnemy::CrackEnemy()
{
	enemy_color= 0x4C9CA6;

	hp = 10;
	width = 70.0f;
	height = 70.0f;
	speed = 1.5f;
	can_hit = false;
	object_type = ObjectType::enemy;
	shape = Shape::square;

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
	enemy_image.push_back(tmp_img[0]);
	//敵画像死ぬアニメーション読み込み
	tmp_img = rm->GetSoftImages("Resource/Images/Characters/Enemy/square_death.png",4,4,1,64,32);
	//0~3
	for (int i = 0; i <= 3; i++)
	{
		enemy_image.push_back(tmp_img[i]);
	}
	int tmp;
	tmp = rm->GetSounds("Resource/Sounds/GameMain/Click/hitenemy_c.mp3");
	se[0] = tmp;

	tmp = rm->GetSounds("Resource/Sounds/GameMain/Click/hitenemy_c.mp3");
	se[1] = tmp;
}

CrackEnemy::~CrackEnemy()
{
	
}

void CrackEnemy::Initialize()
{
}

void CrackEnemy::Update()
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
			//death_effect = new DeathEffect(location);
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

		//death_effect->Update();
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

void CrackEnemy::Draw() const
{


	//DrawCircleAA(location.x, location.y, 3, 32, 0x00ffff, TRUE);
	//DrawGraph(0, 300, handle2, TRUE);
	//DrawGraph(0,332, handle, TRUE);
	if (state == State::wait)
	{
		//DrawExtendGraph(int x1, int y1, int x2, int y2,int GrHandle, int TransFlag);
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
		DrawRotaGraph((int)location.x, (int)location.y + face_shift_y, 2, 0, face_image[face_num], TRUE);
	}
}

void CrackEnemy::HitReaction(ObjectBase* character)
{
	
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:

		if (hp > 0) {
			// 敵が押された時SE再生
			PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);
			create_damage_effect = true;//ダメージエフェクト生成
			hp -= 10;
			hit_cursor = true;
		}
		break;
	case ObjectType::wall:
		if (character->GetCanHit() != false)
		{
			can_hit = false;
			state = State::death;
			create_wall_effect = true;
		}
		break;
	case ObjectType::circlezone:
		// 敵が押された時SE再生
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);
		hp -= 10;
		
		break;
	case ObjectType::attackskill:
		// 敵がつぶれるSE再生
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
