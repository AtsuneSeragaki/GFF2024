#pragma once

#include "AbstractScene.h"
#include "../ObjectFile/PlayerFile/Cursor.h"
#include "../OpeningFile/OpeningAnim.h"

//#define BOX_WIDTH  130
//#define BOX_HEIGHT 70

#define BUTTON_BOX_WIDTH  130
#define BUTTON_BOX_HEIGHT 70

class TitleScene : public AbstractScene
{
private:
	Cursor* cursor;
	OpeningAnim* opening_anim;
	//float x1, x2, y1, y2; // ボタンの座標
	//float x1, x2, y1, y2; // ボタンの座標
	int select; // プレイヤーが選んだメニュー
	//int on_button; // カーソルがボタンの上にあるか
	int bgm; // BGMデータ
	bool is_bgm_active; // BGMが流れているか？

	std::vector<int> cloud_img;//雲の画像
	std::vector<int> titlelogo_img;//タイトルロゴの画像
	std::vector<int> start_button_img;//スタートボタンの画像
	std::vector<int> end_button_img;//エンドボタンの画像

	int start_img_num;			// スタートボタン画像番号
	int end_img_num;			// エンドボタン画像番号
	int button_anim_count;		// ボタン押下アニメションカウント

	float start_x;				// スタートボタンのx座標
	float start_y;				// スタートボタンのy座標
	float end_x;				// エンドボタンのx座標
	float end_y;				// エンドボタンのy座標

	bool change_screen_flg;		// 画面遷移しても良いか？

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

