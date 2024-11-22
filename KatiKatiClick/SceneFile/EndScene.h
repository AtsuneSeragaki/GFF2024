#pragma once

#include "AbstractScene.h"

class EndScene : public AbstractScene
{
private:
	int cnt;

public:
	EndScene();
	~EndScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};
