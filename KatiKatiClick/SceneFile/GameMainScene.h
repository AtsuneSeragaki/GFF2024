#pragma once
#include "AbstractScene.h"
#include "DxLib.h"
#include "../ObjectFile/EnemyFile/SquishEnemy.h"
#include "../ObjectFile/PlayerFile/Cursor.h"
#include "../UtilityFile/Define.h"
#include <vector>

class GameMainScene :
    public AbstractScene
{
private:
	SquishEnemy* squishenemy;
	ObjectBase* check_virtual;
	std::vector<ObjectBase*> objects;
public:
	GameMainScene();
	~GameMainScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;

private:
	void EnemyGenerate();

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
	
};

