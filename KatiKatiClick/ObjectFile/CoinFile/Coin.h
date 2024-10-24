#pragma once
#include "DxLib.h"
#include "../../UtilityFile/Geometry.h"

class Coin
{
private:
	Vector2D location;			// 座標
	bool can_delete;			// 削除してもいいか

public:
	Coin();
	~Coin();

	void Update();
	void Draw() const;

	bool GetCanDeleteFlg() const;
	void SetLocation(const Vector2D& location);		// 生成座標の設定
};