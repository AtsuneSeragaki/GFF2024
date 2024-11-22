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

	click_flg = false;
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
	//  "タイトルへ戻る"ボタン画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, button_image[0], TRUE);
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
