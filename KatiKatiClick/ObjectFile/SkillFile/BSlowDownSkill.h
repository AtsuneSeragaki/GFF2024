#pragma once
#include "BSkillBase.h"
#include <vector>

class BSlowDownSkill : public BSkillBase
{
private:
	std::vector<int> button_img; // ボタン画像

public:
	BSlowDownSkill();
	~BSlowDownSkill();

	void Initialize() override;
	void Update()override;
	void Draw() const override;
	void HitReaction(ObjectBase* character) override; //hitCheckがtrueだったらhitした後の処理をする
};