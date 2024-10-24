#include "AttackSkill.h"

#include "DxLib.h"

AttackSkill::AttackSkill() : effect_img()
{
	location.x = 0.0f;
	location.y = 0.0f;
	object_type = ObjectType::skill;
	radius = 10.0f;
	can_hit = true;

	for (int i = 0; i < BUTTON_IMG_NUM; i++)
	{
		button_img[i] = 0;
	}

	button_x = 0;
	button_y = 0;
	skill_state = SkillState::close;

	coin = 0;
}

AttackSkill::~AttackSkill()
{
}

void AttackSkill::Initialize()
{
	location.x = 0.0f;
	location.y = 0.0f;
	object_type = ObjectType::skill;
	radius = 10.0f;
	can_hit = true;

	button_x = 50;
	button_y = 600;
	skill_state = SkillState::close;

	coin = 20;
}

void AttackSkill::Update()
{
	if (coin >= 20 && skill_state == SkillState::close)
	{
		skill_state = SkillState::possible;
	}
}

void AttackSkill::Draw() const
{
	// 状態によって描画する内容を変える
	switch (skill_state)
	{
	case SkillState::close:
		DrawBox(button_x, button_y, button_x + BUTTON_WIDTH, button_y + BUTTON_HEIGHT, 0xffffff, TRUE);
		DrawString(button_x + 10, button_y + 10, "AttackSkill\nclose", 0x000000);
		break;

	case SkillState::possible:
		DrawBox(button_x, button_y, button_x + BUTTON_WIDTH, button_y + BUTTON_HEIGHT, 0xffff00, TRUE);
		DrawString(button_x + 10, button_y + 10, "AttackSkill\npossible", 0x000000);
		break;

	case SkillState::standby:
		DrawBox(button_x, button_y, button_x + BUTTON_WIDTH, button_y + BUTTON_HEIGHT, 0x0000ff, TRUE);
		DrawString(button_x + 10, button_y + 10, "AttackSkill\nstanby", 0x000000);
		break;

	case SkillState::active:
		DrawBox(button_x, button_y, button_x + BUTTON_WIDTH, button_y + BUTTON_HEIGHT, 0x00ff00, TRUE);
		DrawString(button_x + 10, button_y + 10, "AttackSkill\nactive", 0x000000);
		break;

	default:
		break;
	}

#ifdef _DEBUG
	// コインの枚数（テスト用）
	SetFontSize(20);
	DrawFormatString(1200, 0, 0xffffff, "coin_test:%d", coin);

#endif // _DEBUG
}

void AttackSkill::HitReaction(ObjectBase* character)
{
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:

		if (skill_state == SkillState::possible)
		{
			skill_state = SkillState::standby;
		}
		else if(skill_state == SkillState::standby)
		{
			skill_state = SkillState::active;
		}

		break;
	default:
		break;
	}
}