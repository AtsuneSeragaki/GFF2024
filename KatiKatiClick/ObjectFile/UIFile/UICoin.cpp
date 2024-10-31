#include "UICoins.h"

UICoins::UICoins()
{
	location.x = 150.0f;
	location.y = 20.0f;
	coins_num = 0;
}

UICoins::~UICoins()
{

}

void UICoins::Update()
{
	// 数字画像の切り替え

}

void UICoins::Draw() const
{
	DrawBox(140, 10, 260, 50, 0xc0c0c0, TRUE);
	DrawFormatString((int)location.x, (int)location.y, 0x000000, "coins : %d", coins_num);
}

// コインを1増やす
void UICoins::IncreaseCoins()
{
	coins_num++;
}

// コインを減らす
void UICoins::ReduceCoins(int coins_num)
{
	this->coins_num -= coins_num;
}

// 座標の取得
Vector2D UICoins::GetLocation() const
{
	return location;
}

// コインの枚数を取得
int UICoins::GetCoinsNum() const
{
	return coins_num;
}