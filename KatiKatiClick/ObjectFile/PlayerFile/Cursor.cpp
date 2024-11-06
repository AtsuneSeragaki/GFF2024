#include "Cursor.h"
#include "../../UtilityFile/MouseInput.h"
#include "../../UtilityFile/ResourceManager.h"
#include "DxLib.h"

Cursor::Cursor():se(0)
{
	location.x = 0.0f;
	location.y = 0.0f;
	object_type = ObjectType::cursor;
	shape = Shape::circle;
	radius = 10.0f;
	can_hit = false;

	ResourceManager* rm = ResourceManager::GetInstance();
	int tmp;
	tmp = rm->GetSounds("Resource/Sounds/Click/mouse.mp3");
	se = tmp;

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
	int x, y;
	GetMousePoint(&x,&y);
	location.x = (float)x;
	location.y = (float)y;

	if (MouseInput::GetMouseState() == eMouseInputState::eClick)
	{
		// クリックSE再生
		PlaySoundMem(se, DX_PLAYTYPE_BACK, TRUE);
		can_hit = true;
	}
	else
	{
		can_hit = false;
	}
}

void Cursor::Draw() const
{
	DrawCircleAA(location.x, location.y, radius, 32, 0x00ffff, TRUE);
}

void Cursor::HitReaction(ObjectBase* character)
{
	// 効果音の再生を止める
	StopSoundMem(se);
}
