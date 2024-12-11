#pragma once

#include "AbstractScene.h"
#include "../ObjectFile/PlayerFile/Cursor.h"
#include "../OpeningFile/OpeningAnim.h"
#include "../FadeFile/Fade.h"

class TitleScene : public AbstractScene
{
private:
	Fade* fade;
	Cursor* cursor;
	OpeningAnim* opening_anim;
	int select;							// プレイヤーが選んだメニュー
	int bgm;							// BGMデータ
	bool is_bgm_active;					// BGMが流れているか？

	std::vector<int> cloud_img;			//雲の画像
	std::vector<int> titlelogo_img;		//タイトルロゴの画像
	std::vector<int> play_button_img;	//プレイボタンの画像
	std::vector<int> end_button_img;	//エンドボタンの画像
	std::vector<int> select_img;	//選択の画像
	std::vector<int> star_img;	//選択の画像

	int star_cnt;
	int star_alpha[20];

	int play_img_num;			// プレイボタン画像番号
	int end_img_num;			// エンドボタン画像番号
	int change_wait_time;		// シーン切り替えの待ち時間

	float play_x;				// プレイボタンのx座標
	float play_y;				// プレイボタンのy座標
	float end_x;				// エンドボタンのx座標
	float end_y;				// エンドボタンのy座標

	bool change_screen_flg;		// 画面遷移しても良いか？

	bool anim_start;            // アニメーションスタートしていいか？
	int black_alpha;

	int bgm_volume;  // BGMの音量
	
	Vector2D cloud_pos;
	Vector2D cloud_pos2;

	bool overlap_play_button_flg;	// プレイボタンにカーソルが重なったか？
	bool overlap_end_button_flg;	// エンドボタンにカーソルが重なったか？
	Vector2D star_pos[20];
	Vector2D star_size[20];

	
public:
	TitleScene();
	~TitleScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;

	static bool is_fade;        // フェードしてきたか？

private:
	float DistanceSqrf(float box_x, float box_y, float circle_x, float circle_y);
	bool HitBoxCircle(float box_x,float box_y,Vector2D location,float radius);//四角と円の当たり判定
	void ButtonAnimation();			// ボタン押下アニメション処理
	void DrawButton() const;		// ボタンの描画
	void ButtonHitCheck();			// ボタンとカーソルの当たり判定
	void MoveCloud();				// 雲の移動

	void StarVisible();				//星の表示
};

