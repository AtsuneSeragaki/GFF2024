#pragma once
#include "EnemyBase.h"
class MiniCrackEnemy :
    public EnemyBase
{
public:
    MiniCrackEnemy();
    ~MiniCrackEnemy();
    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

};

