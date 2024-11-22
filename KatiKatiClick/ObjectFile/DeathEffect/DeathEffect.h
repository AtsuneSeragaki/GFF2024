#pragma once
#include "../../UtilityFile/Geometry.h"

class DeathEffect
{
private:
	Vector2D pos1;
	Vector2D pos2;
	Vector2D pos3;
	Vector2D pos4;

	int count;
	int alpha;

	float vel;//初速を入れる
	float acc;//重力加速
	
	bool can_delete;//削除してもいいか
	
public:
	//倒れたエネミーの座標を受け取る
	DeathEffect(Vector2D set_location);
	~DeathEffect();

	void Update();
	void DamageEffect();
	void Draw()const;
	bool GetDeleteFlg();
};

