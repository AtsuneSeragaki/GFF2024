#pragma once
class AbstractScene
{
public:
	virtual ~AbstractScene() {};
	int change;
	virtual void Finalize() {}

	virtual void Update() = 0;
	virtual void Draw() const = 0;
	virtual AbstractScene* Change() = 0;
};