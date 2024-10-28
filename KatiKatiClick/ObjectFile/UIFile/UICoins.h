#pragma once
#include "UIBase.h"

class UICoins : public UIBase
{
private:
	int coins_num;               // 今持っているコインの枚数

public:
    UICoins();
    ~UICoins();

    void Update()override;
    void Draw()const override;

    void IncreaseCoins();               // コインを1増やす
    void ReduceCoins(int coins_num);    // コインを減らす

    int GetCoinsNum() const;            // コインの枚数を取得
};