#pragma once
#include "../ObjectBase.h"
#include "DxLib.h"
#include <vector>
#include "../../UtilityFile/ResourceManager.h"

enum class State
{
	wait,//動き出すまでの待機
	move,//動く
	goal,//ゴールしたとき
	death,//倒された時
};

class EnemyBase :
    public ObjectBase
{
protected:
	State state;
    int hp;//体力
	float speed;//速さ
	bool hit_cursor;//カーソルに当たった
	int wait_time;//動くまでの時間
	int se[2]; // 効果音
	bool can_create_mini;//小さいのを作る
	std::vector<int> enemy_image;   //エネミー画像
	std::vector<int> face_image;	//エネミーの表情画像
	unsigned int enemy_color;	//エネミーの色
	int face_num;//表示する表情の番号
	double face_exrate;//拡大率
	int face_shift_y;//表情の画像ずらす用

	int count_img;//画像切り替えカウント
	int change_img;//画像切り替え

	int shape_change_x;//歩く画像を変更する数字で
	int shape_change_y;
	int shape_change_cnt;//カウント

	bool create_wall_effect;//壁にぶつかった時のエフェクト
	bool create_damage_effect;//ダメージ受けた時のエフェクト

	float default_speed; // スピードの初期値
	bool hit_slowdown_skill; // 足止めスキルに当たっているか

public:
	EnemyBase()
	{
		enemy_color = 0x000000;
		wait_time = 0;
		hp = 0;
		default_speed = 0.0f;
		speed = default_speed;
		hit_cursor = false;
		state = State::wait;
		can_create_mini = false;
		se[0] = 0;
		se[1] = 0;
		count_img = 0;
		change_img = 0;
		shape_change_x = 0;
		shape_change_y = 0;
		shape_change_cnt = 0;
		create_damage_effect = false;
		create_wall_effect = false;
		face_num =0;
		face_exrate = 2.0;
		face_shift_y = 18;
		
		hit_slowdown_skill = false;

		// ResourceManagerのインスタンスを取得
		ResourceManager* rm = ResourceManager::GetInstance();
		std::vector<int> tmp_img;
		//敵画像表情読み込み
		tmp_img = rm->GetImages("Resource/Images/Characters/Enemy/face.png", 5, 5, 1, 22, 9);
		//12~15
		for (int i = 0; i < 5; i++)
		{
			face_image.push_back(tmp_img[i]);
		}
	}
	~EnemyBase(){};

	void Initialize() override = 0;
	void Update()override = 0;
	void Draw() const override=0;
	void HitReaction(ObjectBase* character) override=0; //hitCheckがtrueだったらhitした後の処理をする
	bool GetHitCursor() { return hit_cursor; }
	void SetFalseHitCursor() { hit_cursor = false; }
	void SetWaitTime(int set_time) { wait_time = set_time; }
	bool GetCanCreateMini() { return can_create_mini; }
	void SetMini(float set_width, float set_height)
	{
		width = set_width;
		height = set_height;
		hp = 10;
		default_speed = 2.0f;
		speed = default_speed;
		face_exrate = 1.3;
		face_shift_y = 11;
		face_num = 2;
		hit_slowdown_skill = false;
	}
	void SetHp(int set_hp) { hp = set_hp; }
	void StopCreateMini() { can_create_mini = false; }
	void SetSpeed(float set_speed) { speed = set_speed; }
	State GetState() { return state; }
	void SetStateGameOver() {
		speed = 5;
		state = State::goal;
	}
	bool GetCreateWallEffect() { return create_wall_effect; }
	void OffCreateWallEffect() { create_wall_effect=false; }
	bool GetCreateDamageEffect() { return create_damage_effect; }
	void OffCreateDamageEffect() { create_damage_effect=false; }
	
	void MoveShapeChange();

	unsigned int GetColor()
	{
		return enemy_color;
	}

	float GetEnemySpeed() { return speed; }
	float GetEnemyDefaultSpeed() { return default_speed; }
	bool GetHitSlowDownSkillFlg() { return hit_slowdown_skill; }
	void SetHitSlowDownSkillFlg(bool flg) { hit_slowdown_skill = flg; }
};

