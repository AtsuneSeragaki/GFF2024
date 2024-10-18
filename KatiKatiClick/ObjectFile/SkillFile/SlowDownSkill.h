#pragma once
#include "ObjectBase.h"

class SlowDownSkill :
	public ObjectBase
{
protected:

public:
	void Update()override;
	void Draw() const override;
	void HitReaction(ObjectBase* character) override; //hitCheckがtrueだったらhitした後の処理をする
};