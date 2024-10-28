#include "Coin.h"

Coin::Coin()
{
	location = 0.0f;
	ui_coins_location = 0.0f;
	can_delete = false;

	delete_count = 0;
}

Coin::~Coin()
{

}

void Coin::Update()
{
	delete_count++;

	if (delete_count >= 60)
	{
		// 60カウント以上になったらコインを削除
		can_delete = true;
	}
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

// コインUI座標の設定
void Coin::SetUICoinsLocation(const Vector2D& ui_coins_location)
{
	this->ui_coins_location = ui_coins_location;
}