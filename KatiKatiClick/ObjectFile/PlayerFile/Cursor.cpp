#include "Cursor.h"
#include "../../UtilityFile/MouseInput.h"
#include "../../UtilityFile/ResourceManager.h"
#include "DxLib.h"

Cursor::Cursor():se()
{
	location.x = 0.0f;
	location.y = 0.0f;
	object_type = ObjectType::cursor;
	shape = Shape::circle;
	radius = 10.0f;
	can_hit = false;

	ResourceManager* rm = ResourceManager::GetInstance();
	int tmp;
	tmp = rm->GetSounds("Resource/Sounds/Tmouseclick.mp3");
	se[0] = tmp;

	tmp = rm->GetSounds("Resource/Sounds/Thitenemy.mp3");
	se[1] = tmp;
}

Cursor::~Cursor()
{
}

void Cursor::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	int tmp;
	tmp = rm->GetSounds("Resource/Sounds/Tmouseclick.mp3");
	se[0] = tmp;

	tmp = rm->GetSounds("Resource/Sounds/Thitenemy.mp3");
	se[1] = tmp;
}

void Cursor::Update()
{
	int x, y;
	GetMousePoint(&x,&y);
	location.x = (float)x;
	location.y = (float)y;

	

	if (MouseInput::GetMouseState() == eMouseInputState::eClick)
	{
		// クリックSE再生
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

		// クリックエフェクト生成
		click_effect.push_back(new ClickEffect);
		click_effect.back()->SetLocation(location);

		can_hit = true;
	}
	else
	{
		can_hit = false;
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


	DrawCircleAA(location.x, location.y, radius, 32, 0x00ffff, TRUE);
}

void Cursor::HitReaction(ObjectBase* character)
{
	switch (character->GetObjectType())
	{
	case ObjectType::enemy:
		// se[0]の再生を止める
		StopSoundMem(se[0]);
		// クリックSE再生
		PlaySoundMem(se[1], DX_PLAYTYPE_BACK, TRUE);
		break;

	default:
		// se[0]の再生を止める
		StopSoundMem(se[0]);
		break;
	}
}
