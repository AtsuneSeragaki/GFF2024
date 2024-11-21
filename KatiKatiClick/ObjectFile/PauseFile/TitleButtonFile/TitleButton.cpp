#include "TitleButton.h"
#include "DxLib.h"
#include "../../../UtilityFile/ResourceManager.h"

TitleButton::TitleButton()
{
	location.x = 0.0f;
	location.y = 0.0f;
	can_hit = true;
	object_type = ObjectType::in_pausebutton;
	shape = Shape::square;
	width = 160.0f;
	height = 32.0f;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// "タイトルへ戻る"ボタン画像を読み込む
	tmp = rm->GetImages("Resource/Images/Pause/Button/TitleButton.png");
	button_image.push_back(tmp[0]);

	click_flg = false;
}

TitleButton::~TitleButton()
{

}

void TitleButton::Initialize()
{

}

void TitleButton::Update()
{

}

void TitleButton::Draw() const
{
	//DrawBoxAA(location.x - width/2, location.y - height/2, location.x + width/2, location.y + height/2, 0xff0000, FALSE);

	//  "タイトルへ戻る"ボタン画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, button_image[0], TRUE);
}

void TitleButton::HitReaction(ObjectBase* character)
{
	if (character->GetObjectType() == ObjectType::cursor)
	{
		click_flg = true;
	}
}

bool TitleButton::GetClickFlg() const
{
	return click_flg;
}