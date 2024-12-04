#pragma once
#include "BSkillBase.h"
#include <vector>

class BSlowDownSkill : public BSkillBase
{
private:
	std::vector<int> button_img; // ボタン画像
		//色を変える用
	int red;//RGBのR
	int green;//RGBのG
	int blue;//RGBのB
	int webs_alpha;

public:
	BSlowDownSkill();
	~BSlowDownSkill();

	void Initialize() override;
	void Update()override;
	void Draw() const override;
	void Finalize();
	void HitReaction(ObjectBase* character) override; //hitCheckがtrueだったらhitした後の処理をする

	void ChangeImage() override;

	void ChangeButtonSize();
};