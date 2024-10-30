#include "BSlowDownSkill.h"

#include "DxLib.h"

BSlowDownSkill::BSlowDownSkill()
{
	location.x = 330.0f;
	location.y = 650.0f;
	width = BUTTON_WIDTH;
	height = BUTTON_HEIGHT;
	object_type = ObjectType::b_slowdownskill;
	can_hit = true;
	shape = Shape::square;
	can_delete = false;

	for (int i = 0; i < BUTTON_IMG_NUM; i++)
	{
		button_img[i] = 0;
	}

	bskill_state = BSkillState::close;
}

BSlowDownSkill::~BSlowDownSkill()
{
}

void BSlowDownSkill::Initialize()
{
	location.x = 330.0f;
	location.y = 650.0f;
	width = BUTTON_WIDTH;
	height = BUTTON_HEIGHT;
	object_type = ObjectType::b_slowdownskill;
	can_hit = true;
	shape = Shape::square;
	can_delete = false;
	bskill_state = BSkillState::close;
}

void BSlowDownSkill::Update()
{
	if (bskill_state == BSkillState::close)
	{
		bskill_state = BSkillState::possible;
	}
}

void BSlowDownSkill::Draw() const
{
	// 状態によって描画する内容を変える
	switch (bskill_state)
	{
	case BSkillState::close:
		DrawBoxAA(location.x - BUTTON_WIDTH / 2, location.y - BUTTON_HEIGHT / 2, location.x + BUTTON_WIDTH / 2, location.y + BUTTON_HEIGHT / 2, 0xffffff, TRUE);
		DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10, (int)location.y - (int)BUTTON_HEIGHT / 2 + 10, "SlowDownSkill\nclose", 0x000000);
		break;

	case BSkillState::possible:
		DrawBoxAA(location.x - BUTTON_WIDTH / 2, location.y - BUTTON_HEIGHT / 2, location.x + BUTTON_WIDTH / 2, location.y + BUTTON_HEIGHT / 2, 0xffff00, TRUE);
		DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10, (int)location.y - (int)BUTTON_HEIGHT / 2 + 10, "SlowDownSkill\npossible", 0x000000);
		break;

	case BSkillState::standby:
		DrawBoxAA(location.x - BUTTON_WIDTH / 2, location.y - BUTTON_HEIGHT / 2, location.x + BUTTON_WIDTH / 2, location.y + BUTTON_HEIGHT / 2, 0x0000ff, TRUE);
		DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10, (int)location.y - (int)BUTTON_HEIGHT / 2 + 10, "SlowDownSkill\nstanby", 0x000000);
		break;

	case BSkillState::active:
		DrawBoxAA(location.x - BUTTON_WIDTH / 2, location.y - BUTTON_HEIGHT / 2, location.x + BUTTON_WIDTH / 2, location.y + BUTTON_HEIGHT / 2, 0x00ff00, TRUE);
		DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10, (int)location.y - (int)BUTTON_HEIGHT / 2 + 10, "SlowDownSkill\nactive", 0x000000);
		break;

	default:
		break;
	}

#ifdef _DEBUG

#endif // _DEBUG
}

void BSlowDownSkill::HitReaction(ObjectBase* character)
{
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:

		if (bskill_state == BSkillState::possible)
		{
			bskill_state = BSkillState::standby;
		}
		else if (bskill_state == BSkillState::standby)
		{
			bskill_state = BSkillState::active;
		}
		break;

	default:
		break;
	}
}