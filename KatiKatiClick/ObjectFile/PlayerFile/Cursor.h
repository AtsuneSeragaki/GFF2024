#pragma once
#include "../ObjectBase.h"
class Cursor :
    public ObjectBase
{
public:
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;
};

