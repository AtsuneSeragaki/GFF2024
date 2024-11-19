#pragma once
#include "BSkillBase.h"
#include <vector>

class BAttackSkill : public BSkillBase
{
private:
	std::vector<int> button_img; // ボタン画像

public:
	BAttackSkill();
	~BAttackSkill();

	void Initialize() override;
	void Update()override;
	void Draw() const override;
	void Finalize();
	void HitReaction(ObjectBase* character) override; //hitCheckがtrueだったらhitした後の処理をする

	void ChangeImage() override;
};