#pragma once
#include "../../ObjectBase.h"
#include <vector>

class LeftButton : public ObjectBase
{
private:
	std::vector<int> button_image;      // ボタン画像
	bool click_flg;						// クリックされたか？

public:
	LeftButton();
	~LeftButton();

	void Initialize() override;
	void Update()override;
	void Draw()const override;
	void HitReaction(ObjectBase* character) override;

	bool GetClickFlg() const;
};