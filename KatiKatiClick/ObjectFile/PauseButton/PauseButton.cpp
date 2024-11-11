#include "PauseButton.h"
#include "DxLib.h"
#include "../../UtilityFile/ResourceManager.h"

PauseButton::PauseButton()
{
	location.x = 0.0f;
	location.y = 0.0f;
	can_hit = true;
	object_type = ObjectType::pausebutton;
	shape = Shape::square;
	width = 50.0f;
	height = 50.0f;

	is_pause = false;
	cursor_x = 0.0f;
	cursor_y = 0.0f;

	// ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	// はてな画像を読み込む
	tmp = rm->GetImages("Resource/Images/Question.png");
	question_image.push_back(tmp[0]);
}

PauseButton::~PauseButton()
{

}

void PauseButton::Initialize()
{

}

void PauseButton::Update()
{
	//if (is_pause)
	//{
	//	// カーソル位置の更新
	//	int x, y;
	//	GetMousePoint(&x, &y);
	//	cursor_x = (float)x;
	//	cursor_y = (float)y;

	//}
}

void PauseButton::Draw() const
{
	DrawBoxAA(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, 0xc0c0c0, TRUE);

	if (is_pause)
	{
		DrawFormatStringF(location.x - 20.0f, location.y - 10.0f, 0xee0000, "PAUSE");
	}
	else
	{
		DrawFormatStringF(location.x - 20.0f, location.y - 10.0f, 0x000000, "PAUSE");
	}


	// はてな画像の描画
	//DrawRotaGraphF(location.x, location.y, 1.0, 0.0, question_image[0], TRUE);

	//if (is_pause)
	//{
	//	// カーソル仮表示
	//	DrawCircleAA(location.x, location.y, radius, 32, 0x00ffff, TRUE);
	//}
}

void PauseButton::HitReaction(ObjectBase* character)
{
	if (character->GetObjectType() == ObjectType::cursor)
	{
		if (is_pause == false)
		{
			// 一時停止にする
			is_pause = true;
		}
		else
		{
			// 一時停止を解除する
			is_pause = false;
		}
	}
}

bool PauseButton::GetPauseFlg() const
{
	return is_pause;
}
