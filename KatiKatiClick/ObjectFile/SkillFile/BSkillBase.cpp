#include "BSkillBase.h"

BSkillBase::BSkillBase() : image(0),bskill_state(BSkillState::close),use_coin(0), hit_cursor(false),se(),effect_image(0),effect_x(0),effect_y(0),effect_width(0),effect_height(0)
{
}

void BSkillBase::SetHitCursorFlg(bool flg)
{
	hit_cursor = flg;
}
