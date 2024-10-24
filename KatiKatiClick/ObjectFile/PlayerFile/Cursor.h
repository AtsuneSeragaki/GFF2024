#pragma once
#include "../ObjectBase.h"
class Cursor :
    public ObjectBase
{
public:
    Cursor();
    ~Cursor();

    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;
};

