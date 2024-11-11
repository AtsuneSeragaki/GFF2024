#include "PauseButton.h"
#include "DxLib.h"

PauseButton::PauseButton()
{
	location.x = 0.0f;
	location.y = 0.0f;
	can_hit = true;
	object_type = ObjectType::pausebutton;
	shape = Shape::square;
	width = 50.0f;
	height = 40.0f;

	is_pause = false;
	cursor_x = 0.0f;
	cursor_y = 0.0f;
}

PauseButton::~PauseButton()
{

}

void PauseButton::Initialize()
{

}

void PauseButton::Update()
{
	//if (is_pause)
	//{
	//	// カーソル位置の更新
	//	int x, y;
	//	GetMousePoint(&x, &y);
	//	cursor_x = (float)x;
	//	cursor_y = (float)y;

	//}
}

void PauseButton::Draw() const
{
	DrawBoxAA(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, 0xc0c0c0, TRUE);
	// DrawFormatStringF(location.x - 20.0f, location.y - 10.0f, 0x000000, "PAUSE");

	//if (is_pause)
	//{
	//	// カーソル仮表示
	//	DrawCircleAA(location.x, location.y, radius, 32, 0x00ffff, TRUE);
	//}
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
