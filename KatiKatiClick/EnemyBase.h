#pragma once
#include "ObjectBase.h"
class EnemyBase :
    public ObjectBase
{
protected:
    int hp;//体力
	float speed;//速さ

public:
	void Update()override = 0;
	void Draw() const override=0;
	void HitReaction(ObjectBase* character) override=0; //hitCheckがtrueだったらhitした後の処理をする

};

