#include "RightButton.h"
#include "DxLib.h"
#include "../../../UtilityFile/ResourceManager.h"

RightButton::RightButton()
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
	tmp = rm->GetImages("Resource/Images/Pause/Button/RightButton.png");
	button_image.push_back(tmp[0]);
}

RightButton::~RightButton()
{

}

void RightButton::Initialize()
{

}

void RightButton::Update()
{

}

void RightButton::Draw() const
{
	// 矢印ボタン画像の描画
	DrawRotaGraphF(location.x, location.y, 2.5, 0.0, button_image[0], TRUE);

	//DrawCircleAA(location.x, location.y, radius, 32, 0xff0000f, FALSE);
}

void RightButton::HitReaction(ObjectBase* character)
{
	if (character->GetObjectType() == ObjectType::cursor)
	{

	}
}