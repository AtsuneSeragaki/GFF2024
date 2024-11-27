#pragma once
#include <vector>
#include "../ObjectFile/ObjectBase.h"

class OpeningAnim
{
private:
	std::vector<ObjectBase*> objects;

	std::vector<std::vector<int>> op_enm_array;
	std::vector<int> pizza_img;
	Vector2D pizza_pos;
	int pizza_angle;
	int anim_num;
	bool anim_end;

public:
	OpeningAnim();
	~OpeningAnim();

	void Update();
	void Draw() const;
	void PizzaFall();

protected:
	template <class T>
	T* CreateObject(Vector2D set_location)
	{
		T* new_instance = new T();

		ObjectBase* new_object = dynamic_cast<ObjectBase*>(new_instance);

		if (new_object == nullptr)
		{
			delete new_instance;
			throw("ゲームオブジェクトが生成できませんでした\n");
		}

		objects.push_back(new_object);
		objects.back()->SetLocation(set_location);
		return new_instance;
	}
};
