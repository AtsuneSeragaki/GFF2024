#pragma once

#include "AbstractScene.h"
#include "../ObjectFile/PlayerFile/Cursor.h"
#include <vector>

#define BOX_WIDTH  100.0f
#define BOX_HEIGHT 50.0f

#define STAR_WIDTH 60.0f
#define STAR_HEIGHT 60.0f

#define STAR_WIDTH_2 100.0f
#define STAR_HEIGHT_2 100.0f

#define STAR_X 98.0f
#define STAR_Y 235.0f

#define PI    3.1415926535897932384626433832795f

class ResultScene : public AbstractScene
{
private:
	Cursor* cursor;
	float x1,y1,x2,y2; // ボタンの座標
	int select; // プレイヤーが選んだメニュー
	int on_button; // カーソルがボタンの上にあるか
	bool is_clear; // クリアしたか？
	int star_num;      // 星の数
	int star_hp[3];
	float star_x[3];
	float star_y[3];
	int bgm; // BGMデータ
	bool is_bgm_active; // BGMが流れているか？
	int star_images[2];
	int fire_image;
	int pizza_image;
	double pizza_angle;
	double star_gold_extrate[3]; // 画像の拡大率
	double star_angle[3];
	double star_extrate[3];
	bool star_gold[3];


public:
	ResultScene(bool is_game_clear,int goal_num);
	~ResultScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;

private:
	float DistanceSqrf(float box_x, float box_y, float circle_x, float circle_y);
	bool HitBoxCircle(float box_x, float box_y, float width, float height, Vector2D location, float radius);//四角と円の当たり判定
	void ChangePizzaAngle();
	void HitCheck();
	void StarMove();
};