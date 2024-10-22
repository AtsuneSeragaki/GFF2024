#include "Cursor.h"
#include "DxLib.h"

Cursor::Cursor()
{
	location.x = 0.0f;
	location.y = 0.0f;
	object_type = ObjectType::cursor;
	radius = 10.0f;
	can_hit = true;
}

Cursor::~Cursor()
{
}

void Cursor::Update()
{
	int x, y;
	GetMousePoint(&x,&y);
	location.x = (float)x;
	location.y = (float)y;


}

void Cursor::Draw() const
{
	DrawCircleAA(location.x, location.y, radius, 32, 0x00ffff, TRUE);

}

void Cursor::HitReaction(ObjectBase* character)
{
}
