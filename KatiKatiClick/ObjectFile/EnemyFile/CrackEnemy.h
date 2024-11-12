#pragma once
#include "EnemyBase.h"
#include <vector>
class CrackEnemy :
    public EnemyBase
{
private:
    int count_img;
    int chenge_img;
    bool check_hp;
public:
    CrackEnemy();
    ~CrackEnemy();
    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

    
};

