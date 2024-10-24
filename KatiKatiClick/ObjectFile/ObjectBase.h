#pragma once

struct Location
{
	float x;
	float y;
};

enum class ObjectType
{
	null,//初期化
	enemy,
	skill,
	cursor,
};

class ObjectBase
{
protected:

	float radius;//半径
	bool can_hit;//当たり判定を行っていいか？
	Location location;//座標
	ObjectType object_type;//自分のtypeを入れる
	bool can_delete;//消していいか

public:
	ObjectBase();
	~ObjectBase();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() const = 0;
	virtual void HitReaction(ObjectBase* character) = 0; //hitCheckがtrueだったらhitした後の処理をする

	//丸と丸の当たり判定:何かに当たったかどうかだけ返す
	bool HitCheck(Location other_obj, float other_radius);

	Location GetLocation();//座標を返す
	ObjectType GetObjectType();//typeを返す
	bool GetCanHit();//当たり判定をしてもいいかを返す
	float GetRadius();//半径を返す
	bool GetIsDelete();//is_deleteを返す
};