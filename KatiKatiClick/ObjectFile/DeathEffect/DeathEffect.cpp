#include "DeathEffect.h"
#include "DxLib.h"

DeathEffect::DeathEffect(Vector2D set_location)
{
	pos1 = set_location;
	pos2 = set_location;
	pos3 = set_location;
	pos4 = set_location;

	pos1.x -= 15;
	pos1.y -= 10;
	pos2.x += 5;
	pos2.y -= 10;
	pos3.x += 5;
	pos3.y += 10;
	pos4.x -= 15;
	pos4.y += 10;

	count = 0;
	alpha = 255;

	vel = -10;
	acc = 1;
	can_delete = false;
}

DeathEffect::~DeathEffect()
{
}

void DeathEffect::Update()
{
	if (count < 10) {
		count++;

	}
	else
	{
		alpha = 70;
	}
	float num = (float)count;
	pos1.x -= num;
	pos1.y -= num;
	pos2.x += num;
	pos2.y -= num;
	pos3.x += num;
	pos3.y += num;
	pos4.x -= num;
	pos4.y += num;


}

void DeathEffect::DamageEffect()
{
	vel += acc;
	pos1.y += vel;
	pos2.y += vel;
	pos3.y += vel;
	pos4.y += vel;

	pos1.x -= 6.0f;
	pos2.x += 5.0f;
	pos3.x -= 3.0f;
	pos4.x += 4.0f;

	if (vel > 10)
	{
		can_delete = true;
	}

}

void DeathEffect::Draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox((int)pos1.x, (int)pos1.y, (int)pos1.x + 10, (int)pos1.y + 10, 0xffffff, TRUE);
	DrawBox((int)pos2.x, (int)pos2.y, (int)pos2.x + 10, (int)pos2.y + 10, 0xffffff, TRUE);
	DrawBox((int)pos3.x, (int)pos3.y, (int)pos3.x + 10, (int)pos3.y + 10, 0xffffff, TRUE);
	DrawBox((int)pos4.x, (int)pos4.y, (int)pos4.x + 10, (int)pos4.y + 10, 0xffffff, TRUE);
	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool DeathEffect::GetDeleteFlg()
{
	return can_delete;
}

