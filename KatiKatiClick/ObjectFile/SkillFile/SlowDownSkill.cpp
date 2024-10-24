#include "SlowDownSkill.h"

#include "DxLib.h"

SlowDownSkill::SlowDownSkill() : effect_img()
{
	location.x = 250.0f;
	location.y = 600.0f;
	object_type = ObjectType::skill;
	radius = 80.0f;
	can_hit = true;

	for (int i = 0; i < BUTTON_IMG_NUM; i++)
	{
		button_img[i] = 0;
	}

	button_x = 250;
	button_y = 600;
	skill_state = SkillState::close;

	coin = 40;
}

SlowDownSkill::~SlowDownSkill()
{
}

void SlowDownSkill::Initialize()
{
	location.x = 0.0f;
	location.y = 0.0f;
	object_type = ObjectType::skill;
	radius = 10.0f;
	can_hit = true;

	button_x = 50;
	button_y = 600;
	skill_state = SkillState::close;

	coin = 40;
}

void SlowDownSkill::Update()
{
	if (coin >= 40 && skill_state == SkillState::close)
	{
		skill_state = SkillState::possible;
	}
}

void SlowDownSkill::Draw() const
{
	// 状態によって描画する内容を変える
	switch (skill_state)
	{
	case SkillState::close:
		DrawBox(button_x, button_y, button_x + BUTTON_WIDTH, button_y + BUTTON_HEIGHT, 0xffffff, TRUE);
		DrawString(button_x + 10, button_y + 10, "SlowDownSkill\nclose", 0x000000);
		break;

	case SkillState::possible:
		DrawBox(button_x, button_y, button_x + BUTTON_WIDTH, button_y + BUTTON_HEIGHT, 0xffff00, TRUE);
		DrawString(button_x + 10, button_y + 10, "SlowDownSkill\npossible", 0x000000);
		break;

	case SkillState::standby:
		DrawBox(button_x, button_y, button_x + BUTTON_WIDTH, button_y + BUTTON_HEIGHT, 0x0000ff, TRUE);
		DrawString(button_x + 10, button_y + 10, "SlowDownSkill\nstanby", 0x000000);
		break;

	case SkillState::active:
		DrawBox(button_x, button_y, button_x + BUTTON_WIDTH, button_y + BUTTON_HEIGHT, 0x00ff00, TRUE);
		DrawString(button_x + 10, button_y + 10, "SlowDownSkill\nactive", 0x000000);
		break;

	default:
		break;
	}

#ifdef _DEBUG
	// コインの枚数（テスト用）
	SetFontSize(20);
	DrawFormatString(1000, 20, 0xffffff, "coin_test:%d", coin);

#endif // _DEBUG
}

void SlowDownSkill::HitReaction(ObjectBase* character)
{
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:

		if (skill_state == SkillState::possible)
		{
			skill_state = SkillState::standby;
		}
		else if (skill_state == SkillState::standby)
		{
			skill_state = SkillState::active;
		}
		break;

	default:
		break;
	}
}