#pragma once
#include "../ObjectBase.h"
class Goal :
    public ObjectBase
{
private:
    int hp;//ゴールの耐久値

public:
    Goal();
    ~Goal();

    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

};

