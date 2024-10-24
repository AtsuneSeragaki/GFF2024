#pragma once
#include "DxLib.h"

struct Location
{
	float x;
	float y;
};

class Coin
{
private:
	Location location;

	bool can_delete;

public:
	Coin();
	~Coin();

	void Update();
	void Draw() const;

	bool GetCanDeleteFlg() const;
};