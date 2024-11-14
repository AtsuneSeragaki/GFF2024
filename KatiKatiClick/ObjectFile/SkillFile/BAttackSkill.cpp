#include "BAttackSkill.h"

#include "../../UtilityFile/ResourceManager.h"
#include "DxLib.h"

BAttackSkill::BAttackSkill()
{
	location.x = 10.0f;
	location.y = 700.0f;
	width = BUTTON_WIDTH;
	height = BUTTON_HEIGHT;
	object_type = ObjectType::b_attackskill;
	can_hit = true;
	shape = Shape::square;
	can_delete = false;
	bskill_state = BSkillState::close;

	// ボタン画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/Skill/battack_close.png",1);
	button_img.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Skill/battack_possible.png",1);
	button_img.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Skill/battack_active.png",1);
	button_img.push_back(tmp[0]);
	image = button_img[0];

	// 効果音の読み込み
	int tmp2;
	tmp2 = rm->GetSounds("Resource/Sounds/Click/skill.mp3");
	se[0] = tmp2;

	tmp2 = rm->GetSounds("Resource/Sounds/Click/mouse.mp3");
	se[1] = tmp2;
}

BAttackSkill::~BAttackSkill()
{
	Finalize();
}

void BAttackSkill::Initialize()
{
	location.x = 130.0f;
	location.y = 650.0f;
	width = BUTTON_WIDTH;
	height = BUTTON_HEIGHT;
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
	button_img.push_back(tmp[1]);
	tmp = rm->GetImages("Resource/Images/Skill/battack_active.png");
	button_img.push_back(tmp[2]);
	image = button_img[0];
}

void BAttackSkill::Update()
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

void BAttackSkill::Draw() const
{
	// 状態によって描画する内容を変える
	switch (bskill_state)
	{
	case BSkillState::close:
		DrawGraph(location.x - BUTTON_WIDTH / 2, location.y - BUTTON_HEIGHT / 2, image, TRUE);
		//DrawBoxAA(location.x - BUTTON_WIDTH / 2, location.y - BUTTON_HEIGHT / 2, location.x + BUTTON_WIDTH / 2, location.y + BUTTON_HEIGHT / 2, 0xffffff, TRUE);
		//DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10,(int)location.y - (int)BUTTON_HEIGHT / 2 + 10, "AttackSkill\nclose", 0x000000);
		break;

	case BSkillState::possible:
		DrawGraph(location.x - BUTTON_WIDTH / 2, location.y - BUTTON_HEIGHT / 2, image, TRUE);
		//DrawBoxAA(location.x - BUTTON_WIDTH / 2, location.y - BUTTON_HEIGHT / 2, location.x + BUTTON_WIDTH / 2, location.y + BUTTON_HEIGHT / 2, 0xffff00, TRUE);
		//DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10, (int)location.y - (int)BUTTON_HEIGHT / 2 + 10, "AttackSkill\npossible", 0x000000);
		break;

	case BSkillState::active:
		DrawGraph(location.x - BUTTON_WIDTH / 2, location.y - BUTTON_HEIGHT / 2, image, TRUE);
		//DrawBoxAA(location.x - BUTTON_WIDTH / 2, location.y - BUTTON_HEIGHT / 2, location.x + BUTTON_WIDTH / 2, location.y + BUTTON_HEIGHT / 2, 0x00ff00, TRUE);
		//DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10, (int)location.y - (int)BUTTON_HEIGHT / 2 + 10, "AttackSkill\nactive", 0x000000);
		break;

	default:
		break;
	}

	// 解放に必要なコインの数を描画
	//DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10, (int)location.y - (int)BUTTON_HEIGHT / 2 + 50, "coin:20", 0x000000);

#ifdef _DEBUG

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