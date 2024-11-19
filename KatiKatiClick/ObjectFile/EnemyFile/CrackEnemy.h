#pragma once
#include "EnemyBase.h"
#include <vector>
#include "../DeathEffect/DeathEffect.h"

class CrackEnemy :
    public EnemyBase
{
private:
    //DeathEffect* death_effect;
public:
    CrackEnemy();
    ~CrackEnemy();
    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

};

