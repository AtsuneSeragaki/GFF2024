#pragma once
#include "../ObjectBase.h"
#include <vector>

class PauseButton : public ObjectBase
{
private:
    bool is_pause;          // 一時停止か？

    float cursor_x;         // カーソルx座標
    float cursor_y;         // カーソルy座標

    std::vector<int> button_image;      // ボタン画像
    std::vector<int> heading_image;     // "遊び方"テキスト画像
    std::vector<int> text_image;        // 説明テキスト画像
    std::vector<int> help_image;        // 説明画像
    int image_num;                      // 画像番号
    int page_num;                       // 説明ページ画像番号

public:
    PauseButton();
    ~PauseButton();

    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

    bool GetPauseFlg() const;           // 一時停止フラグの取得
};

