#pragma once

#include "../ObjectBase.h"
#include <vector>

class SkillBase : public ObjectBase
{
protected:
	bool disp_flg; // 表示 false:しない true:する
	int cnt;
	int image;
	std::vector<int> effect_img;
	int effect_num;
	bool max_flg;  // MAXの大きさまで大きく false:なってない true:なった
	int blend_num; // 画像の透明度の値

public:
	SkillBase();
	~SkillBase(){};

	bool GetDispFlg() { return disp_flg; }
	void SetDispFlg(bool flg) { disp_flg = flg; }
};
