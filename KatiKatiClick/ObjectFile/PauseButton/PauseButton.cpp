#include "PauseButton.h"
#include "DxLib.h"

PauseButton::PauseButton()
{
	location.x = 300.0f;
	location.y = 20.0f;
	can_hit = true;
	object_type = ObjectType::pausebutton;
	shape = Shape::square;
	width = 30.0f;
	height = 50.0f;

	is_pause = false;
}

PauseButton::~PauseButton()
{

}

void PauseButton::Initialize()
{

}

void PauseButton::Update()
{

}

void PauseButton::Draw() const
{
	DrawBoxAA(location.x - 10, location.y - 10, location.x + height, location.y + width, 0xc0c0c0, TRUE);
	DrawFormatStringF(location.x, location.y, 0x000000, "PAUSE");
}

void PauseButton::HitReaction(ObjectBase* character)
{
	if (character->GetObjectType() == ObjectType::cursor)
	{
		if (is_pause == false)
		{
			// 一時停止にする
			is_pause = true;
		}
		else
		{
			// 一時停止を解除する
			is_pause = false;
		}
	}
}

bool PauseButton::GetPauseFlg() const
{
	return is_pause;
}
