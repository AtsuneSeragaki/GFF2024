#pragma once
#include "../ObjectBase.h"
class Goal :
    public ObjectBase
{
private:
    int goal_cnt;//敵が通った数をカウント

public:
    Goal();
    ~Goal();

    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

    void EnemyGoal() { goal_cnt--; }
    int GetGoalCnt() { return goal_cnt; }
};

