#pragma once
#include "../../ObjectBase.h"
#include <vector>

class PauseButton : public ObjectBase
{
private:
    bool is_pause;          // 一時停止か？

    std::vector<int> button_image;      // ボタン画像
    std::vector<int> heading_image;     // "遊び方"テキスト画像
    std::vector<int> text_image;        // 説明テキスト画像
    std::vector<int> help_image;        // 説明画像
    std::vector<int> mouse_image;      // マウス画像
    int image_num;                      // 画像番号
    int page_num;                       // 説明ページ画像番号
    int mouse_image_num;                // マウスの画像番号
    int animation_count;                // マウスのアニメーションカウント

public:
    PauseButton();
    ~PauseButton();

    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

    bool GetPauseFlg() const;           // 一時停止フラグの取得

    void SetPage(bool change_left);                     // ページの設定
};

