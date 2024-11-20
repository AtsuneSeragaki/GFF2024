#include "TitleScene.h"

#include "../UtilityFile/MouseInput.h"
#include "DxLib.h"

TitleScene::TitleScene()
{
	x1 = 75;
	x2 = 255;
	y1 = 300;
	y2 = 300;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
}

void TitleScene::Draw() const
{
	DrawBox(x1 - BOX_WIDTH / 2, y1 - BOX_HEIGHT / 2, x1 + BOX_WIDTH / 2, y1 + BOX_HEIGHT / 2, 0xffffff, TRUE);
	DrawString(x1, y1, "START", 0x000000);
	DrawBox(x2 - BOX_WIDTH / 2, y2 - BOX_HEIGHT / 2, x2 + BOX_WIDTH / 2, y2 + BOX_HEIGHT / 2, 0xffffff, TRUE);
	DrawString(x2, y2, "END", 0x000000);
}

AbstractScene* TitleScene::Change()
{
	return this;
}
