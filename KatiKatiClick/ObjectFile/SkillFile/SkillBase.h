#pragma once

#include "../ObjectBase.h"

class SkillBase : public ObjectBase
{
protected:
	bool disp_flg; // 表示 false:しない true:する

public:
	SkillBase();
	~SkillBase(){};

	bool GetDispFlg() { return disp_flg; }
	void SetDispFlg(bool flg) { disp_flg = flg; }
};
