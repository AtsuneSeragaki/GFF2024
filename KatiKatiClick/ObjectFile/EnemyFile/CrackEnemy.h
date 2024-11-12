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

    int shape_change_x;//歩く画像を変更する数字で
    int shape_change_y;
    int shape_change_cnt;//カウント

public:
    CrackEnemy();
    ~CrackEnemy();
    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

};

