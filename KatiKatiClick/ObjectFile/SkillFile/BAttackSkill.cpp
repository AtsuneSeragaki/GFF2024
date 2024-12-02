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
	tmp = rm->GetImages("Resource/Images/Skill/battack_possible.png");
	button_img.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Skill/battack_active.png");
	button_img.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Skill/battack_close_d.png", 1);
	button_img.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Skill/battack_possible_d.png");
	button_img.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Skill/battack_active_d.png");
	button_img.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Skill/explosion.png");
	button_img.push_back(tmp[0]);
	image = button_img[0];
	effect_image = button_img[6];

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
	button_img.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Skill/battack_possible.png");
	button_img.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Skill/battack_active.png");
	button_img.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Skill/explosion.png");
	button_img.push_back(tmp[0]);
	image = button_img[0];
	effect_image = button_img[3];

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
	// 状態によって描画する内容を変える
	switch (bskill_state)
	{
	case BSkillState::close:
		DrawGraph(location.x - width / 2, location.y - height / 2, image, TRUE);
		//DrawBoxAA(location.x - BUTTON_WIDTH / 2, location.y - BUTTON_HEIGHT / 2, location.x + BUTTON_WIDTH / 2, location.y + BUTTON_HEIGHT / 2, 0xffffff, TRUE);
		//DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10,(int)location.y - (int)BUTTON_HEIGHT / 2 + 10, "AttackSkill\nclose", 0x000000);
		break;

	case BSkillState::possible:
		DrawGraph(location.x - width / 2, location.y - height / 2, image, TRUE);
		if (effect_width > 44)
		{
			DrawExtendGraph(location.x + 15 - effect_width / 2, location.y - 13 - effect_height / 2, location.x + 15 + effect_width / 2, location.y - 13 + effect_height / 2, effect_image, TRUE);
		}
		//DrawBoxAA(location.x - BUTTON_WIDTH / 2, location.y - BUTTON_HEIGHT / 2, location.x + BUTTON_WIDTH / 2, location.y + BUTTON_HEIGHT / 2, 0xffff00, TRUE);
		//DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10, (int)location.y - (int)BUTTON_HEIGHT / 2 + 10, "AttackSkill\npossible", 0x000000);
		break;

	case BSkillState::active:
		DrawGraph(location.x - width / 2, location.y - height / 2, image, TRUE);
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
			image = button_img[0];
			break;

		case BSkillState::possible:
			image = button_img[1];
			break;

		case BSkillState::active:
			image = button_img[2];
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
			image = button_img[3];
			break;

		case BSkillState::possible:
			image = button_img[4];
			break;

		case BSkillState::active:
			image = button_img[5];
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
