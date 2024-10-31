#include "PauseButton.h"
#include "DxLib.h"

PauseButton::PauseButton()
{
	location.x = 300.0f;
	location.y = 20.0f;
	object_type = ObjectType::pausebutton;
	width = 30.0f;
	height = 50.0f;
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

}