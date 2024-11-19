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
	void Finalize();
	void HitReaction(ObjectBase* character) override; //hitCheckがtrueだったらhitした後の処理をする
	void ChangeWidthHeight(); // 横幅、縦幅の値を変更
	void ChangeBlendNum();    // 画像の透明度の値を変更
};