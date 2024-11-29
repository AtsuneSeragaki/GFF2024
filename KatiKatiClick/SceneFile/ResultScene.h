#pragma once

#include "AbstractScene.h"
#include "../ObjectFile/PlayerFile/Cursor.h"
#include <vector>

#define PI    3.1415926535897932384626433832795f  // 円周率

#define BOX_WIDTH  100.0f       // ボタンの幅
#define BOX_HEIGHT 50.0f        // ボタンの高さ

#define STAR_WIDTH  60.0f       // 星の横幅(1,3)
#define STAR_HEIGHT 60.0f       // 星の高さ(1,3)

#define STAR_WIDTH_2  100.0f    // 星の横幅(2)
#define STAR_HEIGHT_2 100.0f    // 星の高さ(2)

#define STAR_X 98.0f            // 星(1)のX座標
#define STAR_Y 235.0f           // 星(1)のY座標

class ResultScene : public AbstractScene
{
private:
	Cursor* cursor;              // カーソルオブジェクト
	float x1,y1,x2,y2;           // ボタンの座標
	int select;                  // プレイヤーが選んだメニュー
	int on_button;               // カーソルがボタンの上にあるか
	bool is_clear;               // クリアしたか？
	int star_num;                // 星の数
	int star_hp[3];              // 星のHP
	float star_x[3];             // 星のX座標
	float star_y[3];             // 星のY座標
	float star_gold_x[3];             // 星のX座標
	float star_gold_y[3];             // 星のY座標
	int star_images[2];          // 星の画像
	int fire_image;              // 火の画像
	int pizza_image;             // ピザの画像
	double pizza_angle;          // ピザの角度
	double star_gold_extrate[3]; // 金の星の拡大率
	double star_angle[3];        // 星の角度
	double star_extrate[3];      // 銀の星の拡大率
	bool star_gold[3];           // 金の星か？
	bool star_back[3];           // 星が画面外に出て帰ってくるか？
	int bgm;                     // BGMデータ
	bool is_bgm_active;          // BGMが流れているか？
	float fire_extrate[3];       // 火のY座標
	bool is_fire_max[3];         // 火は最大サイズか？
	float star_move[3];          // 星の移動量を少しずつ変える
	int star_wait_time[3];       // 火がついた後の星の待機時間
	float fire_x[3], fire_y[3];  // 火の表示位置(星の中心座標に足す分)
	int cnt;

public:
	ResultScene(bool is_game_clear,int goal_num);
	~ResultScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;

private:

	//四角と円の当たり判定処理
	void HitCheck();
	float DistanceSqrf(float box_x, float box_y, float circle_x, float circle_y);
	bool HitBoxCircle(float box_x, float box_y, float width, float height, Vector2D location, float radius);

	// ピザの角度を変更する処理
	void ChangePizzaAngle();
	
	// プレイヤーにクリックされた時の星の動き処理
	void StarMove();
};