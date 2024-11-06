#pragma once
#include "EnemyBase.h"
class FrogEnemy :
    public EnemyBase
{
private:
    int angle;
    float radian, result;

public:
    FrogEnemy();
    ~FrogEnemy();
    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;
};

