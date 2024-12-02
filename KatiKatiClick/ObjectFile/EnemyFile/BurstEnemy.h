#pragma once
#include "EnemyBase.h"
class BurstEnemy :
    public EnemyBase
{
private:
    int death_cnt;//死ぬまでのカウント
    int angle;
    float radian, result;
public:
    BurstEnemy();
    ~BurstEnemy();
    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

};
