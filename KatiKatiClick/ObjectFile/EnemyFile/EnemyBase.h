#pragma once
#include "../ObjectBase.h"
#include "DxLib.h"

enum class State
{
	move,
	goal,
	death,
};

class EnemyBase :
    public ObjectBase
{
protected:
	State state;
    int hp;//体力
	float speed;//速さ
	bool hit_cursor;//カーソルに当たった


public:
	EnemyBase()
	{
		hp = 0;
		speed = 0.0f;
		hit_cursor = false;
		state = State::move;
	}
	~EnemyBase(){};

	void Initialize() override = 0;
	void Update()override = 0;
	void Draw() const override=0;
	void HitReaction(ObjectBase* character) override=0; //hitCheckがtrueだったらhitした後の処理をする
	bool GetHitCursor() { return hit_cursor; }
	void SetFalseHitCursor() { hit_cursor = false; }
	
};

