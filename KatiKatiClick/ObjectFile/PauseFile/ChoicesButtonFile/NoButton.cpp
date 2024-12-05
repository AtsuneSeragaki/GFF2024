#include "NoButton.h"
#include "DxLib.h"
#include "../../../UtilityFile/ResourceManager.h"

NoButton::NoButton()
{
	location.x = 0.0f;
	location.y = 0.0f;
	can_hit = true;
	object_type = ObjectType::choicebutton;
	shape = Shape::square;
	width = 90.0f;
	height = 40.0f;
	
	click_flg = false;
	cursor_overlap_flg = false;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// "いいえ"ボタン画像を読み込む
	tmp = rm->GetImages("Resource/Images/Pause/Button/NoButton.png", 2, 2, 1, 96, 40);
	for (int i = 0; i < 2; i++)
	{
		button_image.push_back(tmp[i]);
	}

	anim_count = 0;
	button_image_num = 0;
}

NoButton::~NoButton()
{

}

void NoButton::Initialize()
{

}

void NoButton::Update()
{
	cursor_overlap_flg = false;

	//if (click_flg)
	//{
	//	// 当たり判定なし
	//	can_hit = false;
	//}

	//// 押下アニメーション
	//if (can_hit == false)
	//{
	//	anim_count++;
	//	if (anim_count < 5)
	//	{
	//		// 押下時画像に変更
	//		button_image_num = 1;
	//	}
	//	else
	//	{
	//		anim_count = 0;
	//		button_image_num = 0;
	//		can_hit = true;
	//		click_flg = false;
	//	}
	//}
}

void NoButton::Draw() const
{
	//  "いいえ"ボタン画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, button_image[button_image_num], TRUE);

	// カーソルが "いいえ"ボタンに重なっていたら
	if (cursor_overlap_flg)
	{
		// ポーズボタンを暗くする
		// 描画輝度のセット
		SetDrawBright(128, 128, 128);
		//  "いいえ"ボタン画像の描画
		DrawRotaGraphF(location.x, location.y, 1.0, 0.0, button_image[button_image_num], TRUE);
		// 描画輝度を元に戻す
		SetDrawBright(255, 255, 255);
	}

	// 当たり判定確認
	//DrawBoxAA(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, 0x000000,FALSE, 1.0f);
}

void NoButton::HitReaction(ObjectBase* character)
{
	if (character->GetObjectType() == ObjectType::cursor)
	{
		click_flg = true;
	}
}