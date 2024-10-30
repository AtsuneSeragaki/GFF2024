#pragma once
#include "DxLib.h"
#include "../../UtilityFile/Geometry.h"

class Coin
{
private:
	Vector2D location;				// 座標
	Vector2D ui_coins_location;		// コインUIの座標
	bool can_delete;				// 削除してもいいか

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