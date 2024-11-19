#include "PauseButton.h"
#include "DxLib.h"
#include "../../UtilityFile/ResourceManager.h"

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
	cursor_x = 0.0f;
	cursor_y = 0.0f;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	//// はてな画像を読み込む
	//tmp = rm->GetImages("Resource/Images/Question3.png");
	//question_image.push_back(tmp[0]);

	// ポーズボタン画像を読み込む
	tmp = rm->GetImages("Resource/Images/Pause/PauseButton.png", 2, 2, 1, 16, 16);
	for (int i = 0; i < 2; i++)
	{
		button_image.push_back(tmp[i]);
	}

	image_num = 0;
	change_location = false;
}

PauseButton::~PauseButton()
{

}

void PauseButton::Initialize()
{

}

void PauseButton::Update()
{
	if (is_pause == false)
	{
		// 画像を停止ボタンにする
		image_num = 0;

		//if (change_location)
		//{
		//	location.x = 320.0f;
		//	location.y = 590.0f;
		//	change_location = false;
		//}
	}
	else
	{
		// 画像を再生ボタンにする
		image_num = 1;

		//if (change_location)
		//{
		//	location.x = 180.0f;
		//	location.y = 700.0f;
		//	change_location = false;
		//}
	}
}

void PauseButton::Draw() const
{
	//DrawBoxAA(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, 0xc0c0c0, TRUE);
	//DrawFormatStringF(location.x - 20.0f, location.y - 10.0f, 0x000000, "PAUSE");

	if (is_pause == false)
	{
		//DrawBoxAA(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, 0xc0c0c0, TRUE);
		//DrawFormatStringF(location.x - 20.0f, location.y - 10.0f, 0x000000, "PAUSE");
	}
	else
	{
		//DrawFormatStringF(location.x - 20.0f, location.y - 10.0f, 0x666666, "PAUSE");

		//// ボックス
		//DrawBoxAA(location.x - width / 2, location.y + height / 2, location.x + width / 2, location.y + height / 2 + 60.0f, 0xc0c0c0, TRUE);
		//DrawBoxAA(location.x - width / 2, location.y + height / 2, location.x + width / 2, location.y + height / 2 + 30.0f, 0xaa0000, FALSE);

		//DrawFormatStringF(300.0f, 65.0f, 0xaa0000, "HELP");

		//// ボックス
		//DrawBoxAA(location.x - width / 2, location.y + height / 2 + 60.0f, location.x + width / 2, location.y + height / 2 + 120.0f, 0xc0c0c0, TRUE);
		//DrawBoxAA(location.x - width / 2, location.y + height / 2 + 60.0f, location.x + width / 2, location.y + height / 2 + 120.0f, 0x0000aa, FALSE);

		//DrawFormatStringF(300.0f, 125.0f, 0x0000aa, "TITLE");





		 DrawBoxAA(0.0f, 0.0f, 360.0f, 560.0f, 0xdddddd, TRUE);

		DrawFormatStringF(160.0f, 50.0f, 0x000000, "HELP");
		DrawFormatStringF(150.0f, 500.0f, 0x000000, "TITLE");

		//DrawBoxAA(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, 0xc0c0c0, TRUE);
		//DrawFormatStringF(location.x - 20.0f, location.y - 10.0f, 0xee0000, "PAUSE");
	}

	//DrawBoxAA(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, 0x000000, FALSE, 2.0f);

	// ポーズボタン画像の描画
	DrawRotaGraphF(location.x, location.y, 3.0, 0.0, button_image[image_num], TRUE);
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

		// ボタンの位置を変更
		// change_location = true;
	}
}

bool PauseButton::GetPauseFlg() const
{
	return is_pause;
}
