#pragma once
#include "../ObjectBase.h"
#include "../ClickEffectFile/ClickEffect.h"
#include <vector>

class Cursor :
    public ObjectBase
{
private:
    int se[2]; // 効果音
    std::vector<ClickEffect*> click_effect;     // クリックエフェクト

public:
    Cursor();
    ~Cursor();

    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;
};

