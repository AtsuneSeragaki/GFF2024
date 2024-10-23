#pragma once
#include "SkillBase.h"

#define SKILL_IMG_NUM 3 // スキルエフェクト画像枚数

class AttackSkill : public SkillBase
{
private:
	int effect_img[SKILL_IMG_NUM];  // スキルエフェクト画像

public:
	AttackSkill();
	~AttackSkill();

	void Update()override;
	void Draw() const override;
	void HitReaction(ObjectBase* character) override; //hitCheckがtrueだったらhitした後の処理をする
};