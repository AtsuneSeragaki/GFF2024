#pragma once
#include "../PauseBase.h"
#include <vector>

class PauseButton : public PauseBase
{
private:
    bool is_pause;          // 一時停止か？

    std::vector<int> button_image;      // ボタン画像
    std::vector<int> mark_image;        // ボタンのマーク画像
    std::vector<int> heading_image;     // "遊び方"テキスト画像
    std::vector<int> text_image;        // 説明テキスト画像
    std::vector<int> help_image;        // 説明画像
    std::vector<int> mouse_image;       // マウス画像
    std::vector<int> appeal_image;      // マウスのアピール画像
    int image_num;                      // 画像番号
    int page_num;                       // 説明ページ画像番号
    int mouse_image_num;                // マウスの画像番号
    int animation_count;                // マウスのアニメーションカウント
    int button_animation_count;         // ポーズボタンのアニメーションカウント
    bool button_animation_flg;          // ポーズボタンアニメーション開始か？

    float mark_y;                       // ボタンマークのy座標
    int mark_image_num;                 // ボタンマークの画像番号
    double angle;

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