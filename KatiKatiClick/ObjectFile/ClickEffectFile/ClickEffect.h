#pragma once
#include "../../UtilityFile//Geometry.h"
#include <vector>

class ClickEffect
{
private:
	Vector2D location;		// 座標
	float radius;			// 半径
	//float max_radius;		// 最大半径
	int count;				// エフェクト再生カウント
	bool can_delete;		// 削除しても良いか？

	std::vector<int> effect_image;  // エフェクト画像
	int image_num;					// 画像番号
	int anim_count;					// アニメーションカウント


public:
	ClickEffect();
	~ClickEffect();

	void Update();
	void Draw() const;

	void SetLocation(const Vector2D& location);		// 生成座標の設定
	bool GetDeleteFlg() const;
};

