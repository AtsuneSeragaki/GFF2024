#pragma once
#include "../UtilityFile//Geometry.h"

enum class ObjectType
{
	null,//初期化
	cursor,
	enemy,
	skill
};

class ObjectBase
{
protected:

	float radius;//半径
	bool can_hit;//当たり判定を行っていいか？
	Vector2D location;		// 座標
	ObjectType object_type;//自分のtypeを入れる
	bool is_delete;//消していいか


public:
	ObjectBase();
	~ObjectBase();

	virtual void initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() const = 0;
	virtual void HitReaction(ObjectBase* character) = 0; //hitCheckがtrueだったらhitした後の処理をする

	//丸と丸の当たり判定:何かに当たったかどうかだけ返す
	bool HitCheck(Vector2D other_obj, float other_radius);

	ObjectType GetObjectType();//typeを返す
	bool GetCanHit();//当たり判定をしてもいいかを返す
	float GetRadius();//半径を返す
	bool GetIsDelete();//is_deleteを返す

	const Vector2D& GetLocation() const;			// 座標を返す
	void SetLocation(const Vector2D& location);		// 生成座標の設定
};