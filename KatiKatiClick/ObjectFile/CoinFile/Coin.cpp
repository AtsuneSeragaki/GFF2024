#include "Coin.h"

Coin::Coin()
{
	location.x = 100.0f;
	location.y = 100.0f;

	can_delete = false;
}

Coin::~Coin()
{

}

void Coin::Update()
{

}

void Coin::Draw() const
{
	DrawCircleAA(location.x, location.y, 10.0f, 32, 0x00ffff, TRUE);
}

bool Coin::GetCanDeleteFlg() const
{
	return can_delete;
}
