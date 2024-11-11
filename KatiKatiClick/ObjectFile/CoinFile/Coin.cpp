#include "Coin.h"
#include "../../UtilityFile/ResourceManager.h"

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

	image_num = 0;
	anim_count = 0;

	delete_count = 0;
}

Coin::~Coin()
{

}

void Coin::Update()
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

	//delete_count++;

	//if (delete_count >= 180)
	//{
	//	// 60カウント以上になったらコインを削除
	//	//can_delete = true;
	//}

	// コインUIとコインのx座標、y座標のそれぞれの距離
	distance.x = ui_coins_location.x - location.x;
	distance.y = ui_coins_location.y - location.y;

	// 平方根を使ってコインUIとコインの斜辺の距離を求める
	hypotenuse = sqrtf(distance.x * distance.x + distance.y * distance.y);

	location.x += distance.x / hypotenuse * speed;
	location.y += distance.y / hypotenuse * speed;

	if (hypotenuse < speed)
	{
		// コインを削除
		can_delete = true;
	}

	// 加速
	speed += 0.5f;
}

void Coin::Draw() const
{
	// コイン画像の描画
	DrawRotaGraphF(location.x, location.y, 1.5, 0.0, coin_image[image_num], TRUE);

	// 円の描画
	//DrawCircleAA(location.x, location.y, 5.0f, 32, 0xffff00, FALSE);
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