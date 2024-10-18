#pragma once
#include "EnemyBase.h"
class SquishEnemy :
    public EnemyBase
{
private:
public:
    SquishEnemy();
    ~SquishEnemy();
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

};

