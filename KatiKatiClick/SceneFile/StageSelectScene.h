#pragma once

#include "AbstractScene.h"
#include "../ObjectFile/PlayerFile/Cursor.h"
#include "../FadeFile/Fade.h"
#include <vector>

#define STAGE_BUTTON_WIDTH   200
#define STAGE_BUTTON_HEIGHT  100 

class StageSelectScene : public AbstractScene
{
private:
	class Fade* fade;
	class Cursor* cursor;
	int select;							// プレイヤーが選んだメニュー
	int bgm;							// BGMデータ
	bool is_bgm_active;					// BGMが流れているか？
	int bgm_volume;                     // BGMの音量

	std::vector<int> title_button_img;	// タイトルボタンの画像
	int title_img_num;			        // タイトルボタン画像番号
	int change_wait_time;		        // シーン切り替えの待ち時間
	float title_x;				        // タイトルボタンのx座標
	float title_y;				        // タイトルボタンのy座標
	bool change_screen_flg;		        // 画面遷移しても良いか？
	bool overlap_title_button_flg;	    // タイトルボタンにカーソルが重なったか？

	std::vector<int> stage1_button_img; // ステージ1ボタンの画像
	std::vector<int> stage2_button_img; // ステージ2ボタンの画像
	std::vector<int> stage3_button_img; // ステージ3ボタンの画像

	int stage1_img_num;			        // ステージ1ボタン画像番号
	int stage2_img_num;			        // ステージ2ボタン画像番号
	int stage3_img_num;			        // ステージ3ボタン画像番号

	bool overlap_stage1_button_flg;	    // ステージ1ボタンにカーソルが重なったか？
	bool overlap_stage2_button_flg;	    // ステージ2ボタンにカーソルが重なったか？
	bool overlap_stage3_button_flg;	    // ステージ3ボタンにカーソルが重なったか？

	float stage1_x;                     // ステージ1ボタンのx座標
	float stage1_y;                     // ステージ1ボタンのy座標
	float stage2_x;                     // ステージ2ボタンのx座標
	float stage2_y;                     // ステージ2ボタンのy座標
	float stage3_x;                     // ステージ3ボタンのx座標
	float stage3_y;                     // ステージ4ボタンのy座標

	int text_img;                       // ステージ選択文字の画像               

public:
	StageSelectScene();
	~StageSelectScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;

	//四角と円の当たり判定処理
	float DistanceSqrf(float box_x, float box_y, float circle_x, float circle_y);
	bool HitBoxCircle(float box_x, float box_y, float width, float height, Vector2D location, float radius);

	// ボタンとカーソルの当たり判定
	void ButtonHitCheck();

	// ボタン押下アニメション処理
	void ButtonAnimation();
};