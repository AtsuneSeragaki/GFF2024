#pragma once

#include "../ObjectBase.h"

#define BUTTON_WIDTH  50  // ボタンの幅
#define BUTTON_HEIGHT 50  // ボタンの高さ

#define BUTTON_IMG_NUM 3  // ボタン画像の枚数

enum class SkillState
{
	close,   // 解放前
	possible,// 解放できる
	standby, // 解放後
	active   // 解放中
};

class SkillBase : public ObjectBase
{
protected:
	int button_img[BUTTON_IMG_NUM]; // ボタン画像
	int button_x;      // ボタンX座標
	int button_y;      // ボタンY座標
	SkillState skill_state; // ボタンの状態

public:
	SkillBase();
	~SkillBase(){};

	// ボタンの状態を返す
	SkillState GetSkillState() { return skill_state; }

protected:
	int coin;  // コインの枚数（テスト用）
};