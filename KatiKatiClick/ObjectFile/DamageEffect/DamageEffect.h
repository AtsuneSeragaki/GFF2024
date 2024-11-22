#pragma once
#include "../../UtilityFile/Geometry.h"
#include <vector>

class DamageEffect
{
private:
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
	
public:
	//倒れたエネミーの座標を受け取る
	DamageEffect(Vector2D set_location);
	~DamageEffect();

	void Update();
	void WallDamageEffect();
	void Draw()const;
	bool GetDeleteFlg();
};

