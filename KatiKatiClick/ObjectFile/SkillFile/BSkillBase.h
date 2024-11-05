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
	int image; // 画像データ
	int se[2]; // 効果音データ
	BSkillState bskill_state; // ボタンの状態
	bool use_coin; // コイン false:使ってない true:使った

public:
	BSkillBase();
	~BSkillBase(){};

	// ボタンの状態を返す
	BSkillState GetSkillState() { return bskill_state; }

	// ボタンの状態をCloseにする
	void SetSkillStateClose() { bskill_state = BSkillState::close; }

	// ボタンの状態をpossibleにする
	void SetSkillStatePossible() { bskill_state = BSkillState::possible; }

	// コインを使ったかフラグの値を返す
	bool GetUseCoinFlg() { return use_coin; }

	// コインを使ったかフラグの値をfalseにする
	void SetUseCoinFlg() { use_coin = false; }
};