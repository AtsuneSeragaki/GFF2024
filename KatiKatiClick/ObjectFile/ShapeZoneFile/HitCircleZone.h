#pragma once
#include "../ObjectBase.h"
class HitCircleZone :
    public ObjectBase
{
private:
    int count;
public:
    HitCircleZone();
    ~HitCircleZone();
    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

    void SetRadius(float set_radius) { radius = set_radius; }
};

