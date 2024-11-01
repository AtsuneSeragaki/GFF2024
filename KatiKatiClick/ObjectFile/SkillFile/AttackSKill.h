#pragma once

#include "SkillBase.h"

class AttackSkill : public SkillBase
{
private:

public:
	AttackSkill();
	~AttackSkill();

	void Update() override;
	void Initialize() override;
	void Draw()const override;
	void Finalize();


};