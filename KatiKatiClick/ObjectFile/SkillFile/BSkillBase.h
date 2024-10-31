#pragma once

#include "../ObjectBase.h"


#define BUTTON_WIDTH  130.0f  // ボタンの幅
#define BUTTON_HEIGHT 100.0f  // ボタンの高さ

enum class BSkillState
{
	close,   // 解放前
	possible,// 解放できる
	standby, // 解放後
	active   // 解放中
};

class BSkillBase : public ObjectBase
{
protected:
	int image;
	BSkillState bskill_state; // ボタンの状態

public:
	BSkillBase();
	~BSkillBase(){};

	// ボタンの状態を返す
	BSkillState GetSkillState() { return bskill_state; }
};