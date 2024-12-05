#pragma once
#include "UIBase.h"
#include "../../UtilityFile/Geometry.h"
#include <vector>

class UICoins : public UIBase
{
private:
    Vector2D location;			    // 座標
	int coins_num;                  // 今持っているコインの枚数
    std::vector<int> wallet_image;  // 財布画像
    std::vector<int> num_image;     // 数字画像
    int image_num[3];               // 描画する画像番号
    int se;                         // 効果音

    float box_width;                // UI表示領域の幅
    float box_location_x;           // UI表示領域boxのx座標

    int move_num_image[3];          // 0:数字画像は動かない、1:上に動く、 2:下に動く
    float move_height;              // 動く高さ

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