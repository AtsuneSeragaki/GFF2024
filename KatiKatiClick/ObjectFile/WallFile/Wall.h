#pragma once
#include "../ObjectBase.h"

#include <vector>
class Wall :
    public ObjectBase
{
private:
    int hp;//ゴールの耐久値
    std::vector<int> img;
    std::vector<int> smoke_img;
    std::vector<int> damage_img;

    int img_num;//画像切替表示用
    int smoke_cnt;
    int change_cnt;//画像切り替えカウント
    int flash_cnt;
    int off_flash_cnt;//flashとめるまでのカウント

    Vector2D damage_pos;
    bool damage_display;
    bool can_shake;
    bool smoke_flg;
    bool can_damage_flash;//点滅するか
    bool flash_flg;

    int se; // 効果音
    int se_2; // 効果音

    bool move_once;//movecenterを一度だけ奴用
    int wait_time;//

public:
    Wall();
    ~Wall();

    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

    void MoveCenter();
    void SetWaitTime(int set_time) { wait_time = set_time; }
    bool GetMoveOnce() { return move_once; }

};

