#include "BSlowDownSkill.h"

#include "../../UtilityFile/ResourceManager.h"
#include "DxLib.h"

BSlowDownSkill::BSlowDownSkill()
{
	location.x = 0.0f;
	location.y = 0.0f;
	width = SKILL_BUTTON_WIDTH;
	height = SKILL_BUTTON_HEIGHT;
	object_type = ObjectType::b_slowdownskill;
	can_hit = true;
	shape = Shape::square;
	can_delete = false;
	bskill_state = BSkillState::close;
	use_coin = false;
	hit_cursor = false;

	// ボタン画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/Skill/skill_button.png");
	button_img.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Skill/bslowdown.png");
	button_img.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Skill/spiderweb.png");
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

	effect_x = (int)location.x;
	effect_y = (int)location.y - 5;
	effect_width = 200;
	effect_height = 200;

	red = 168;
	blue = 168;
	green = 168;
	webs_alpha=255;
}

BSlowDownSkill::~BSlowDownSkill()
{

}

void BSlowDownSkill::Initialize()
{
	location.x = 330.0f;
	location.y = 650.0f;
	width = SKILL_BUTTON_WIDTH;
	height = SKILL_BUTTON_HEIGHT;
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
	ChangeImage();
	hit_cursor = false;

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

void BSlowDownSkill::Draw() const
{
	//色をかぶせる
	SetDrawBright(red, green, blue);
	DrawGraphF(location.x - SKILL_BUTTON_WIDTH / 2.0f - 5.0f, location.y - height / 2.0f, button_img[0], TRUE);
	SetDrawBright(255, 255, 255);

	//カーソルがヒットしていたらマークに薄い黒を重ねる
	if (hit_cursor)
	{
		// 暗くする
		SetDrawBright(150, 150, 150);
		// マークの描画
		DrawRotaGraphF(location.x /*+ 15.0f*/, location.y, 1, 0, button_img[1], TRUE);
		SetDrawBright(255, 255, 255);
	}
	else
	{
		// マークの描画
		DrawRotaGraphF(location.x /*+ 15.0f*/, location.y, 1, 0, button_img[1], TRUE);
	}

	//if(hit_cursor==true)
	//{
	//	// 描画ブレンドモードをアルファブレンドにする
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 20);
	//}
	//else {
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	//}
	//DrawRotaGraphF(location.x + 15.0f, location.y - 15.0f, 3, 0, button_img[2], TRUE);
	//// 描画ブレンドモードをノーブレンドにする
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//SetDrawBright(255, 255, 255);


	// 状態によって描画する内容を変える
	switch (bskill_state)
	{
	case BSkillState::close:
		//DrawGraph(location.x - width / 2, location.y - height / 2, image, TRUE);
		//DrawBoxAA(location.x - SKILL_BUTTON_WIDTH / 2, location.y - SKILL_BUTTON_HEIGHT / 2, location.x + SKILL_BUTTON_WIDTH / 2, location.y + SKILL_BUTTON_HEIGHT / 2, 0xffffff, FALSE);
		//DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10, (int)location.y - (int)BUTTON_HEIGHT / 2 + 10, "SlowDownSkill\nclose", 0x000000);
		break;

	case BSkillState::possible:
		//DrawGraph(location.x - width / 2, location.y - height / 2, image, TRUE);
		if (effect_width > 44)
		{
			DrawExtendGraphF(location.x /*+ 15.0f */- effect_width / 2.0f, location.y - 12.0f - effect_height / 2.0f, location.x /*+ 15.0f*/ + effect_width / 2.0f, location.y - 9.0f + effect_height / 2.0f, effect_image, TRUE);
		}
		//DrawExtendGraph(effect_x - effect_width / 2, effect_y - effect_height / 2, effect_x + effect_width / 2, effect_y + effect_height / 2, effect_image, TRUE);
		//DrawBoxAA(location.x - BUTTON_WIDTH / 2, location.y - BUTTON_HEIGHT / 2, location.x + BUTTON_WIDTH / 2, location.y + BUTTON_HEIGHT / 2, 0xffff00, TRUE);
		//DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10, (int)location.y - (int)BUTTON_HEIGHT / 2 + 10, "SlowDownSkill\npossible", 0x000000);
		break;

	case BSkillState::active:
		//DrawGraph(location.x - width / 2, location.y - height / 2, image, TRUE);
		//DrawBoxAA(location.x - BUTTON_WIDTH / 2, location.y - BUTTON_HEIGHT / 2, location.x + BUTTON_WIDTH / 2, location.y + BUTTON_HEIGHT / 2, 0x00ff00, TRUE);
		//DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10, (int)location.y - (int)BUTTON_HEIGHT / 2 + 10, "SlowDownSkill\nactive", 0x000000);
		break;

	default:
		break;
	}

	// 解放に必要なコインの数を描画
	//DrawString((int)location.x - (int)BUTTON_WIDTH / 2 + 10, (int)location.y - (int)BUTTON_HEIGHT / 2 + 50, "coin:40", 0x000000);

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

void BSlowDownSkill::ChangeImage()
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
			//暗い灰色をセット
			red = 100;
			green = 102;
			blue = 95;
			break;

		case BSkillState::possible:
			//暗い黄色をセット
			red = 151;
			green = 129;
			blue = 12;
			break;

		case BSkillState::active:
			//暗い緑をセット
			red = 74;
			green = 120;
			blue = 29;
			break;

		default:
			break;
		}
	}
}

void BSlowDownSkill::ChangeButtonSize()
{
	if (effect_width > 44)
	{
		effect_width -=7;
		effect_height -= 7;
	}
}
