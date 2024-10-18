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

	static bool now_key;//現在の入力
	static bool old_key;//昔の入力

public:
	static void Update();
};
