#include "Coin.h"

Coin::Coin()
{
	location = 0.0f;
	can_delete = false;
}

Coin::~Coin()
{

}

void Coin::Update()
{

}

void Coin::Draw() const
{
	// 円の描画
	DrawCircleAA(location.x, location.y, 5.0f, 32, 0xffff00, FALSE);
}

bool Coin::GetCanDeleteFlg() const
{
	return can_delete;
}

// 生成座標の設定
void Coin::SetLocation(const Vector2D& location)
{
	this->location = location;
}
