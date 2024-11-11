#include "CrackEnemy.h"
#include "../../UtilityFile/Define.h"
#include "../../UtilityFile/ResourceManager.h"
#include <cassert>

CrackEnemy::CrackEnemy()
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

	////画像の読込
	//int sh = LoadSoftImage("Resource/Images/characters/enemy/square.png");
	//if (sh == -1) {
	//	assert(0 && "aaaaaa");
	//}
	//SetPaletteSoftImage(sh, 2, 255, 0, 0, 255);
	//handle2 = CreateGraphFromSoftImage(sh);
	//DeleteSoftImage(sh);
	//handle =  CreateGraphFromSoftImage(LoadSoftImage("Resource/Images/characters/enemy/square.png"));

		// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp_img;

	//敵画像の読み込み
	tmp_img = rm->GetSoftImages("Resource/Images/Characters/Enemy/square.png");
	enemy_image.push_back(tmp_img[0]);

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

void CrackEnemy::Draw() const
{

	//DrawBox((int)location.x - (int)width / 2, (int)location.y - (int)height / 2, (int)location.x + (int)width / 2, (int)location.y + (int)height / 2, 0xffffff, TRUE);
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
	// パレットの一覧を描画
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
	DrawRotaGraph((int)location.x, (int)location.y, 2.0, 0, enemy_image[0], 0);

}

void CrackEnemy::HitReaction(ObjectBase* character)
{
	
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:

		// 敵が押された時SE再生
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

		if (hp >= 20) { can_create_mini = true; }
		hp -= 20;
		width -= 30.0f;
		height -= 30.0f;
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
	default:
		break;
	}
}
