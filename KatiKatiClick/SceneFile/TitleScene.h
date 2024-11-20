#pragma once

#include "AbstractScene.h"

#define BOX_WIDTH  100
#define BOX_HEIGHT 100

class TitleScene : public AbstractScene
{
private:
	int x1, x2, y1, y2; // ボタンの座標

public:
	TitleScene();
	~TitleScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};

