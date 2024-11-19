#include "Barrier.h"
#include "DxLib.h"
#include "../../UtilityFile/Define.h"

Barrier::Barrier()
{
	location.x = (float)SCREEN_WIDTH / 2.0f;
	width = (float)SCREEN_WIDTH;
	height = (float)ONE_LANE_HEIGHT / 4.0f;
	shape = Shape::square;
	object_type = ObjectType::barrier;
	hp = 2;
	can_hit = true;
}

Barrier::~Barrier()
{
}

void Barrier::Initialize()
{
}

void Barrier::Update()
{
	if (hp <= 0)
	{
		can_delete = true;
	}
}

void Barrier::Draw() const
{
	DrawBox((int)location.x - (int)width / 2, (int)location.y - (int)height / 2, (int)location.x + (int)width / 2, (int)location.y + (int)height / 2, 0xffff00, TRUE);
	DrawBox((int)location.x - (int)width / 2, (int)location.y - (int)height / 2, (int)location.x + (int)width / 2, (int)location.y + (int)height / 2, 0xAD6820, FALSE);
}

void Barrier::HitReaction(ObjectBase* character)
{
	if (character->GetObjectType() == ObjectType::enemy)
	{
		if (hp > 0)
		{
			hp -= 1;
		}
	}
}
