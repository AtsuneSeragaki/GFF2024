#pragma once

#include "../ObjectBase.h"

#define BUTTON_WIDTH  130.0f  // ボタンの幅
#define BUTTON_HEIGHT 100.0f  // ボタンの高さ

enum class BSkillState
{
	close,       // 解放できない状態
	possible,    // 解放できる状態
	active       // スキル使用中
};

class BSkillBase : public ObjectBase
{
protected:
	int image; // 画像データ
	int effect_image; // スキルボタンが溜まる時のエフェクト画像
	int se[3]; // 効果音データ
	BSkillState bskill_state; // ボタンの状態
	bool use_coin; // コイン false:使ってない true:使った
	bool hit_cursor; // カーソルがボタンの上に false:ない true:ある
	int effect_x, effect_y;
	int effect_width, effect_height;

public:
	BSkillBase();
	~BSkillBase(){};

	// スキルボタンの状態によって画像を変える処理
	virtual void ChangeImage() = 0;

	// hit_cursorの値を設定
	void SetHitCursorFlg(bool flg);

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