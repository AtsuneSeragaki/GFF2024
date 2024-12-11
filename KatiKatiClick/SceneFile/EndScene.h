#pragma once

#include "AbstractScene.h"
#include "../ObjectFile/EnemyFile/CrackEnemy.h"

class EndScene : public AbstractScene
{
private:
	int cnt;
	int bgm; // BGMデータ
	bool is_bgm_active; // BGMが流れているか？

	CrackEnemy* crackenemy; // 敵のオブジェクト

	std::vector<int> cloud_img;			//雲の画像

	int end_img[2];

	int woman_img;

	int black_alpha;
	bool anim_start;            // アニメーションスタートしていいか？

	int text_cnt;

	bool text_flg;

public:
	EndScene();
	~EndScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};
