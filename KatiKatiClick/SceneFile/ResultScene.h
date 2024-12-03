#pragma once

#include "AbstractScene.h"
#include "../ObjectFile/PlayerFile/Cursor.h"
#include <vector>

#define PI    3.1415926535897932384626433832795f  // 円周率

//#define BOX_WIDTH  100.0f       // ボタンの幅
//#define BOX_HEIGHT 50.0f        // ボタンの高さ

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
	//float x1,y1,x2,y2;           // ボタンの座標
	int select;                  // プレイヤーが選んだメニュー
	//int on_button;               // カーソルがボタンの上にあるか
	bool is_clear;               // クリアしたか？
	int star_num;                // 星の数
	int star_hp[3];              // 星のHP
	float star_x[3];             // 星のX座標
	float star_y[3];             // 星のY座標
	float star_gold_x[3];        // 星のX座標
	float star_gold_y[3];        // 星のY座標
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
	float cnt[3];                // 星が戻ってくるときのアニメーション用カウント
	int star_click_se[2];        // 星を叩いた時の効果音
	float star_gold_width[3];    // 金の星の横幅
	float star_gold_height[3];   // 金の星の高さ

	std::vector<int> retry_button_img;	// リトライボタンの画像
	std::vector<int> title_button_img;	// タイトルボタンの画像

	int retry_img_num;			// リトライボタン画像番号
	int title_img_num;			// タイトルボタン画像番号
	int change_wait_time;		// シーン切り替えの待ち時間

	float retry_x;				// リトライボタンのx座標
	float retry_y;				// リトライボタンのy座標
	float title_x;				// タイトルボタンのx座標
	float title_y;				// タイトルボタンのy座標

	bool change_screen_flg;		// 画面遷移しても良いか？

	bool is_star_min[3];        // 星のサイズが最小か？

	int fire_se;                // 点火する時の音

	std::vector<int> gstar_click_effect;  // 金の星をクリックしたときに出るエフェクト画像

	int gstar_effect_img[3];          // 金の星エフェクト画像

	bool is_gstar_click[3];        // 金の星がクリックされたか

	int gstar_effect_num[3];       // 金の星表示するエフェクト画像の番号

	int gstar_effect_change_num[3];    // 金の星表示するエフェクト画像の切り替え時間

	double gstar_effect_extrate[3];    // 金の星表示するエフェクト画像の拡大率

	int result_img;                // リザルト画像

	std::vector<int> num_img;      // 数字画像

	int game_clear_img;            // ゲームクリア画像	

	int game_over_img;             // ゲームオーバー画像

	int kill_enemy_num;            // 倒した敵の数

	int get_coin_num;              // 獲得したコインの数

	int kill_enemy_num_2;          // 倒した敵の数増える用

	int get_coin_num_2;            // 獲得したコインの数増える用

	int score;                     // スコア

	int score_2;                   // スコア増える用

public:
	ResultScene(bool is_game_clear,int goal_num,int enemy_num,int coin_num);
	~ResultScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;

private:

	//四角と円の当たり判定処理
	float DistanceSqrf(float box_x, float box_y, float circle_x, float circle_y);
	bool HitBoxCircle(float box_x, float box_y, float width, float height, Vector2D location, float radius);

	// ピザの角度を変更する処理
	void ChangePizzaAngle();
	
	// 星とカーソルの当たり判定
	void StarHitCheck();

	// プレイヤーにクリックされた時の星の動き処理
	void StarMove();

	// 星が帰ってくるときのアニメーション処理
	void StarBackAnim(int i);

	// ボタンとカーソルの当たり判定
	void ButtonHitCheck();

	// ボタン押下アニメション処理
	void ButtonAnimation();

	// ボタンの描画
	void DrawButton() const;

	// 星がはまるアニメーション用
	void ChangeStarSize(int i);

	// 金の星をクリックしたときに出るエフェクト画像の切り替え
	void GStarClickEffect();

	// 数字増やす
	void AddNum();
};