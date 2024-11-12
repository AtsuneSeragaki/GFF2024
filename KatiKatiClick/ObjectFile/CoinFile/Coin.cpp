#include "DxLib.h"
#include "Coin.h"
#include "../../UtilityFile/ResourceManager.h"
#include "../../UtilityFile/Define.h"

Coin::Coin()
{
	location = 0.0f;
	ui_coins_location = 0.0f;
	distance = 0.0f;
	hypotenuse = 0.0f;
	speed = 5.0f;
	effect_flg = false;
	can_delete = false;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// コイン画像を読み込む
	tmp = rm->GetImages("Resource/Images/Coin/Coin03.png", 6, 6, 1, 32, 16);
	for (int i = 0; i < 6; i++)
	{
		coin_image.push_back(tmp[i]);
	}

	// エフェクト画像を読み込む
	tmp = rm->GetImages("Resource/Images/Coin/Effect.png", 6, 6, 1, 16, 16);
	for (int i = 0; i < 6; i++)
	{
		effect_image.push_back(tmp[i]);
	}

	image_num = 0;
	anim_count = 0;
	radius = 10.0f;
	effect_count = 150;

	angle = 0.0;
	degree = 0.0;
}

Coin::~Coin()
{

}

void Coin::Update()
{
	if (effect_flg == false)
	{
		// コイン回収の動き
		CoinMove();

		// コインのアニメーション
		CoinAnimation();

		if (hypotenuse < speed)
		{
			// エフェクトが出現
			effect_flg = true;

			anim_count = 0;
			image_num = 0;
		}
	}
	else
	{
		effect_count -= 3;
		radius += 0.5f;

		// エフェクトアニメーション更新
		anim_count++;

		if (anim_count >= 5)
		{
			if (image_num < 5)
			{
				image_num++;
			}
			else
			{
				// アニメーションが一周したらコインを削除
				can_delete = true;
			}

			anim_count = 0;
		}

		//// 回転
		//if (degree < 360.0)
		//{
		//	degree += 2.0;
		//}
		//else
		//{
		//	degree = 0.0;
		//}

		//// 画像の角度
		//angle = DEGREE_RADIAN(degree);
	}
}

void Coin::Draw() const
{
	if (effect_flg == false)
	{
		// コイン画像の描画
		DrawRotaGraphF(location.x, location.y, 1.5, 0.0, coin_image[image_num], TRUE);
	}
	else
	{
		// 描画輝度のセット
		SetDrawBright(255, 255, 150);
		// エフェクト画像の描画
		DrawRotaGraphF(location.x, location.y, 2.0, angle, effect_image[image_num], TRUE);
		// 描画輝度を元に戻す
		SetDrawBright(255, 255, 255);


		//// 描画ブレンドモードをアルファブレンドにする
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, effect_count);
		//// 円のエフェクトの描画
		//DrawCircleAA(location.x, location.y, radius, 32, GetColor(255, 255, 150), FALSE, 1.0f);
		//// 描画ブレンドモードをノーブレンドにする
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// エフェクト画像の描画
		//DrawRotaGraphF(location.x, location.y, 2.0, 0.0, effect_image[image_num], TRUE);
	}
}

// コイン回収の動き
void Coin::CoinMove()
{
	// コインUIとコインのx座標、y座標のそれぞれの距離
	distance.x = ui_coins_location.x - location.x;
	distance.y = ui_coins_location.y - location.y;

	// 平方根を使ってコインUIとコインの斜辺の距離を求める
	hypotenuse = sqrtf(distance.x * distance.x + distance.y * distance.y);

	// speed分ずつコインがUIに向かって動く
	location.x += distance.x / hypotenuse * speed;
	location.y += distance.y / hypotenuse * speed;

	// 加速
	speed += 0.5f;
}

// コインのアニメーション
void Coin::CoinAnimation()
{
	anim_count++;

	if (anim_count >= 5)
	{
		if (image_num < 5)
		{
			image_num++;
		}
		else
		{
			image_num = 0;
		}

		anim_count = 0;
	}
}

bool Coin::GetCanDeleteFlg() const
{
	return can_delete;
}

// 生成座標の設定
void Coin::SetLocation(const Vector2D& location)
{
	this->location = location;
}

// コインUI座標の設定
void Coin::SetUICoinsLocation(const Vector2D& ui_coins_location)
{
	this->ui_coins_location.x = ui_coins_location.x - 70.0f;
	this->ui_coins_location.y = ui_coins_location.y;
}