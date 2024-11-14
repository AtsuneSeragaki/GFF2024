#include "DxLib.h"
#include "Coin.h"
#include "../../UtilityFile/ResourceManager.h"
#include "../../UtilityFile/Define.h"
#define _USE_MATH_DEFINES
#include <math.h>

Coin::Coin()
{
	location = 0.0f;
	ui_coins_location = 0.0f;
	distance = 0.0f;
	hypotenuse = 0.0f;
	speed = 5.0f;
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

	state = CoinState::POP;
	result_sin = 0.0f;
	count = 40;
	pop_count = 0;
}

Coin::~Coin()
{

}

void Coin::Update()
{
	switch (state)
	{
		case CoinState::POP:
			// 弾ける動き
			Pop();

			// コインのアニメーション
			CoinAnimation();
			break;

		case CoinState::MOVE:
			// コイン回収の動き
			Move();

			// コインのアニメーション
			CoinAnimation();

			if (hypotenuse < speed)
			{
				// エフェクトが出現
				state = CoinState::EFFECT;

				anim_count = 0;
				image_num = 0;
			}
			break;

		case CoinState::EFFECT:
			// エフェクトのアニメーション
			EffectAnimation();
			break;

		default:
			break;
	}
}

void Coin::Draw() const
{
	switch (state)
	{
		case CoinState::POP:
			// コイン画像の描画
			DrawRotaGraphF(location.x, location.y - result_sin, 1.5, 0.0, coin_image[image_num], TRUE);
			break;

		case CoinState::MOVE:
			// コイン画像の描画
			DrawRotaGraphF(location.x, location.y, 1.5, 0.0, coin_image[image_num], TRUE);
			break;

		case CoinState::EFFECT:
			// 描画輝度のセット
			SetDrawBright(255, 255, 150);
			// エフェクト画像の描画
			DrawRotaGraphF(location.x, location.y, 2.0, 0.0, effect_image[image_num], TRUE);
			// 描画輝度を元に戻す
			SetDrawBright(255, 255, 255);
			break;

		default:
			break;
	}
}

// コイン回収の動き
void Coin::Move()
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

// コイン弾けるの動き
void Coin::Pop()
{
	location.x += 0.5f;

	if (count < 60)
	{
		count++;
	}
	else
	{
		count = 0;
		pop_count++;
	}

	result_sin = fabsf(sinf(M_PI * 2 / 60 * count) * 30);

	if (pop_count >= 1 && count >= 30)
	{
		state = CoinState::MOVE;
	}
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

// // エフェクトのアニメーション
void Coin::EffectAnimation()
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