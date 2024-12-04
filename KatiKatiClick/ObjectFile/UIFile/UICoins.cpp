#include "UICoins.h"
#include "../../UtilityFile/ResourceManager.h"
#include "../../UtilityFile/Define.h"
#include "DxLib.h"

UICoins::UICoins()
{
	location.x = 227.0f;
	location.y = 765.0f;
	coins_num = 0;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// コイン画像の読み込み
	tmp = rm->GetImages("Resource/Images/Coin/Wallet.png");
	wallet_image.push_back(tmp[0]);

	// 数字画像を読み込む
	tmp = rm->GetImages("Resource/Images/Timer/Num.png", 10, 10, 1, 32, 32);
	for (int i = 0; i < 10; i++)
	{
		num_image.push_back(tmp[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		image_num[i] = 0;
	}

	// 音データ読み込み
	int tmp_s;
	tmp_s = rm->GetSounds("Resource/Sounds/GameMain/Coin/getcoin.mp3");
	se = tmp_s;

	ChangeVolumeSoundMem(90, se);

	box_width = 134.0f;
	box_location_x = SCREEN_WIDTH_HALF - box_width / 2;

	for (int i = 0; i < 3; i++)
	{
		move_num_image[i] = 0;
	}
	move_height = 0.0f;
}

UICoins::~UICoins()
{

}

void UICoins::Update()
{
	int tmp_coins_num = coins_num;

	for (int i = 0; i < 3; i++)
	{
		int tmp_image_num = image_num[i];

		if (tmp_coins_num > 0)
		{
			// 数字画像の切り替え
			// 小さい位の数字から求める
			image_num[i] = tmp_coins_num % 10;
			// 次の位
			tmp_coins_num /= 10;
		}
		else
		{
			image_num[i] = 0;
		}

		// コインが減った
		if (tmp_image_num > image_num[i])
		{
			if (i == 1)
			{
				// 下の位の数字画像も下がる
				move_num_image[0] = 2;
			}

			if (i == 2)
			{
				// 下の位の数字画像も下がる
				move_num_image[0] = 2;
				move_num_image[1] = 2;
			}

			move_num_image[i] = 2;
			move_height = 5.0f;
		}
		
		// コインが増えた
		if (tmp_image_num < image_num[i])
		{
			if (i == 1)
			{
				// 下の位の数字画像も上がる
				move_num_image[0] = 1;
			}

			if (i == 2)
			{
				// 下の位の数字画像も上がる
				move_num_image[0] = 1;
				move_num_image[1] = 1;
			}

			move_num_image[i] = 1;
			move_height = 5.0f;
		}
	}

	if (move_height > 0.0f)
	{
		// 数字画像を元の位置に戻していく
		move_height -= 0.5f;
	}
	else
	{
		move_height = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			// 数字画像の描画位置を戻す
			move_num_image[i] = 0;
		}
	}
}

void UICoins::Draw() const
{
	// 描画ブレンドモードをアルファブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	// 白色四角
	DrawBoxAA(box_location_x, location.y - 25.0f, box_location_x + box_width, location.y + 25.0f, 0xffffff, TRUE);
	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// 黒色四角枠
	DrawBoxAA(box_location_x, location.y - 25.0f, box_location_x + box_width, location.y + 25.0f, 0x000000, FALSE, 3.0f);

	// 財布画像の描画
	DrawRotaGraphF(location.x - 80.0f, location.y, 1.0, 0.0, wallet_image[0], TRUE);

	for (int i = 0; i < 3; i++)
	{
		// 数字画像の描画
		switch (move_num_image[i])
		{
		case 0:
			DrawRotaGraphF(location.x - i * 20.0f, location.y, 1.0, 0.0, num_image[image_num[i]], TRUE);
			break;
		case 1:
			// 描画位置が上がる
			DrawRotaGraphF(location.x - i * 20.0f, location.y - move_height, 1.0, 0.0, num_image[image_num[i]], TRUE);
			break;
		case 2:
			// 描画位置が下がる
			DrawRotaGraphF(location.x - i * 20.0f, location.y + move_height, 1.0, 0.0, num_image[image_num[i]], TRUE);
			break;
		default:
			break;
		}
	}

	//DrawLineAA(180.0f, 0.0f, 180.0f, 800.0f, 0xff0000, 1.0f);
}

// コインを1増やす
void UICoins::IncreaseCoins()
{
	// コインがカウントアップする時のSE再生
	PlaySoundMem(se, DX_PLAYTYPE_BACK, TRUE);
	coins_num++;
}

// コインを減らす
void UICoins::ReduceCoins(int coins_num)
{
	this->coins_num -= coins_num;
}

// 座標の取得
Vector2D UICoins::GetLocation() const
{
	return location;
}

// コインの枚数を取得
int UICoins::GetCoinsNum() const
{
	return coins_num;
}