#pragma once
#include "DxLib.h"
#include "../../UtilityFile/Geometry.h"
#include <vector>

class Coin
{
private:
	Vector2D location;				// 座標
	Vector2D ui_coins_location;		// コインUIの座標
	Vector2D distance;				// コインUIとコインの距離
	float hypotenuse;				// 斜辺
	float speed;					// コインの移動速度
	bool can_delete;				// 削除してもいいか

	std::vector<int> coin_image;    // コイン画像
	int image_num;					// 画像番号
	int anim_count;					// アニメーションカウント


	int delete_count;				// 消えるまでのカウント（テスト用）

public:
	Coin();
	~Coin();

	void Update();
	void Draw() const;

	bool GetCanDeleteFlg() const;
	void SetLocation(const Vector2D& location);						// 生成座標の設定
	void SetUICoinsLocation(const Vector2D& ui_coins_location);		// コインUI座標の設定
};