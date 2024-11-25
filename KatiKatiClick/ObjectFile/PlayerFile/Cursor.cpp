#include "Cursor.h"
#include "../../UtilityFile/MouseInput.h"
#include "../../UtilityFile/ResourceManager.h"
#include "DxLib.h"

Cursor::Cursor()
{
	location.x = 0.0f;
	location.y = 0.0f;
	object_type = ObjectType::cursor;
	shape = Shape::circle;
	radius = 12.0f;
	can_hit = false;

	ResourceManager* rm = ResourceManager::GetInstance();
	int tmp;
	tmp = rm->GetSounds("Resource/Sounds/GameMain/Click/mouse.mp3");
	se = tmp;

	//std::vector<int> tmp_img;
	//tmp_img = rm->GetImages("Resource/Images/Characters/Cursor/attack.png", 2, 2, 1, 37, 25);
	//for (int i = 0; i < 2; i++)
	//{
	//	cursor_img.push_back(tmp_img[i]);
	//}
	//tmp_img = rm->GetImages("Resource/Images/Characters/Cursor/nomal.png", 2, 2, 1, 31, 28);
	////tmp_img = rm->GetImages("Resource/Images/Characters/Cursor/effect.png");
	//for (int i = 0; i < 2; i++)
	//{
	//	cursor_img.push_back(tmp_img[i]);
	//}
	
	std::vector<int>tmp_img2;
	tmp_img2 = rm->GetImages("Resource/Images/Characters/Cursor/cursor.png");
	cursor_img.push_back(tmp_img2[0]);
	img_num = 0;
	count = 0;

	state = P_State::wait;
	angle = 0;
}

Cursor::~Cursor()
{
}

void Cursor::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	int tmp;
	tmp = rm->GetSounds("Resource/Sounds/Click/mouse.mp3");
	se = tmp;
}

void Cursor::Update()
{

	location = MouseInput::GetMouseLocation();
	

	if (MouseInput::GetMouseState() == eMouseInputState::eClick)
	{
		// クリックSE再生
		PlaySoundMem(se, DX_PLAYTYPE_BACK, TRUE);

		// クリックエフェクト生成
		click_effect.push_back(new ClickEffect);
		click_effect.back()->SetLocation(location);

		can_hit = true;
		count = 0;
		state = P_State::attack;
	}
	else
	{
		can_hit = false;
	}


	if (state == P_State::attack)
	{


		if (count > 5)
		{
			angle = -1;
		}
		else {
			angle = -2;

		}

		if (count > 10)
		{
			count = 0;
			state = P_State::wait;
		}

		count++;
	}
	else
	{
		angle = 0;
	}


	for (int i = 0; i < click_effect.size(); i++)
	{
		// クリックエフェクト更新処理
		click_effect[i]->Update();

		if (click_effect[i]->GetDeleteFlg() == true)
		{
			// 削除
			click_effect.erase(click_effect.begin() + i);
		}
	}
}

void Cursor::Draw() const
{
	for (int i = 0; i < click_effect.size(); i++)
	{
		// クリックエフェクト描画処理
		click_effect[i]->Draw();
	}


	//DrawRotaGraph(location.x, location.y, 1.5, 0, cursor_img[0], TRUE);
	DrawRotaGraph((int)location.x,(int)location.y, 1.5, angle, cursor_img[0], TRUE);
	//DrawCircleAA(location.x, location.y, radius, 32, 0x00ffff, FALSE);

}

void Cursor::HitReaction(ObjectBase* character)
{
	switch (character->GetObjectType())
	{
	case ObjectType::in_pausebutton:
		break;

	case ObjectType::pausebutton:
		break;

	case ObjectType::choicebutton:
		break;

	default:
		// se[0]の再生を止める
		StopSoundMem(se);
		break;
	}
	
}
