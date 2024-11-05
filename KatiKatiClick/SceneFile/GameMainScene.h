#pragma once
#include "AbstractScene.h"
#include "DxLib.h"
#include "../ObjectFile/EnemyFile/CrackEnemy.h"
#include "../ObjectFile/EnemyFile/BurstEnemy.h"
#include "../ObjectFile/EnemyFile/SnakeEnemy.h"
#include "../ObjectFile/PlayerFile/Cursor.h"
#include "../ObjectFile/GoalFile/Goal.h"
#include "../UtilityFile/Define.h"
#include "../ObjectFile/CoinFile/Coin.h"
#include "../UtilityFile/Geometry.h"
#include "../ObjectFile/UIFile/UICoins.h"
#include "../ObjectFile/UIFile/UITimer.h"
#include "../ObjectFile/PauseButton/PauseButton.h"
#include <vector>

class GameMainScene :
    public AbstractScene
{
private:
	ObjectBase* check_virtual;
	std::vector<ObjectBase*> objects;
	std::vector<Coin*> coins;
	UICoins* ui_coins;
	UITimer* ui_timer;
	Goal* goal;

	int enm_generate_cnt;//エネミー生成カウント
	
	bool is_enm_generate;//エネミーを生成するか？

	bool is_game_clear;			// ゲームクリアか？
	bool is_game_over;			// ゲームオーバーか？
	int change_wait_time;		// シーン切り替え待ち時間

public:
	GameMainScene();
	~GameMainScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;


private:
	void Initialize();
	void EnemyGenerate(int num);
	void EnmGenerateTimeCheck();
	void CoinGenerate(int i, int j);
	// スキルボタンの解放でコインを使った時の処理
	void SkillCoinUse(int i,int coin_num); 
	// スキル位置選択ポーズ処理
	void SkillPause(int i);

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

