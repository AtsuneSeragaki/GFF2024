#include "UICoins.h"

UICoins::UICoins()
{
	location.x = 100.0f;
	location.y = 600.0f;
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
	DrawFormatString((int)location.x, (int)location.y, 0xffffff, "coins : %d", coins_num);
}

// コインを1増やす
void UICoins::IncreaseCoins()
{
	// コインがカウントアップする時のSE再生

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