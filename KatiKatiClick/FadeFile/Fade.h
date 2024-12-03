#pragma once
#include "../ObjectFile/ObjectBase.h"
#include <vector>

class Fade
{
private:
	std::vector<int> enm_img;

	float upperbox_down_y;//上のボックスを下げるよう
	float bottombox_up_y;//下のボックス上げる用
	float rightbox_shiftx;//右のボックス左に動かす用
	float leftbox_shiftx;//左のボックス右に動かす用

	bool enm_display_flg;//エネミー画像表示するか

public:
	Fade();
	~Fade();
	void Update();
	void Draw() const;
};

