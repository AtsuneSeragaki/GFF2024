#pragma once

#include "AbstractScene.h"

class EndScene : public AbstractScene
{
private:
	int cnt;
	int bgm; // BGMデータ
	bool is_bgm_active; // BGMが流れているか？

public:
	EndScene();
	~EndScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};
