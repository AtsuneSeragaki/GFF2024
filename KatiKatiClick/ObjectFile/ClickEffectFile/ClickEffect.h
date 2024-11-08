#pragma once
#include "../../UtilityFile//Geometry.h"

class ClickEffect
{
private:
	Vector2D location;		// 座標
	float radius;			// 半径
	int count;				// エフェクト再生カウント
	bool can_delete;		// 削除しても良いか？

public:
	ClickEffect();
	~ClickEffect();

	void Update();
	void Draw() const;

	void SetLocation(const Vector2D& location);		// 生成座標の設定
	bool GetDeleteFlg() const;
};

