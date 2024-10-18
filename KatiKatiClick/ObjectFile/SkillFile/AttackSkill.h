#pragma once
#include "SkillBase.h"

class AttackSkill : public SkillBase
{
protected:

public:
	AttackSkill();
	~AttackSkill();

	void Update()override;
	void Draw() const override;
	void HitReaction(ObjectBase* character) override; //hitCheckがtrueだったらhitした後の処理をする
};