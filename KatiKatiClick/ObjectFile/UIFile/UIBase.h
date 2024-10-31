#pragma once

class UIBase
{
public:
	UIBase();
	~UIBase();

	virtual void Update() = 0;
	virtual void Draw() const = 0;
};