#pragma once
#include "../ObjectBase.h"
#include "../ClickEffectFile/ClickEffect.h"
#include <vector>

enum class P_State
{
    attack,
    wait,
};

class Cursor :
    public ObjectBase
{
private:
    int se; // 効果音
    std::vector<ClickEffect*> click_effect;     // クリックエフェクト
    std::vector<int> cursor_img;//カーソル画像
    int cursor_effect;
    int img_num;//カーソル画像切り替え用
    int count;//カーソル画像切替カウント
    int angle;

    P_State state;

public:
    Cursor();
    ~Cursor();

    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

    P_State GetPState() { return state; }
};

