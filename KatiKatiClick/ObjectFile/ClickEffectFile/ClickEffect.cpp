#include "ClickEffect.h"
#include "DxLib.h"

ClickEffect::ClickEffect()
{
	location = 0.0f;
	radius = 10.0f;
	count = 120;
	//max_radius = count / 2 + radius;
	can_delete = false;
}

ClickEffect::~ClickEffect()
{

}

void ClickEffect::Update()
{
	count -= 2;

	// 半径を大きくする
	radius += 0.5f;

	if (count <= 0)
	{
		// 削除可能
		can_delete = true;
	}
}

void ClickEffect::Draw() const
{
	// 描画ブレンドモードをアルファブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, count);

	DrawCircleAA(location.x, location.y, radius, 32, 0x00cccc, FALSE);
	//DrawCircleAA(location.x, location.y, max_radius, 32, 0x00aaaa, FALSE);

	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ClickEffect::SetLocation(const Vector2D& location)
{
	this->location = location;
}

bool ClickEffect::GetDeleteFlg() const
{
	return can_delete;
}