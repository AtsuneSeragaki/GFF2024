#pragma once
#include "../../ObjectBase.h"
#include <vector>

class RightButton : public ObjectBase
{
private:
	std::vector<int> button_image;      // ボタン画像

public:
	RightButton();
	~RightButton();

	void Initialize() override;
	void Update()override;
	void Draw()const override;
	void HitReaction(ObjectBase* character) override;

};

