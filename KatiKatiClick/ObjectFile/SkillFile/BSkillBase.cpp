#include "BSkillBase.h"

BSkillBase::BSkillBase() : image(0),bskill_state(BSkillState::close),use_coin(0), hit_cursor(false),se(),effect_image(0)
{
}

void BSkillBase::SetHitCursorFlg(bool flg)
{
	hit_cursor = flg;
}
