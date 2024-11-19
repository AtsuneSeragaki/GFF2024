#pragma once
#include "../ObjectBase.h"
class Barrier :
    public ObjectBase
{
private:
    int hp;//ゴールの耐久値

public:
    Barrier();
    ~Barrier();

    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

};

