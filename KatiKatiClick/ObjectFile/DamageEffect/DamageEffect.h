#pragma once
#include "../../UtilityFile/Geometry.h"
#include <vector>

enum class Effect_Type
{
	none,
	enemy_damage,
	wall_damage,
};


class DamageEffect
{
private:
	Effect_Type effect_type;
	
	int box_width;
	int box_height;

	Vector2D pos1;
	Vector2D pos2;
	Vector2D pos3;
	Vector2D pos4;
	Vector2D pos;

	std::vector<int> smoke_img;

	int count;
	int alpha;

	float vel;//初速を入れる
	float acc;//重力加速

	int img_num;//画像切替表示用
	int smoke_cnt;
	bool smoke_flg;
	
	bool can_delete;//削除してもいいか

	unsigned int color;//エフェクトの色

	float move;
	
public:
	//倒れたエネミーの座標を受け取る
	DamageEffect(Vector2D set_location,unsigned int get_color);
	~DamageEffect();

	void Update();
	//エネミーのダメージエフェクトの更新
	void EnemyDamageEffect();
	//壁にぶつかったときのエフェクトの更新
	void WallDamageEffect();
	//エネミーのダメージエフェクトをeffect_typeにセット
	void SetEffectEnemyDamage() { effect_type = Effect_Type::enemy_damage; };
	//壁にぶつかったときのエフェクトをeffect_typeにセット
	void SetEffectWallDamage() { effect_type = Effect_Type::wall_damage; };
	void Draw()const;
	bool GetDeleteFlg();
};

