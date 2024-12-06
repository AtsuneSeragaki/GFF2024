#include "PauseButton.h"
#include "DxLib.h"
#include "../../../UtilityFile/ResourceManager.h"

PauseButton::PauseButton()
{
	location.x = 0.0f;
	location.y = 0.0f;
	can_hit = true;
	object_type = ObjectType::pausebutton;
	shape = Shape::square;
	width = 50.0f;
	height = 50.0f;

	is_pause = false;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// ポーズボタン画像を読み込む
	tmp = rm->GetImages("Resource/Images/Pause/PauseButton.png", 2, 2, 1, 16, 16);
	for (int i = 0; i < 2; i++)
	{
		button_image.push_back(tmp[i]);
	}

	// "遊び方"テキスト画像を読み込む
	tmp = rm->GetImages("Resource/Images/Pause/Text/HowToPlay.png");
	heading_image.push_back(tmp[0]);

	// 説明テキスト画像を読み込む
	tmp = rm->GetImages("Resource/Images/Pause/Text/Text.png", 5, 1, 5, 360, 64);
	for (int i = 0; i < 5; i++)
	{
		text_image.push_back(tmp[i]);
	}

	// 説明画像を読み込む
	tmp = rm->GetImages("Resource/Images/Pause/HelpImage.png", 5, 5, 1, 340, 340);
	for (int i = 0; i < 5; i++)
	{
		help_image.push_back(tmp[i]);
	}

	// マウス画像を読み込む
	tmp = rm->GetImages("Resource/Images/Pause/Mouse.png", 2, 2, 1, 30, 48);
	for (int i = 0; i < 2; i++)
	{
		mouse_image.push_back(tmp[i]);
	}

	// マウスのアピール画像
	tmp = rm->GetImages("Resource/Images/Pause/Appeal.png");
	appeal_image.push_back(tmp[0]);

	image_num = 0;
	page_num = 0;
	mouse_image_num = 0;
	animation_count = 0;

	cursor_overlap_flg = false;
}

PauseButton::~PauseButton()
{

}

void PauseButton::Initialize()
{

}

void PauseButton::Update()
{
	cursor_overlap_flg = false;

	if (is_pause == false)
	{
		// 画像を停止ボタンにする
		image_num = 0;

		if (page_num != 0)
		{
			// ページを0に戻す
			page_num = 0;
			animation_count = 0;
			mouse_image_num = 0;
		}
	}
	else
	{
		// 画像を再生ボタンにする
		image_num = 1;

		// マウスのアニメーション処理
		if (page_num <= 2)
		{
			if (animation_count < 30)
			{
				animation_count++;
			}
			else
			{
				animation_count = 0;

				if (mouse_image_num < 1)
				{
					mouse_image_num++;
				}
				else
				{
					mouse_image_num = 0;
				}
			}
		}
		else
		{
			animation_count = 0;
			mouse_image_num = 0;
		}
	}
}

void PauseButton::Draw() const
{
	if (is_pause)
	{
		// 灰色背景
		DrawBoxAA(0.0f, 0.0f, 360.0f, 700.0f, 0xdddddd, TRUE);

		// "遊び方"テキスト画像描画
		DrawRotaGraphF(180.0f, 50.0f, 1.0, 0.0, heading_image[0], TRUE);
		DrawLineAA(100.0f, 75.0f, 260.0f, 75.0f, 0x000000, 2.0f);

		// 説明テキスト画像描画
		DrawRotaGraphF(180.0f, 150.0f, 1.0, 0.0, text_image[page_num], TRUE);

		// 説明画像描画
		DrawRotaGraphF(180.0f, 370.0f, 1.0, 0.0, help_image[page_num], TRUE);
		DrawBoxAA(10.0f, 200.0f, 350.0f, 540.0f, 0x222222, FALSE, 2.0f);

		if (page_num <= 2)
		{
			// マウス画像の描画
			DrawRotaGraphF(330.0f, 510.0f, 1.0, 0.0, mouse_image[mouse_image_num], TRUE);

			if (mouse_image_num == 0)
			{
				// マウスのアピール画像の描画
				DrawRotaGraphF(310.0f, 490.0f, 1.0, 0.0, appeal_image[0], TRUE);
			}
		}

		for (int i = 0; i < 5; i++)
		{
			if (i != page_num)
			{
				// 黒丸
				DrawCircleAA(140.0f + i * 20.0f, 560.0f, 5, 32, 0x000000, TRUE);
			}
			else
			{
				// 白丸
				DrawCircleAA(140.0f + i * 20.0f, 560.0f, 5, 32, 0xffffff, TRUE);
				DrawCircleAA(140.0f + i * 20.0f, 560.0f, 5, 32, 0x000000, FALSE, 1.0f);
			}
		}
	}

	//DrawLineAA(180.0f, 0.0f, 180.0f, 800.0f, 0xff0000, 1.0f);

	// ポーズボタン画像の描画
	DrawRotaGraphF(location.x, location.y, 3.0, 0.0, button_image[image_num], TRUE);

	// カーソルがポーズボタンに重なっていたら
	if (cursor_overlap_flg)
	{
		// ポーズボタンを暗くする
		// 描画輝度のセット
		SetDrawBright(128, 128, 128);
		// ポーズボタン画像の描画
		DrawRotaGraphF(location.x, location.y, 3.0, 0.0, button_image[image_num], TRUE);
		// 描画輝度を元に戻す
		SetDrawBright(255, 255, 255);
	}
}

void PauseButton::HitReaction(ObjectBase* character)
{
	if (character->GetObjectType() == ObjectType::cursor)
	{
		if (is_pause == false)
		{
			// 一時停止にする
			is_pause = true;
		}
		else
		{
			// 一時停止を解除する
			is_pause = false;
		}
	}
}

bool PauseButton::GetPauseFlg() const
{
	return is_pause;
}

void PauseButton::SetPage(bool change_left)
{
	if (change_left)
	{
		// 前のページへ
		this->page_num--;

		if (this->page_num < 0)
		{
			// 最後のページにする
			this->page_num = 4;
		}
	}
	else
	{
		// 次のページへ
		this->page_num++;

		if (this->page_num > 4)
		{
			// 最初のページにする
			this->page_num = 0;
		}
	}
}