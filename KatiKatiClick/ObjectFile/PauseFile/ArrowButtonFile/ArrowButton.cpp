#include "ArrowButton.h"
#include "DxLib.h"
#include "../../../UtilityFile/ResourceManager.h"

ArrowButton::ArrowButton()
{
	location.x = 0.0f;
	location.y = 0.0f;
	can_hit = true;
	object_type = ObjectType::pausebutton;
	shape = Shape::square;
	width = 50.0f;
	height = 50.0f;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// ボタン画像を読み込む
	tmp = rm->GetImages("Resource/Images/Pause/Button/ArrowButton.png", 2, 2, 1, 16, 16);
	for (int i = 0; i < 2; i++)
	{
		button_image.push_back(tmp[i]);
	}

	direction = 0;			// 左向き矢印ボタン
}

ArrowButton::~ArrowButton()
{

}

void ArrowButton::Initialize()
{

}

void ArrowButton::Update()
{

}

void ArrowButton::Draw() const
{
	// 矢印ボタン画像の描画
	DrawRotaGraphF(location.x, location.y, 3.0, 0.0, button_image[direction], TRUE);
}

void ArrowButton::HitReaction(ObjectBase* character)
{
	if (character->GetObjectType() == ObjectType::cursor)
	{
		if (direction == 0)
		{
			// 左向き矢印
			direction = 1;
		}
		else
		{
			// 右向き矢印
			direction = 0;
		}
	}

}

void ArrowButton::ChangeRightArrow()
{
	this->direction = 1;
}