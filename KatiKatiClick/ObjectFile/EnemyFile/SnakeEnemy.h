#pragma once
#include "EnemyBase.h"
class SnakeEnemy :
    public EnemyBase
{
private:
    int angle;
    float radian, result;

public:
    SnakeEnemy();
    ~SnakeEnemy();
    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

};

