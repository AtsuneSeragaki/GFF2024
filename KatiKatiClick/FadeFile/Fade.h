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

	bool fade_end;//フェードが終わったか
	int wait_time;

	int fade_se;               // シーン切り替え時の効果音

public:
	Fade();
	~Fade();
	void Update();
	void Draw() const;
	bool CheckFadeEnd() { return fade_end; }
};

