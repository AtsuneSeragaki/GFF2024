#include "BAttackSkill.h"

#include "../../UtilityFile/ResourceManager.h"
#include "DxLib.h"

BAttackSkill::BAttackSkill()
{
	location.x = 10.0f;
	location.y = 700.0f;
	width = SKILL_BUTTON_WIDTH;
	height = SKILL_BUTTON_HEIGHT;
	object_type = ObjectType::b_attackskill;
	can_hit = true;
	shape = Shape::square;
	can_delete = false;
	bskill_state = BSkillState::close;
	hit_cursor = false;

	// ボタン画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/Skill/battack_close.png",1);
	button_img.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Skill/battack.png",1);
	button_img.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Skill/explosion.png");
	button_img.push_back(tmp[0]);
	image = button_img[0];
	effect_image = button_img[2];

	// 効果音の読み込み
	int tmp_s;
	tmp_s = rm->GetSounds("Resource/Sounds/GameMain/Click/skill.mp3");
	se[0] = tmp_s;

	tmp_s = rm->GetSounds("Resource/Sounds/GameMain/Click/mouse.mp3");
	se[1] = tmp_s;

	tmp_s = rm->GetSounds("Resource/Sounds/GameMain/Skill/skill_possible.mp3");
	se[2] = tmp_s;

	// 音量変更
	ChangeVolumeSoundMem(150, se[0]);
	ChangeVolumeSoundMem(200, se[2]);

	effect_width = 200;
	effect_height = 200;

	red = 168;
	blue = 168;
	green = 168;
}

BAttackSkill::~BAttackSkill()
{
	Finalize();
}

void BAttackSkill::Initialize()
{
	location.x = 130.0f;
	location.y = 650.0f;
	width = SKILL_BUTTON_WIDTH;
	height = SKILL_BUTTON_HEIGHT;
	object_type = ObjectType::b_attackskill;
	can_hit = true;
	shape = Shape::square;
	can_delete = false;
	bskill_state = BSkillState::close;
	use_coin = false;

	// ボタン画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("../../Resource/Images/battack_close.png");
	tmp = rm->GetImages("Resource/Images/Skill/explosion.png");
	button_img.push_back(tmp[0]);
	image = button_img[0];
	effect_image = button_img[4];

	effect_x = location.x;
	effect_y = location.y - 5;
	effect_width = 200;
	effect_height = 200;
}

void BAttackSkill::Update()
{
	ChangeImage();

	if (bskill_state == BSkillState::possible)
	{
		if (effect_width == 200)
		{
			PlaySoundMem(se[2], DX_PLAYTYPE_BACK, TRUE);
		}
		ChangeButtonSize();
	}
	else
	{
		effect_width = 200;
		effect_height = 200;
	}
}

void BAttackSkill::Draw() const
{

	SetDrawBright(red, green, blue);
	DrawGraphF(location.x - width / 2.0f, location.y - height / 2.0f, button_img[0], TRUE);
	if(hit_cursor==false){ SetDrawBright(255, 255, 255); }
	DrawRotaGraphF(location.x+15.0f, location.y, 1, 0, button_img[1], TRUE);

	SetDrawBright(255, 255, 255);
	// 状態によって描画する内容を変える
	switch (bskill_state)
	{
	case BSkillState::close:
		//DrawGraph(location.x - width / 2, location.y - height / 2, image, TRUE);
		//DrawBoxAA(location.x - BUTTON_WIDTH / 2, location.y - BUTTON_HEIGHT / 2, location.x + BUTTON_WIDTH / 2, location.y + BUTTON_HEIGHT / 2, 0xffffff, TRUE);
		//DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10,(int)location.y - (int)BUTTON_HEIGHT / 2 + 10, "AttackSkill\nclose", 0x000000);
		break;

	case BSkillState::possible:
		//DrawGraph(location.x - width / 2, location.y - height / 2, image, TRUE);

		SetDrawBright(255, 213, 21);
		if (effect_width > 44)
		{
			DrawExtendGraphF(location.x + 15.0f - effect_width / 2.0f, location.y - 13.0f - effect_height / 2.0f, location.x + 15.0f + effect_width / 2.0f, location.y - 13.0f + effect_height / 2.0f, effect_image, TRUE);
		}
		SetDrawBright(255, 255, 255);

		//DrawBoxAA(location.x - BUTTON_WIDTH / 2, location.y - BUTTON_HEIGHT / 2, location.x + BUTTON_WIDTH / 2, location.y + BUTTON_HEIGHT / 2, 0xffff00, TRUE);
		//DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10, (int)location.y - (int)BUTTON_HEIGHT / 2 + 10, "AttackSkill\npossible", 0x000000);
		break;

	case BSkillState::active:
		//DrawGraph(location.x - width / 2, location.y - height / 2, image, TRUE);
		//DrawBoxAA(location.x - BUTTON_WIDTH / 2, location.y - BUTTON_HEIGHT / 2, location.x + BUTTON_WIDTH / 2, location.y + BUTTON_HEIGHT / 2, 0x00ff00, TRUE);
		//DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10, (int)location.y - (int)BUTTON_HEIGHT / 2 + 10, "AttackSkill\nactive", 0x000000);
		break;

	default:
		break;
	}



	// 解放に必要なコインの数を描画
	//DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10, (int)location.y - (int)BUTTON_HEIGHT / 2 + 50, "coin:20", 0x000000);

#ifdef _DEBUG
	//DrawExtendGraph(effect_x - effect_width / 2, effect_y - effect_height / 2, effect_x + effect_width / 2, effect_y + effect_height / 2, effect_image, TRUE);
#endif // _DEBUG
}

void BAttackSkill::Finalize()
{
	button_img.clear();
}

void BAttackSkill::HitReaction(ObjectBase* character)
{
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:

		if (bskill_state == BSkillState::possible)
		{
			// 解放前SE再生
			
			PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);
			bskill_state = BSkillState::active;
			use_coin = true;
			effect_width = 200;
			effect_height = 200;
		}
		else
		{
			// 何も起きない時のSE再生
			PlaySoundMem(se[1], DX_PLAYTYPE_BACK, TRUE);
		}

		break;

	default:
		
		break;
	}
}

void BAttackSkill::ChangeImage()
{
	if (hit_cursor == false)
	{
		switch (bskill_state)
		{
		case BSkillState::close:
			//灰色をセット
			red = 168;
			blue = 168;
			green = 168;
			break;

		case BSkillState::possible:
			//黄色をセット
			red = 255;
			green = 213;
			blue = 21;
			break;

		case BSkillState::active:
			//緑をセット
			red = 124;
			green = 197;
			blue = 51;
			break;

		default:
			break;
		}
	}
	else
	{
		switch (bskill_state)
		{
		case BSkillState::close:
			red = 100;
			green = 102;
			blue = 95;
			break;

		case BSkillState::possible:
			red = 151;
			green = 129;
			blue = 12;
			break;

		case BSkillState::active:
			red = 74;
			green = 120;
			blue = 29;
			break;

		default:
			break;
		}
	}
}

void BAttackSkill::ChangeButtonSize()
{
	if (effect_width > 44)
	{
		effect_width -= 3;
		effect_height -= 3;
	}
}
