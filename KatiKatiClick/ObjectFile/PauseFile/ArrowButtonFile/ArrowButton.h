#pragma once
#include "../../ObjectBase.h"
#include <vector>

class ArrowButton : public ObjectBase
{
private:
	std::vector<int> button_image;      // ボタン画像
	int direction;						// 矢印の向き 0: 左　1: 右

public:
	ArrowButton();
	~ArrowButton();

	void Initialize() override;
	void Update()override;
	void Draw()const override;
	void HitReaction(ObjectBase* character) override;

	void ChangeRightArrow();		// 右向き矢印に変更する
};