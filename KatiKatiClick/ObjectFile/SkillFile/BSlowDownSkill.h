#pragma once
#include "BSkillBase.h"

#define SKILL_IMG_NUM 3 // スキルエフェクト画像枚数

class BSlowDownSkill : public BSkillBase
{
private:

public:
	BSlowDownSkill();
	~BSlowDownSkill();

	void Initialize() override;
	void Update()override;
	void Draw() const override;
	void HitReaction(ObjectBase* character) override; //hitCheckがtrueだったらhitした後の処理をする
};