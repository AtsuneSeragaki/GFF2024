#pragma once
#include "UIBase.h"
#include <vector>

class UITimer : public UIBase
{
private:
	int fps_count;
	int seconds;		            // ゲームが終わるまでの秒数
    std::vector<int> images_data;   // 数字画像
    int image_num[2];               // 描画する画像番号

public:
    UITimer();
    ~UITimer();

    void Update() override;
    void Draw() const override;

    int GetSeconds() const;     // 秒数の取得
    int GetSecondsImage() const;    // 
};