#include "PauseBase.h"

PauseBase::PauseBase()
{
	click_flg = false;
	cursor_overlap_flg = false;
}

PauseBase::~PauseBase()
{
}

void PauseBase::Initialize()
{
}

void PauseBase::Update()
{
}

void PauseBase::Draw() const
{
}

void PauseBase::HitReaction(ObjectBase* character)
{
}

bool PauseBase::GetClickFlg() const
{
	return click_flg;
}

void PauseBase::SetCursorOverlapFlg()
{
	cursor_overlap_flg = true;
}
