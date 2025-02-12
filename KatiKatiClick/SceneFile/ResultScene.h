#pragma once

#include "AbstractScene.h"
#include "../ObjectFile/PlayerFile/Cursor.h"
#include "../FadeFile/Fade.h"
#include <vector>

#define PI    3.1415926535897932384626433832795f  // 円周率

#define STAR_WIDTH  75.0f       // 星の横幅(1,3)
#define STAR_HEIGHT 75.0f       // 星の高さ(1,3)

#define STAR_WIDTH_2  100.0f    // 星の横幅(2)
#define STAR_HEIGHT_2 100.0f    // 星の高さ(2)

#define STAR_X 100.0f            // 星(1)のX座標
#define STAR_Y 250.0f           // 星(1)のY座標

#define STAR_GOLD_X 98.0f            // 星(1)のX座標
#define STAR_GOLD_Y 255.0f           // 星(1)のY座標

class ResultScene : public AbstractScene
{
private:
	Cursor* cursor;              // カーソルオブジェクト
	Fade* fade;                  // フェードオブジェクト

	int select;                  // プレイヤーが選んだメニュー

	bool is_clear;               // クリアしたか？

	int star_num;                // 星の数
	int star_hp[3];              // 星のHP
	float star_x[3];             // 星のX座標
	float star_y[3];             // 星のY座標
	float star_gold_x[3];        // 星のX座標
	float star_gold_y[3];        // 星のY座標
	int star_silver_image;       // 銀の星の画像
	std::vector<int> star_gold_images; // 金の星の画像
	int star_img_num[3];            // 描画する金の星の画像番号
	int fire_image;              // 火の画像
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

	bool anim_start;            // アニメーションスタートしていいか？
	int black_alpha;

	int bgm_volume;  // BGMの音量
	int star_back_se; // 星がはまる時の効果音

	std::vector<int> kirakira_img;  // キラキラ画像
	int kirakira_alpha[4];          // キラキラの透明度
	bool kirakira_alpha_puls[4];       // キラキラの透明度を加算するか？ 
	int kirakira_anim_num[3];          // キラキラアニメーション画像の番号
	int kirakira_anim_cnt[6];          // 次のキラキラアニメーション画像に変えるまでの時間
	double kirakira_extrate;
	bool kirakira_anim_num_puls[6];       // キラキラの透明度を加算するか？ 
	bool star_click[3];                   // 星がクリックされたか？
	int star_unclick_cnt[3];             // 星がクリックされていない時間
	bool star_start_end;             // 最初のアニメーションが終わったか？

	int kirakira_wait_time[3];

	bool overlap_retry_button_flg;	// リトライボタンにカーソルが重なったか？
	bool overlap_title_button_flg;	// タイトルボタンにカーソルが重なったか？

	int stage_number;//選択されたステージの番号

public:
	ResultScene(bool is_game_clear,int goal_num,int enemy_num,int coin_num,int stage_num);
	~ResultScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;

private:

	//四角と円の当たり判定処理
	float DistanceSqrf(float box_x, float box_y, float circle_x, float circle_y);
	bool HitBoxCircle(float box_x, float box_y, float width, float height, Vector2D location, float radius);

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

	// キラキラのアルファ値を変更
	void ChangeKirakiraAlpha();

	// キラキラアニメーション画像変更
	void KirakiraAnimControl();

	// 星がクリックされていない時の処理
	void StarUnClickCount();
};