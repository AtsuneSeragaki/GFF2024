#pragma once

#include "AbstractScene.h"
#include "../ObjectFile/PlayerFile/Cursor.h"

#define BOX_WIDTH  100
#define BOX_HEIGHT 50

class ResultScene : public AbstractScene
{
private:
	Cursor* cursor;
	float x,y; // ボタンの座標
	bool select; // プレイヤーが選んだメニュー
	bool on_button; // カーソルがボタンの上にあるか

public:
	ResultScene();
	~ResultScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;

private:
	float DistanceSqrf(float box_x, float box_y, float circle_x, float circle_y);
	bool HitBoxCircle(float box_x, float box_y, Vector2D location, float radius);//四角と円の当たり判定
};