#include "BSlowDownSkill.h"

#include "../../UtilityFile/ResourceManager.h"
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
	bskill_state = BSkillState::close;
	use_coin = false;

	// ボタン画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/TestSkill.png");
	button_img.push_back(tmp[0]);
	image = button_img[0];
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

	// ボタン画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/TestSkill.png");
	button_img.push_back(tmp[0]);
	image = button_img[0];
}

void BSlowDownSkill::Update()
{
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

void BSlowDownSkill::Finalize()
{
}

void BSlowDownSkill::HitReaction(ObjectBase* character)
{
	switch (character->GetObjectType())
	{
	case ObjectType::cursor:

		if (bskill_state == BSkillState::possible)
		{
			// 解放前SE再生

			bskill_state = BSkillState::standby;
			use_coin = true;
		}
		else if (bskill_state == BSkillState::standby)
		{
			// 解放後SE再生

			bskill_state = BSkillState::active;
		}
		break;

	default:
		break;
	}
}