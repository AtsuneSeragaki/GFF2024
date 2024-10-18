#pragma once
#include "../ObjectBase.h"
#include "DxLib.h"
class EnemyBase :
    public ObjectBase
{
protected:
    int hp;//体力
	float speed;//速さ

public:
	EnemyBase()
	{
		hp = 0;
		speed = 0.0f;
	}
	~EnemyBase(){};

	void Update()override = 0;
	void Draw() const override=0;
	void HitReaction(ObjectBase* character) override=0; //hitCheckがtrueだったらhitした後の処理をする

};

