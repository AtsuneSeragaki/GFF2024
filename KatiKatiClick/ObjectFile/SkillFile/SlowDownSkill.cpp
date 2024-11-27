#include "SlowDownSkill.h"

#include "../../UtilityFile/ResourceManager.h"
#include "DxLib.h"

SlowDownSkill::SlowDownSkill()
{
	can_hit = true;
	object_type = ObjectType::slowdownskill;
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
	tmp = rm->GetImages("Resource/Images/Skill/spiderweb.png");
	effect_img.push_back(tmp[0]);
	image = effect_img[0];

	int tmp2;
	tmp2 = rm->GetSounds("Resource/Sounds/GameMain/Skill/kumonosu.mp3");
	se = tmp2;
}

SlowDownSkill::~SlowDownSkill()
{
	effect_img.clear();
	DeleteGraph(image);
}

void SlowDownSkill::Update()
{
	if (cnt == 0)
	{
		PlaySoundMem(se, DX_PLAYTYPE_BACK, TRUE);
	}

	cnt++;

	if (max_flg == false)
	{
		ChangeWidthHeight();
	}

	if (cnt >= 270)
	{
		ChangeBlendNum();
	}

	if (cnt > 300)
	{
		can_delete = true;
		cnt = 0;
	}
}

void SlowDownSkill::Initialize()
{
}

void SlowDownSkill::Draw() const
{
	DrawBoxAA(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, 0xffffff, TRUE);
	// 描画ブレンドモードをアルファブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend_num);
	DrawExtendGraph(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, image, TRUE);
	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SlowDownSkill::Finalize()
{
}

void SlowDownSkill::HitReaction(ObjectBase* character)
{
}

void SlowDownSkill::ChangeWidthHeight()
{
	width += 5;
	height += 5;

	if (width >= 150)
	{
		max_flg = true;
	}
}

void SlowDownSkill::ChangeBlendNum()
{
	if (blend_num > 0)
	{
		blend_num -= 9;
	}
}
