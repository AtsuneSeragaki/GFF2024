#include "Wall.h"
#include "DxLib.h"
#include "../../UtilityFile/Define.h"
#include "../../UtilityFile/ResourceManager.h"

Wall::Wall()
{

	location.x = (float)SCREEN_WIDTH / 2.0f;
	width = (float)SCREEN_WIDTH;
	height = (float)ONE_LANE_HEIGHT / 4.0f;
	shape = Shape::square;
	object_type = ObjectType::wall;
	hp = 2;
	can_hit = true;
	can_shake = false;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp_img;

	//敵画像の読み込み
	tmp_img = rm->GetImages("Resource/Images/Barrier/Barrier.png");

	img.push_back(tmp_img[0]);
	

	tmp_img = rm->GetImages("Resource/Images/Barrier/BarrierDamage.png");
	damage_img.push_back(tmp_img[0]);

	tmp_img = rm->GetImages("Resource/Images/Barrier/smoke.png",4,4,1,64,32);
	for (int i = 0; i < 4; i++)
	{
		smoke_img.push_back(tmp_img[i]);
	}
	img_num = 0;
	change_cnt = 0;
	damage_pos = 0;
	damage_display = false;
	smoke_flg = false;
	smoke_cnt = 0;
}

Wall::~Wall()
{

}

void Wall::Initialize()
{
}

void Wall::Update()
{
	//if (change_cnt++ > 10)
	//{
	//	change_cnt = 0;
	//	img_num++;
	//	if (img_num > 3)
	//	{
	//		img_num = 0;
	//	}
	//}

	if (can_shake == true)
	{
		change_cnt++;
		switch (change_cnt)
		{
		case 0:
			location.x += 20;
			break;
		case 2:
			location.x -= 10;
			break;
		case 4:
			location.x += 20;
			break;
		case 6:
			location.x -= 10;
			break;
		case 8:
			//hpが0になったら
			if (hp <= 0)
			{
				smoke_flg = true;
				can_hit = false;
			}
			change_cnt = 0;
			can_shake = false;
			break;
		default:
			break;
		}
		
	}

	if (smoke_flg == true)
	{
		smoke_cnt++;
		if (smoke_cnt > 10)
		{
			smoke_cnt = 0;
			img_num++;
			if (img_num > 3)
			{
				img_num = 0;
				can_delete = true;
				smoke_flg = false;
			}
		}

	}

	////ダメージエフェクト更新処理
	//if (damage_effect != nullptr)
	//{
	//	damage_effect->WallDamageEffect();

	//	//消しても良かったら
	//	if (damage_effect->GetDeleteFlg() == true)
	//	{
	//		delete damage_effect;
	//		damage_effect = nullptr;
	//	}
	//}

}

void Wall::Draw() const
{


	if (smoke_flg == true)
	{
		DrawExtendGraph((int)location.x - (int)width / 2, (int)location.y - (int)height*2, (int)location.x + (int)width / 2, (int)location.y + (int)height / 2, smoke_img[img_num], TRUE);
	}
	else
	{
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img[0], TRUE);
		if (damage_display == true)
		{
			DrawRotaGraph((int)damage_pos.x, (int)damage_pos.y, 1, 0, damage_img[0], TRUE);
		}
	}

	
	//DrawBox((int)location.x - (int)width / 2, (int)location.y - (int)height / 2, (int)location.x + (int)width / 2, (int)location.y + (int)height / 2, 0xffff00, TRUE);
	//DrawBox((int)location.x - (int)width / 2, (int)location.y - (int)height / 2, (int)location.x + (int)width / 2, (int)location.y + (int)height / 2, 0xAD6820, FALSE);
}

void Wall::HitReaction(ObjectBase* character)
{
	if (character->GetObjectType() == ObjectType::enemy)
	{
		if (hp > 0)
		{
			hp -= 1;
			damage_display = true;
			damage_pos.y = location.y;
			damage_pos.x = character->GetLocation().x;//座標貰う
			can_shake = true;
			//Vector2D set_pos;
			//set_pos.x = character->GetLocation().x;
			//set_pos.y = location.y;
			//damage_effect = new DamageEffect(set_pos);
		}
	}
}
