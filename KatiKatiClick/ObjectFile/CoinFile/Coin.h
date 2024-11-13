#pragma once
#include "../../UtilityFile/Geometry.h"
#include <vector>

enum class CoinState
{
	POP,
	MOVE,
	EFFECT,
};

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
	std::vector<int> effect_image;  // エフェクト画像
	int image_num;					// 画像番号
	int anim_count;					// アニメーションカウント

	float radius;					// エフェクトの半径
	int effect_count;				// エフェクトカウント

	double angle;        // 画像の角度
	double degree;       // 角度計算用

	CoinState state;				// コインの状態

public:
	Coin();
	~Coin();

	void Update();
	void Draw() const;

private:
	void Move();				// コイン回収の動き
	void Pop();					// コインが弾ける動き
	void CoinAnimation();			// コインのアニメーション
	void EffectAnimation();			// エフェクトのアニメーション

public:
	bool GetCanDeleteFlg() const;
	void SetLocation(const Vector2D& location);						// 生成座標の設定
	void SetUICoinsLocation(const Vector2D& ui_coins_location);		// コインUI座標の設定
};