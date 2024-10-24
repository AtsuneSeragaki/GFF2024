#pragma once

enum class eMouseInputState
{
	eNone,//何も押してない
	eClick,//クリックしている
	eHold,//長押し
};

class MouseInput
{
private:
	//マウスが押されているか

	static int now_key;//現在の入力
	static int old_key;//昔の入力
	static eMouseInputState mouse_input_state;

public:
	static void Update();
	static eMouseInputState GetMouseState();
};
