#pragma once
#include "../PauseBase.h"
#include <vector>

class TitleButton : public PauseBase
{
private:
    std::vector<int> button_image;      // ボタン画像
    int anim_count;						// ボタン押下アニメーション
    int button_image_num;				// ボタンの画像番号

public:
    TitleButton();
    ~TitleButton();

    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;
};