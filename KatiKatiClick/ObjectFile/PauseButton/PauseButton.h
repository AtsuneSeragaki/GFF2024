#pragma once
#include "../ObjectBase.h"
#include <vector>

class PauseButton : public ObjectBase
{
private:
    bool is_pause;          // 一時停止か？

    float cursor_x;         // カーソルx座標
    float cursor_y;         // カーソルy座標

    std::vector<int> question_image;  // はてな画像


public:
    PauseButton();
    ~PauseButton();

    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

    bool GetPauseFlg() const;           // 一時停止フラグの取得
};

