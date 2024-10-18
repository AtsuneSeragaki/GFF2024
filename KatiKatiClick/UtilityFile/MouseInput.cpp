#include "MouseInput.h"
#include "DxLib.h"

bool MouseInput::now_key = false;
bool MouseInput::old_key = false;

void MouseInput::Update()
{
	old_key=now_key;

	//マウスの左ボタンが押されているかチェック
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		//押されてる
		now_key = true;
	}
	else
	{
		//押されていない
		now_key = false;
	}
	
}
