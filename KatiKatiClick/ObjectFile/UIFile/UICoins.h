#pragma once
#include "UIBase.h"
#include "../../UtilityFile/Geometry.h"
#include <vector>

class UICoins : public UIBase
{
private:
    Vector2D location;			    // 座標
	int coins_num;                  // 今持っているコインの枚数
    std::vector<int> coin_image;    // コイン画像
    std::vector<int> num_image;     // 数字画像
    int image_num[3];               // 描画する画像番号

public:
    UICoins();
    ~UICoins();

    void Update() override;
    void Draw() const override;

    void IncreaseCoins();               // コインを1増やす
    void ReduceCoins(int coins_num);    // コインを減らす

    Vector2D GetLocation() const;       // 座標の取得
    int GetCoinsNum() const;            // コインの枚数を取得
};