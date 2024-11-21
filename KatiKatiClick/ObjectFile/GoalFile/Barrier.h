#pragma once
#include "../ObjectBase.h"
#include "../DeathEffect/DeathEffect.h"

#include <vector>
class Barrier :
    public ObjectBase
{
private:
    int hp;//ゴールの耐久値
    std::vector<int> img;
    std::vector<int> damage_img;

    int img_num;//画像切替表示用
    int change_cnt;//画像切り替えカウント

    Vector2D damage_pos;
    bool damage_display;
    bool can_shake;

    DeathEffect* damage_effect;

public:
    Barrier();
    ~Barrier();

    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

};

