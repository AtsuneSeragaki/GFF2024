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
	width = 80.0f;
	height = 32.0f;
	
	click_flg = false;
	cursor_overlap_flg = false;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// "いいえ"ボタン画像を読み込む
	tmp = rm->GetImages("Resource/Images/Pause/Button/NoButton.png");
	button_image.push_back(tmp[0]);

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
}

void NoButton::Draw() const
{
	//  "いいえ"ボタン画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, button_image[0], TRUE);

	// カーソルが "いいえ"ボタンに重なっていたら
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

void NoButton::HitReaction(ObjectBase* character)
{

}