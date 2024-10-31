#pragma once
#include "UIBase.h"

class UITimer : public UIBase
{
private:
	int fps_count;
	int seconds;		// ゲームが終わるまでの秒数

public:
    UITimer();
    ~UITimer();

    void Update() override;
    void Draw() const override;

    int GetSeconds() const;     // 秒数の取得
};