#pragma once
#include "../ObjectBase.h"
#include <vector>
class Barrier :
    public ObjectBase
{
private:
    int hp;//ゴールの耐久値
    std::vector<int> img;

    int img_num;//画像切替表示用
    int change_cnt;//画像切り替えカウント

public:
    Barrier();
    ~Barrier();

    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

};

