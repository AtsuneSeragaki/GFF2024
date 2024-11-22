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

	img_num = 0;
	change_cnt = 0;
	damage_pos = 0;
	damage_display = false;
}

Wall::~Wall()
{
	if (damage_effect != nullptr)
	{
		delete damage_effect;
		damage_effect = nullptr;
	}
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
				can_delete = true;
			}
			change_cnt = 0;
			can_shake = false;
			break;
		default:
			break;
		}
		
	}

	//ダメージエフェクト更新処理
	if (damage_effect != nullptr)
	{
		damage_effect->DamageEffect();

		//消しても良かったら
		if (damage_effect->GetDeleteFlg() == true)
		{
			delete damage_effect;
			damage_effect = nullptr;
		}
	}

	if (location.x == 175)
	{
		location.x += 5;
	}
}

void Wall::Draw() const
{

	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img[0], TRUE);

	if (damage_display == true)
	{
		DrawRotaGraph((int)damage_pos.x, (int)damage_pos.y, 1, 0, damage_img[0], TRUE);
	}

	if (damage_effect != nullptr)
	{
		damage_effect->Draw();
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
			Vector2D set_pos;
			set_pos.x = character->GetLocation().x;
			set_pos.y = location.y;
			damage_effect = new DeathEffect(set_pos);
		}
	}
}
