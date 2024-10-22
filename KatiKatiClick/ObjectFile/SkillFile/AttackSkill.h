#pragma once
#include "SkillBase.h"

enum class SkillState
{
	standby,
	active,
};

class AttackSkill : public SkillBase
{
private:

public:
	AttackSkill();
	~AttackSkill();

	void Update()override;
	void Draw() const override;
	void HitReaction(ObjectBase* character) override; //hitCheckがtrueだったらhitした後の処理をする
};