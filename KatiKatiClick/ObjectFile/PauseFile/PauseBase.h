#pragma once
#include "../ObjectBase.h"

class PauseBase : public ObjectBase
{
protected:
    bool click_flg;             // クリックされたか？
    bool cursor_overlap_flg;    // カーソルが重なったか？

public:
	PauseBase();
	~PauseBase();

    void Initialize() override;
    void Update()override;
    void Draw()const override;
    void HitReaction(ObjectBase* character) override;

    bool GetClickFlg() const;
    void SetCursorOverlapFlg();
};