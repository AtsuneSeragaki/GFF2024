#pragma once
#include "EnemyBase.h"
class SplitEnemy :
    public EnemyBase
{
private:
    bool check_hp;

public:
    SplitEnemy();
    ~SplitEnemy();
    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;
};

