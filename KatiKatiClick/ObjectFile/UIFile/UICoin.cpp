#include "UICoins.h"

UICoins::UICoins()
{
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
	DrawFormatString(100, 600, 0xffffff, "coins : %d", coins_num);
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

// コインの枚数を取得
int UICoins::GetCoinsNum() const
{
	return coins_num;
}