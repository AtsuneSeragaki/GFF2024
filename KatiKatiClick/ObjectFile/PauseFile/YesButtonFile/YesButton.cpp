#include "YesButton.h"
#include "DxLib.h"
#include "../../../UtilityFile/ResourceManager.h"

YesButton::YesButton()
{
	location.x = 0.0f;
	location.y = 0.0f;
	can_hit = true;
	object_type = ObjectType::yesbutton;
	shape = Shape::square;
	width = 81.0f;
	height = 32.0f;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// "はい"ボタン画像を読み込む
	tmp = rm->GetImages("Resource/Images/Pause/Button/YesButton.png");
	button_image.push_back(tmp[0]);

	// "いいえ"ボタン画像を読み込む
	tmp = rm->GetImages("Resource/Images/Pause/Button/NoButton.png");
	button_image.push_back(tmp[0]);

	// ダイアログボックス画像を読み込む
	tmp = rm->GetImages("Resource/Images/Pause/Button/DialogBox.png");
	button_image.push_back(tmp[0]);

	click_flg = false;

	no_button_location_x = 260.0f;
	no_button_location_y = 330.0f;
}

YesButton::~YesButton()
{

}

void YesButton::Initialize()
{

}

void YesButton::Update()
{

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
	DrawRotaGraphF(180.0f, 300.0f, 1.0, 0.0, button_image[2], TRUE);

	//  "はい"ボタン画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, button_image[0], TRUE);

	//  "いいえ"ボタン画像の描画
	DrawRotaGraphF(no_button_location_x, no_button_location_y, 1.0, 0.0, button_image[1], TRUE);
}

void YesButton::HitReaction(ObjectBase* character)
{
	if (character->GetObjectType() == ObjectType::cursor)
	{
		click_flg = true;
	}
}

bool YesButton::GetClickFlg() const
{
	return click_flg;
}
