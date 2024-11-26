#pragma once
#include "../PauseBase.h"
#include <vector>

class YesButton : public PauseBase
{
private:
    std::vector<int> box_image;         // ボックス画像
    std::vector<int> button_image;      // ボタン画像
    int anim_count;						// ボタン押下アニメーション
    int button_image_num;				// ボタンの画像番号
    bool going_title;                   // タイトルに戻るか？
public:
	YesButton();
	~YesButton();

    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

    bool GetGoingTitleFlg() const;
};