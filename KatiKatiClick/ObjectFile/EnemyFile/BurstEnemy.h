#pragma once
#include "EnemyBase.h"
class BurstEnemy :
    public EnemyBase
{
private:
public:
    BurstEnemy();
    ~BurstEnemy();
    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

};
