#include "LeftButton.h"
#include "DxLib.h"
#include "../../../UtilityFile/ResourceManager.h"

LeftButton::LeftButton()
{
	location.x = 0.0f;
	location.y = 0.0f;
	can_hit = true;
	object_type = ObjectType::in_pausebutton;
	shape = Shape::circle;
	radius = 20.0f;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// ボタン画像を読み込む
	tmp = rm->GetImages("Resource/Images/Pause/Button/ButtonWhite.png", 2, 2, 1, 16, 16);
	for (int i = 0; i < 2; i++)
	{
		button_image.push_back(tmp[i]);
	}

	// 矢印画像を読み込む
	tmp = rm->GetImages("Resource/Images/Pause/Button/Arrow.png");
	arrow_image.push_back(tmp[0]);

	click_flg = false;
	cursor_overlap_flg = false;

	anim_count = 0;
	button_image_num = 0;
}

LeftButton::~LeftButton()
{

}

void LeftButton::Initialize()
{

}

void LeftButton::Update()
{
	cursor_overlap_flg = false;

	if (click_flg)
	{
		// 当たり判定なし
		can_hit = false;

		click_flg = false;
	}

	// 押下アニメーション
	if (can_hit == false)
	{
		anim_count++;
		if (anim_count < 5)
		{
			// 押下時画像に変更
			button_image_num = 1;
		}
		else
		{
			anim_count = 0;
			button_image_num = 0;
			can_hit = true;
		}
	}
}

void LeftButton::Draw() const
{
	if (cursor_overlap_flg == false)
	{
		// 矢印ボタン画像の描画
		DrawRotaGraphF(location.x, location.y, 3.0, 0.0, button_image[button_image_num], TRUE);
		DrawRotaGraphF(location.x, location.y, 2.8, 0.0, arrow_image[0], TRUE);
	}
	else
	{
		// カーソルが矢印ボタンに重なっていたら
		// ポーズボタンを暗くする
		// 描画輝度のセット
		SetDrawBright(160, 160, 160);
		// 矢印ボタン画像の描画
		DrawRotaGraphF(location.x, location.y, 3.0, 0.0, button_image[button_image_num], TRUE);
		DrawRotaGraphF(location.x, location.y, 2.8, 0.0, arrow_image[0], TRUE);
		// 描画輝度を元に戻す
		SetDrawBright(255, 255, 255);
	}

	//DrawCircleAA(location.x, location.y, radius, 32, 0xff0000f, FALSE);
}

void LeftButton::HitReaction(ObjectBase* character)
{
	if (character->GetObjectType() == ObjectType::cursor)
	{
		click_flg = true;
	}
}