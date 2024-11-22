#include "EndScene.h"

#include "DxLib.h"

EndScene::EndScene()
{
	cnt = 0;
}

EndScene::~EndScene()
{
}

void EndScene::Update()
{
	cnt++;
}

void EndScene::Draw() const
{
	DrawString(80, 400, "Thank you for playing!",0xffffff);
}

AbstractScene* EndScene::Change()
{
	if (cnt == 120)
	{
		return nullptr;
	}

	return this;
}
