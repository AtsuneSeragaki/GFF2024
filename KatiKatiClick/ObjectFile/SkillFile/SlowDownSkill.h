#pragma once

#include "SkillBase.h"

class SlowDownSkill : public SkillBase
{
private:

public:
	SlowDownSkill();
	~SlowDownSkill();

	void Update() override;
	void Initialize() override;
	void Draw()const override;
	void Finalize() override;

};