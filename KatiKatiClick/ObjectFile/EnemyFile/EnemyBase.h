#pragma once
#include "../ObjectBase.h"
#include "DxLib.h"

enum class State
{
	wait,//動き出すまでの待機
	move,//動く
	goal,//ゴールしたとき
	death,//倒された時
};

class EnemyBase :
    public ObjectBase
{
protected:
	State state;
    int hp;//体力
	float speed;//速さ
	bool hit_cursor;//カーソルに当たった
	int wait_time;//動くまでの時間
	int se[2]; // 効果音
	bool can_create_mini;//小さいのを作る

public:
	EnemyBase()
	{
		wait_time = 0;
		hp = 0;
		speed = 0.0f;
		hit_cursor = false;
		state = State::wait;
		can_create_mini = false;
		se[0] = 0;
		se[1] = 0;
	}
	~EnemyBase(){};

	void Initialize() override = 0;
	void Update()override = 0;
	void Draw() const override=0;
	void HitReaction(ObjectBase* character) override=0; //hitCheckがtrueだったらhitした後の処理をする
	bool GetHitCursor() { return hit_cursor; }
	void SetFalseHitCursor() { hit_cursor = false; }
	void SetWaitTime(int set_time) { wait_time = set_time; }
	bool GetCanCreateMini() { return can_create_mini; }
	void SetSize(float set_width, float set_height)
	{
		width = set_width;
		height = set_height;
	}
	void SetHp(int set_hp) { hp = set_hp; }
	void StopCreateMini() { can_create_mini = false; }
};

