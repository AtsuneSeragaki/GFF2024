#include "DamageEffect.h"
#include "DxLib.h"
#include "../../UtilityFile/ResourceManager.h"

DamageEffect::DamageEffect(Vector2D set_location, unsigned int get_color)
{
	color = get_color;
	box_width = 3;
	box_height = 3;

	pos1 = set_location;
	pos2 = set_location;
	pos3 = set_location;
	pos4 = set_location;
	pos = set_location;

	//pos1.x -= 15;
	//pos1.y -= 10;
	//pos2.x += 5;
	//pos2.y -= 10;
	//pos3.x += 5;
	//pos3.y += 10;
	//pos4.x -= 15;
	//pos4.y += 10;

	count = 0;
	alpha = 255;

	vel = -10;
	acc = 1;
	can_delete = false;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp_img;
	tmp_img = rm->GetImages("Resource/Images/Barrier/smoke.png", 4, 4, 1, 64, 32);
	for (int i = 0; i < 4; i++)
	{
		smoke_img.push_back(tmp_img[i]);
	}
	img_num = 0;
	smoke_flg = false;
	smoke_cnt = 0;
	effect_type = Effect_Type::none;

	move = 0.0f;
}

DamageEffect::~DamageEffect()
{
}

void DamageEffect::Update()
{

	switch (effect_type)
	{
	case Effect_Type::enemy_damage:
		EnemyDamageEffect();
		break;
	case Effect_Type::wall_damage:
		WallDamageEffect();
		break;
	default:
		break;
	}

}

void DamageEffect::EnemyDamageEffect()
{
	/*
	//段々大きくする
	float num = (float)count;

	switch (count)
	{
	case 2:
		move = 4;
		break;
	case 5:
		move = 6;
		box_width = 4;
		box_height = 4;
		break;
	case 9:
		box_width =3;
		box_height = 3;
		//alpha = 240;
		break;
	default:
		break;
	}

	if (count < 10)
	{
		pos1.x -= move;
		pos1.y -= move;
		pos2.x += move;
		pos2.y -= move;
		pos3.x += move;
		pos3.y += move;
		pos4.x -= move;
		pos4.y += move;
	}

	if (count < 15) {
		count++;

	}
	else
	{
		can_delete = true;
	}
	*/

	vel += acc;
	pos1.y += vel;
	pos2.y += vel;
	pos3.y += vel;
	pos4.y += vel;

	pos1.x -= 4.0f;
	pos2.x += 3.0f;
	pos3.x -= 5.0f;
	pos4.x += 6.0f;


}

void DamageEffect::WallDamageEffect()
{
	vel += acc;
	pos1.y += vel;
	pos2.y += vel;
	pos3.y += vel;
	pos4.y += vel;

	pos1.x -= 6.0f;
	pos2.x += 5.0f;
	pos3.x -= 3.0f;
	pos4.x += 4.0f;


	smoke_cnt++;
	if (smoke_cnt > 3)
	{
		smoke_cnt = 0;
		img_num++;
		if (img_num > 3)
		{
			img_num = 0;
			smoke_flg = false;

			can_delete = true;
		}
	}

	

}

void DamageEffect::Draw() const
{
	int shift = 1;

	switch (effect_type)
	{
	case Effect_Type::enemy_damage:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		//枠部分
		DrawBox((int)pos1.x - box_width-shift, (int)pos1.y - box_height-shift, (int)pos1.x + shift + box_width, (int)pos1.y + shift + box_height, 0x000000, TRUE);
		DrawBox((int)pos2.x - box_width-shift, (int)pos2.y - box_height-shift, (int)pos2.x + shift + box_width, (int)pos2.y + shift + box_height, 0x000000, TRUE);
		DrawBox((int)pos3.x - box_width-shift, (int)pos3.y - box_height-shift, (int)pos3.x + shift + box_width, (int)pos3.y + shift + box_height, 0x000000, TRUE);
		DrawBox((int)pos4.x - box_width-shift, (int)pos4.y - box_height-shift, (int)pos4.x + shift + box_width, (int)pos4.y + shift + box_height, 0x000000, TRUE);


		DrawBox((int)pos1.x-box_width, (int)pos1.y-box_height, (int)pos1.x +box_width, (int)pos1.y +box_height, color, TRUE);
		DrawBox((int)pos2.x-box_width, (int)pos2.y - box_height, (int)pos2.x + box_width, (int)pos2.y +  box_height, color, TRUE);
		DrawBox((int)pos3.x - box_width, (int)pos3.y - box_height, (int)pos3.x + box_width, (int)pos3.y +  box_height, color, TRUE);
		DrawBox((int)pos4.x - box_width, (int)pos4.y - box_height, (int)pos4.x +  box_width, (int)pos4.y +  box_height, color, TRUE);
		// 描画ブレンドモードをノーブレンドにする
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	case Effect_Type::wall_damage:
		DrawBox((int)pos1.x, (int)pos1.y, (int)pos1.x + 10, (int)pos1.y + 10, color, TRUE);
		DrawBox((int)pos2.x, (int)pos2.y, (int)pos2.x + 10, (int)pos2.y + 10, color, TRUE);
		DrawBox((int)pos3.x, (int)pos3.y, (int)pos3.x + 10, (int)pos3.y + 10, color, TRUE);
		DrawBox((int)pos4.x, (int)pos4.y, (int)pos4.x + 10, (int)pos4.y + 10, color, TRUE);
		DrawRotaGraph((int)pos.x, (int)pos.y - 64, 3, 0, smoke_img[img_num], TRUE);
		break;
	default:
		break;
	}

}

bool DamageEffect::GetDeleteFlg()
{
	return can_delete;
}

