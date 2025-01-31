#pragma once
#include "EnemyBase.h"
class HardEnemy :
    public EnemyBase
{
private:
    int angle;
    float radian, result;

    Vector2D old_location;//被ダメージ画像表示用
    bool hit_damage;//ダメージを食らったか
    float old_width, old_height;
    int img_cnt;
    int img_num;
public:
    HardEnemy();
    ~HardEnemy();
    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

};

