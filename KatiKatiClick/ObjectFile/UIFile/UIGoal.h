#pragma once
#include "UIBase.h"
class UIGoal :
    public UIBase
{
private:
    int goal_hp;

public:
    UIGoal();
    ~UIGoal();
    void SetGoalHp(int set_hp) { goal_hp = set_hp; };

    virtual void Update() override;
    virtual void Draw()const override;
};

