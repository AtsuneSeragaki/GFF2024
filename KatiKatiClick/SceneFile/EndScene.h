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

public:
	EndScene();
	~EndScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};
