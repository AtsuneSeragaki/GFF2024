#include "MouseInput.h"
#include "DxLib.h"

int MouseInput::now_key = 0;
int MouseInput::old_key = 0;
eMouseInputState MouseInput::mouse_input_state = eMouseInputState::eNone;
Vector2D MouseInput::location = 0;

void MouseInput::Update()
{

	int x, y;
	GetMousePoint(&x, &y);
	location.x = (float)x;
	location.y = (float)y;


	old_key = now_key;

	//マウスの左ボタンが押されているかチェック
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		//押されてる
		now_key = 1;
	}
	else
	{
		//押されていない
		now_key = 0;
	}

	//クリックした瞬間を取る
	if (now_key == 1 && old_key == 0)
	{
		mouse_input_state = eMouseInputState::eClick;
	}

	//ずっと押し続けているか
	if (now_key == 1 && old_key == 1)
	{
		mouse_input_state = eMouseInputState::eHold;
	}

	//何も押してないか
	if (now_key == 0 && old_key == 0)
	{
		mouse_input_state = eMouseInputState::eNone;
	}

}

eMouseInputState MouseInput::GetMouseState()
{
	return mouse_input_state;
}

Vector2D MouseInput::GetMouseLocation()
{
	return location;
}
