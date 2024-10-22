#pragma once

#include "../ObjectBase.h"

class SkillBase : public ObjectBase
{
protected:

public:
	SkillBase();
	~SkillBase(){};

	void Update()override = 0;
	void Draw() const override = 0;
	void HitReaction(ObjectBase* character) override = 0; //hitCheckがtrueだったらhitした後の処理をする
};