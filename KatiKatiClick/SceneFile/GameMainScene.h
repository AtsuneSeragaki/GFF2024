#pragma once
#include "AbstractScene.h"
#include "DxLib.h"
#include "../ObjectFile/EnemyFile/SquishEnemy.h"

class GameMainScene :
    public AbstractScene
{
private:
	SquishEnemy* squishenemy;
public:
	GameMainScene();
	~GameMainScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;

	
};

