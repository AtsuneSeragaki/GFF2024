#pragma once
#include "ObjectBase.h"
class EnemyBase :
    public ObjectBase
{
private:
    int hp;//体力
	float speed;//速さ

public:
	void Update()override;
	void Draw() const override;
	void HitReaction(ObjectBase* character) override; //hitCheckがtrueだったらhitした後の処理をする

};

