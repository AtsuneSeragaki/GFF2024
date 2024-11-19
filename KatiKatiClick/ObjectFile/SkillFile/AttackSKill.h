#pragma once

#include "SkillBase.h"
#include <vector>

class AttackSkill : public SkillBase
{
private:
	std::vector<int> effect_img;
	int effect_num;
	bool max_flg;  // MAXの大きさまで大きく false:なってない true:なった
	int blend_num; // 画像の透明度の値

public:
	AttackSkill();
	~AttackSkill();

	void Update() override;
	void Initialize() override;
	void Draw()const override;
	void Finalize();
	void HitReaction(ObjectBase* character) override; //hitCheckがtrueだったらhitした後の処理をする
	void ChangeEffectImage(); // エフェクト画像入れ替え
	void ChangeWidthHeight(); // 横幅、縦幅の値を変更
	void ChangeBlendNum();   // 画像の透明度の値を変更
};