#pragma once
#include "SkillBase.h"

class SlowDownSkill : public SkillBase
{
protected:

public:
	SlowDownSkill();
	~SlowDownSkill();

	void Update()override;
	void Draw() const override;
	void HitReaction(ObjectBase* character) override; //hitCheckがtrueだったらhitした後の処理をする
};