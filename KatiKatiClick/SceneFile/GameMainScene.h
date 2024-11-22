#pragma once
#include "AbstractScene.h"
#include "DxLib.h"
#include "../ObjectFile/EnemyFile/CrackEnemy.h"
#include "../ObjectFile/EnemyFile/SplitEnemy.h"
#include "../ObjectFile/EnemyFile/BurstEnemy.h"
#include "../ObjectFile/EnemyFile/SnakeEnemy.h"
#include "../ObjectFile/EnemyFile/FrogEnemy.h"
#include "../ObjectFile/PlayerFile/Cursor.h"
#include "../ObjectFile/WallFile/Wall.h"
#include "../UtilityFile/Define.h"
#include "../ObjectFile/CoinFile/Coin.h"
#include "../UtilityFile/Geometry.h"
#include "../ObjectFile/UIFile/UICoins.h"
#include "../ObjectFile/UIFile/UITimer.h"
#include "../ObjectFile/PauseFile/PauseButtonFile/PauseButton.h"
#include "../ObjectFile/ShapeZoneFile/HitCircleZone.h"
#include <vector>

enum class GameState
{
	start,//
	in_game,//プレイ中
	gameclear,//ゲームクリア
	gameover,//エネミーがゴールした
};

class GameMainScene :
    public AbstractScene
{
private:
	GameState game_state;

	ObjectBase* check_virtual;
	std::vector<ObjectBase*> objects;
	std::vector<Coin*> coins;
	
	UICoins* ui_coins;
	UITimer* ui_timer;

	int enm_generate_cnt;//エネミー生成カウント
	
	int wall_cnt;//ゴールの数カウント

	bool is_enm_generate;//エネミーを生成するか？

	bool is_game_clear;			// ゲームクリアか？
	bool is_game_over;			// ゲームオーバーか？
	int change_wait_time;		// シーン切り替え待ち時間

	bool is_pause;				// 一時停止か？

	bool is_spos_select;        // スキル置く場所選択中か？

	bool is_attack_active;      // アタックスキルが有効か？

	std::vector<int> background_image;     // 背景画像
	float background_location_y;				// 背景のy座標

	bool change_pause_page_flg;		// ポーズ中のヘルプのページを変更するか？
	bool click_left_button_flg;		// 左向き矢印ボタンをクリックしたか？
	bool click_title_button_flg;	// タイトルボタンをクリックしたか？
	bool going_title;				// タイトルへ行きますか？

	int bgm; // BGMデータ


public:
	GameMainScene();
	~GameMainScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;

private:
	//プレイ中
	void InGameUpdate();
	void InStartUpdate();//スタート
	void InGameClearUpdate();//ゲームクリア
	void InGameOverUpdate();//ゲームオーバー

private:
	void Initialize();
	void EnemyGenerate(int num);
	void EnmGenerateTimeCheck();
	void CoinGenerate(int i, int j);
	// スキルボタンの解放でコインを使った時の処理
	void SkillCoinUse(int i,int coin_num); 
	// スキル位置選択ポーズ処理
	void SkillPause(int i);
	// カーソルのみの更新処理
	void CursorUpdate();
	// 一時停止か調べる処理
	void PauseCheck();
	// カーソルがスキルボタンの上にある時の処理
	void HitCursorBSkill(int i);
	// カーソルがスキルボタンの上に無い時の処理
	void ResetCursorBSkill(int i);

protected:
	template <class T>
	T* CreateObject(Vector2D set_location)
	{
		T* new_instance = new T();

		ObjectBase* new_object = dynamic_cast<ObjectBase*>(new_instance);

		if (new_object == nullptr)
		{
			delete new_instance;
			throw("ゲームオブジェクトが生成できませんでした\n");
		}

		objects.push_back(new_object);
		objects.back()->SetLocation(set_location);
		return new_instance;
	}
	
};

