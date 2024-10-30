#pragma once

#include "../ObjectBase.h"

#define BUTTON_WIDTH  160.0f  // ボタンの幅
#define BUTTON_HEIGHT 100.0f  // ボタンの高さ

#define BUTTON_IMG_NUM 3  // ボタン画像の枚数

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
	int button_img[BUTTON_IMG_NUM]; // ボタン画像
	BSkillState bskill_state; // ボタンの状態

public:
	BSkillBase();
	~BSkillBase(){};

	// ボタンの状態を返す
	BSkillState GetSkillState() { return bskill_state; }
};