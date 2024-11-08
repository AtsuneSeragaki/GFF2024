#pragma once
#include "EnemyBase.h"
class CrackEnemy :
    public EnemyBase
{
private:
    //int handle;//画像読込
    //int handle2;//画像読込
    //int image_width;
    //int image_height;
   // int red, green, blue;//RGB
   // int alpha;//透明度
public:
    CrackEnemy();
    ~CrackEnemy();
    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

    
};

