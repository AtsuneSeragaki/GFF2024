#include "ClickEffect.h"
#include "../../UtilityFile/ResourceManager.h"
#include "DxLib.h"

ClickEffect::ClickEffect()
{
	location = 0.0f;
	radius = 10.0f;
	count = 250;
	//max_radius = count / 2 + radius;
	can_delete = false;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// エフェクト画像を読み込む
	tmp = rm->GetImages("Resource/Images/Coin/Effect.png", 6, 6, 1, 16, 16);
	for (int i = 0; i < 6; i++)
	{
		effect_image.push_back(tmp[i]);
	}

	image_num = 0;
	anim_count = 0;
}

ClickEffect::~ClickEffect()
{

}

void ClickEffect::Update()
{
	count -= 5;

	// 半径を大きくする
	//radius += 1.0f;

	if (count <= 0)
	{
		// 削除可能
		can_delete = true;
	}

	// エフェクト更新
	anim_count++;

	if (anim_count >= 5)
	{
		if (image_num < 5)
		{
			image_num++;
		}
		else
		{
			// 削除可能
			can_delete = true;
		}
		anim_count = 0;
	}
}

void ClickEffect::Draw() const
{
	// 描画ブレンドモードをアルファブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, count);

	//DrawCircleAA(location.x, location.y, radius, 32, 0x00cccc, FALSE, 3.0f);
	//DrawCircleAA(location.x, location.y, max_radius, 32, 0x00aaaa, FALSE);

	// エフェクト画像の描画
	DrawRotaGraphF(location.x, location.y, 2.0, 0.0, effect_image[image_num], TRUE);

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