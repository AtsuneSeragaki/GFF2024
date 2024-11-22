#include "UICoins.h"
#include "../../UtilityFile/ResourceManager.h"
#include "DxLib.h"

UICoins::UICoins()
{
	location.x = 230.0f;
	location.y = 760.0f;
	coins_num = 0;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// コイン画像の読み込み
	tmp = rm->GetImages("Resource/Images/Coin/Wallet.png");
	coin_image.push_back(tmp[0]);

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
}

UICoins::~UICoins()
{

}

void UICoins::Update()
{
	// 数字画像の切り替え
	int tmp_coins_num = coins_num;

	for (int i = 0; i < 3; i++)
	{
		if (tmp_coins_num > 0)
		{
			// 小さい位の数字から求める
			image_num[i] = tmp_coins_num % 10;
			// 上の位
			tmp_coins_num /= 10;
		}
		else
		{
			image_num[i] = 0;
		}
	}

}

void UICoins::Draw() const
{
	//DrawBox(170, 10, 280, 60, 0xfff4b3, TRUE);
	//DrawBoxAA(170.0f, 10.0f, 280.0f, 60.0f, 0x000000, FALSE, 2.0f);

	// 描画ブレンドモードをアルファブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	// 白色四角
	DrawBoxAA(location.x - 115.0f, location.y - 25.0f, location.x + 30.0f, location.y + 25.0f, 0xffffff, TRUE);
	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawBoxAA(location.x - 115.0f, location.y - 25.0f, location.x + 30.0f, location.y + 25.0f, 0x000000, FALSE, 2.0f);

	// コイン画像の描画
	DrawRotaGraphF(location.x - 80.0f, location.y, 1.0, 0.0, coin_image[0], TRUE);

	for (int i = 0; i < 3; i++)
	{
		// 数字画像の描画
		DrawRotaGraphF(location.x - i * 20.0f, location.y, 1.0, 0.0, num_image[image_num[i]], TRUE);
	}

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