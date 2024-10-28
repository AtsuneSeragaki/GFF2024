#pragma once
#include "AbstractScene.h"
#include "DxLib.h"
#include "../ObjectFile/EnemyFile/CrackEnemy.h"
#include "../ObjectFile/EnemyFile/BurstEnemy.h"
#include "../ObjectFile/PlayerFile/Cursor.h"
#include "../UtilityFile/Define.h"
#include "../ObjectFile/CoinFile/Coin.h"
#include "../UtilityFile/Geometry.h"
#include "../ObjectFile/UIFile/UICoins.h"
#include <vector>
#include "../ObjectFile/SkillFile/AttackSkill.h"
#include "../ObjectFile/SkillFile/SlowDownSkill.h"

class GameMainScene :
    public AbstractScene
{
private:
	CrackEnemy* crackenemy;
	ObjectBase* check_virtual;
	std::vector<ObjectBase*> objects;
	std::vector<Coin*> coins;
	UICoins* ui_coins;
public:
	GameMainScene();
	~GameMainScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;

private:
	void Initialize();
	void EnemyGenerate();
	void CoinGenerate(int i, int j);

protected:
	template <class T>
	T* CreateObject()
	{
		T* new_instance = new T();

		ObjectBase* new_object = dynamic_cast<ObjectBase*>(new_instance);

		if (new_object == nullptr)
		{
			delete new_instance;
			throw("ゲームオブジェクトが生成できませんでした\n");
		}

		objects.push_back(new_object);
		return new_instance;
	}
	
private:
	AttackSkill* attackskill;
	SlowDownSkill* slowdownskill;

};

