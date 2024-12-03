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
	double pizza_angle;
	int pizza_se;
	int se_cnt;//se鳴らす間
	bool se_flg;
	int anim_num;
	bool anim_end;
	float check_enm_y;
	int enm_se;//エネミーのSE
	int display_num;

	std::vector<int> smoke_img;
	int right_smoke_num;
	int left_smoke_num;
	Vector2D right_smoke_pos;
	Vector2D left_smoke_pos;
	int smoke_cnt;
	std::vector<int> skip_img;//文字表示用

public:
	OpeningAnim();
	~OpeningAnim();

	void Update();
	void Draw() const;
	void PizzaFall();
	bool GetAnimEnd() { return anim_end; }
	int GetDisplay_num(){ return display_num; }

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
