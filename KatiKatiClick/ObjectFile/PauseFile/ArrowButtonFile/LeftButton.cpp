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
	tmp = rm->GetImages("Resource/Images/Pause/Button/LeftButton.png");
	button_image.push_back(tmp[0]);

	click_flg = false;
	cursor_overlap_flg = false;
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
		click_flg = false;
	}
}

void LeftButton::Draw() const
{
	// 矢印ボタン画像の描画
	DrawRotaGraphF(location.x, location.y, 2.5, 0.0, button_image[0], TRUE);

	// カーソルが 矢印ボタンに重なっていたら
	if (cursor_overlap_flg)
	{
		// ポーズボタンを暗くする
		// 描画輝度のセット
		SetDrawBright(128, 128, 128);
		//  "はい"ボタン画像の描画
		DrawRotaGraphF(location.x, location.y, 2.5, 0.0, button_image[0], TRUE);
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