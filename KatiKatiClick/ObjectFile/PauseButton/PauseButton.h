#pragma once
#include "../ObjectBase.h"

class PauseButton : public ObjectBase
{
public:
    PauseButton();
    ~PauseButton();

    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;
};

