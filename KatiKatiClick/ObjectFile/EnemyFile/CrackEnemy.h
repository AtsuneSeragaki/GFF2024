#pragma once
#include "EnemyBase.h"
#include <vector>
class CrackEnemy :
    public EnemyBase
{
private:

public:
    CrackEnemy();
    ~CrackEnemy();
    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

    
};

