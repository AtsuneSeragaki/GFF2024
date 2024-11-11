#pragma once
#include "UIBase.h"
#include <vector>

class UITimer : public UIBase
{
private:
	int fps_count;
	int seconds;		            // ゲームが終わるまでの秒数
    std::vector<int> timer_image;   // タイマー画像
    std::vector<int> colon_image;   // コロン画像
    std::vector<int> num_image;     // 数字画像
    int image_minutes_num;          // 分画像番号
    int image_seconds_num[2];       // 秒画像番号

public:
    UITimer();
    ~UITimer();

    void Update() override;
    void Draw() const override;

    int GetSeconds() const;     // 秒数の取得

private:
    // 表示する数字画像を調べる
    void CheckDisplayNumImage();
};