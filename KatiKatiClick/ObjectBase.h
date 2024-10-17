#pragma once

class ObjectBase
{
protected:
	struct Location
	{
		float x;
		float y;
	};

	enum class ObjectType
	{
		null,//初期化
		mouse,
		enemy,
		skill
	};

	float radius;//半径
	bool can_hit;//当たり判定を行っていいか？
	Location location;//座標
	ObjectType object_type;//自分のtypeを入れる


public:
	ObjectBase()
	{
		location = { 0.0f };
		radius = 0.0f;
		can_hit = false;
		object_type = ObjectType::null;
	}
	~ObjectBase()
	{
	};


	virtual void Update() = 0;
	virtual void Draw() const = 0;
	virtual void HitReaction(ObjectBase* character) = 0; //hitCheckがtrueだったらhitした後の処理をする

	//丸と丸の当たり判定:何かに当たったかどうかだけ返す
	bool HitCheck()
	{
	}

	Location GetLocation() { return location; }//座標を返す
	ObjectType GetObjectType() { return object_type; }//typeを返す
	bool GetCanHit() { return can_hit; }

};