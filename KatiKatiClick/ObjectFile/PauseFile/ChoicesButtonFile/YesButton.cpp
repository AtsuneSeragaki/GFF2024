#include "YesButton.h"
#include "DxLib.h"
#include "../../../UtilityFile/ResourceManager.h"

YesButton::YesButton()
{
	location.x = 0.0f;
	location.y = 0.0f;
	can_hit = true;
	object_type = ObjectType::choicebutton;
	shape = Shape::square;
	width = 80.0f;
	height = 32.0f;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// "はい"ボタン画像を読み込む
	tmp = rm->GetImages("Resource/Images/Pause/Button/YesButton.png", 2, 2, 1, 80, 32);
	for (int i = 0; i < 2; i++)
	{
		button_image.push_back(tmp[i]);
	}

	// ダイアログボックス画像を読み込む
	tmp = rm->GetImages("Resource/Images/Pause/Button/DialogBox.png");
	box_image.push_back(tmp[0]);

	click_flg = false;

	cursor_overlap_flg = false;
	anim_count = 0;
	button_image_num = 0;
	going_title = false;
}

YesButton::~YesButton()
{

}

void YesButton::Initialize()
{

}

void YesButton::Update()
{
	cursor_overlap_flg = false;

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
			going_title = true;
		}
	}
}

void YesButton::Draw() const
{
	// 描画ブレンドモードをアルファブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	// 黒色四角
	DrawBoxAA(0.0f, 0.0f, 360.0f, 800.0f, 0x000000, TRUE);
	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//  ダイアログボックス画像の描画
	DrawRotaGraphF(180.0f, 300.0f, 1.0, 0.0, box_image[0], TRUE);

	//  "はい"ボタン画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, button_image[button_image_num], TRUE);

	// カーソルが "はい"ボタンに重なっていたら
	if (cursor_overlap_flg)
	{
		// ポーズボタンを暗くする
		// 描画輝度のセット
		SetDrawBright(128, 128, 128);
		//  "はい"ボタン画像の描画
		DrawRotaGraphF(location.x, location.y, 1.0, 0.0, button_image[0], TRUE);
		// 描画輝度を元に戻す
		SetDrawBright(255, 255, 255);
	}
}

void YesButton::HitReaction(ObjectBase* character)
{
	if (character->GetObjectType() == ObjectType::cursor)
	{
		click_flg = true;
	}
}

bool YesButton::GetGoingTitleFlg() const
{
	return going_title;
}
