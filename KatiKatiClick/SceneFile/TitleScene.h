#pragma once

#include "AbstractScene.h"
#include "../UtilityFile/MouseInput.h"

#define BOX_WIDTH  100
#define BOX_HEIGHT 100

class TitleScene : public AbstractScene
{
private:
	MouseInput* mouseinput;
	float x1, x2, y1, y2; // ボタンの座標
	int select; // プレイヤーが選んだメニュー

public:
	TitleScene();
	~TitleScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;

private:
	float DistanceSqrf(float box_x, float box_y, float circle_x, float circle_y);
	bool HitBoxCircle(float box_x,float box_y,Vector2D location,float radius);//四角と円の当たり判定
};

