#include "AttackSKill.h"

#include "../../UtilityFile/ResourceManager.h"
#include "DxLib.h"

AttackSkill::AttackSkill()
{
	can_hit = true;
	object_type = ObjectType::attackskill;
	shape = Shape::square;
	can_delete = false;
	height = 0.0f;
	width = 0.0f;
	disp_flg = true;
	effect_num = 0;
	max_flg = false;
	blend_num = 255;

	// 画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/Skill/explosion1.png",3,3,1,16,16);
	for (int i = 0; i < 3; i++)
	{
		effect_img.push_back(tmp[i]);
	}
	
	image = effect_img[0];
}

AttackSkill::~AttackSkill()
{
	effect_img.clear();
	DeleteGraph(image);
}

void AttackSkill::Update()
{
	cnt++;

	if (cnt % 10 == 0)
	{
		ChangeEffectImage();
	}

	if (max_flg == false)
	{
		ChangeWidthHeight();
	}
	
	if (cnt >= 50)
	{
		ChangeBlendNum();
	}

	if (cnt > 60)
	{
		can_delete = true;
		cnt = 0;
	}
}

void AttackSkill::Initialize()
{
}

void AttackSkill::Draw() const
{
	//DrawBoxAA(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, 0xffffff,TRUE);
	// 描画ブレンドモードをアルファブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend_num);
	DrawExtendGraph(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, image, TRUE);
	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void AttackSkill::Finalize()
{
}

void AttackSkill::HitReaction(ObjectBase* character)
{
}

void AttackSkill::ChangeEffectImage()
{
	if (effect_num < 2)
	{
		effect_num++;
	}
	
	image = effect_img[effect_num];
}

void AttackSkill::ChangeWidthHeight()
{
	if (effect_num == 0)
	{
		width += 3;
		height += 3;
	}
	else
	{
		width += 7;
		height += 7;
	}

	if (width >= 150)
	{
		max_flg = true;
	}
}

void AttackSkill::ChangeBlendNum()
{
	if (blend_num > 0)
	{
		blend_num -= 25;
	}
}