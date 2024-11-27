#pragma once

#include "AbstractScene.h"
#include "../ObjectFile/PlayerFile/Cursor.h"
#include <vector>

#define BOX_WIDTH  100
#define BOX_HEIGHT 50

class ResultScene : public AbstractScene
{
private:
	Cursor* cursor;
	float x1,y1,x2,y2; // ボタンの座標
	int select; // プレイヤーが選んだメニュー
	int on_button; // カーソルがボタンの上にあるか
	bool is_clear; // クリアしたか？
	int star_num;      // 星の数
	int bgm; // BGMデータ
	bool is_bgm_active; // BGMが流れているか？
	std::vector<int> images;

public:
	ResultScene(bool is_game_clear,int goal_num);
	~ResultScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;

private:
	float DistanceSqrf(float box_x, float box_y, float circle_x, float circle_y);
	bool HitBoxCircle(float box_x, float box_y, Vector2D location, float radius);//四角と円の当たり判定
};