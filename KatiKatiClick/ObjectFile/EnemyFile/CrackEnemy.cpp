#include "CrackEnemy.h"
#include "../../UtilityFile/Define.h"
#include "../../UtilityFile/ResourceManager.h"

CrackEnemy::CrackEnemy()
{

	hp = 10;
	width = 70.0f;
	height = 70.0f;
	speed = 1.5f;
	can_hit = false;
	object_type = ObjectType::enemy;
	shape = Shape::square;

	count_img = 0;
	chenge_img = 0;
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
	tmp = rm->GetSounds("Resource/Sounds/Click/hitenemy_c.mp3");
	se[0] = tmp;

	tmp = rm->GetSounds("Resource/Sounds/Click/hitenemy_c.mp3");
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
		if (shape_change_cnt++ > 5)
		{
			shape_change_cnt = 0;
			if (shape_change_x == 0)
			{
				shape_change_x = 3;
				shape_change_y = 2;
			}
			else if(shape_change_y==2)
			{
				shape_change_y = 5;
			}
			else
			{
				shape_change_x = 0;
				shape_change_y = 0;
			}
		}

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

		//death_effect->Update();
		if (count_img++ > 2)
		{
			count_img = 0;
			chenge_img++;

			if (chenge_img > 4)
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

	DrawFormatString((int)location.x, (int)location.y-40, 0xe9967a, "hp:%d", hp);
	if (can_hit == true)
	{
		DrawFormatString((int)location.x, (int)location.y - 20, 0xe9967a, "true");
	}
	else
	{
		DrawFormatString((int)location.x, (int)location.y - 20, 0xe9967a, "false");
	}
	/*
	//int r, g, b, a;
	// //パレットの一覧を描画
	//for (int i = 0; i < 8; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//	{
	//		// パレットの色を取得する
	//		GetPaletteSoftImage(handle, j + i * 16, &r, &g, &b, 0);

	//		// DrawBox を使って描画
	//		DrawBox(j * 16, i * 16+200, j * 16 + 16, i * 16 + 16+200, GetColor(r, g, b), TRUE);
	//	}
	//}

	//for (int i = 0; i < image_height; i++)
	//{
	//	for (int j = 0; j < image_width; j++)
	//	{
	//		//1ドットの色を取得
	//		GetPixelSoftImage(handle, j, i, &r, &g, &b, &a);
	//		//DrawBoxで描画
	//		DrawBox((j * 3)+ (int)location.x - (int)width / 2, (i * 3)+ (int)location.y - (int)height / 2, (j * 3 + 3)+ (int)location.x + (int)width / 2, (i * 3 + 3)+ (int)location.y + (int)height / 2, GetColor(r, g, b), TRUE);
	//	}
	//}
	*/
	
	//DrawSoftImage(location.x, location.y, handle);

	//DrawCircleAA(location.x, location.y, 3, 32, 0x00ffff, TRUE);
	//DrawGraph(0, 300, handle2, TRUE);
	//DrawGraph(0,332, handle, TRUE);
	if (state == State::wait)
	{
		//DrawExtendGraph(int x1, int y1, int x2, int y2,int GrHandle, int TransFlag);
		DrawExtendGraph((int)location.x - (int)width / 2, (int)location.y - (int)height / 4, (int)location.x + (int)width / 2, (int)location.y + (int)height / 2, enemy_image[chenge_img], TRUE);
	}
	else
	{
		int left_top_x = (int)location.x - (int)width / 2;
		int left_top_y = (int)location.y - (int)height / 2;
		int right_bottom_x = (int)location.x + (int)width / 2;
		int right_bottom_y = (int)location.y + (int)height / 2;
		DrawExtendGraph(left_top_x + shape_change_x, left_top_y - shape_change_y, right_bottom_x - shape_change_x, right_bottom_y, enemy_image[chenge_img], TRUE);
	}

	/*if (death_effect != nullptr) {
		death_effect->Draw();
	}*/
}

void CrackEnemy::HitReaction(ObjectBase* character)
{
	
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:

		// 敵が押された時SE再生
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

		hp -= 10;
		hit_cursor = true;
		break;
	case ObjectType::goal:
		can_hit = false;
		state = State::death;
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
