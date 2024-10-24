#pragma once

class Vector2D
{
public:
	float x;
	float y;

public:
	Vector2D() : x(0.0f), y(0.0f) {}
	Vector2D(float s) : x(s), y(s) {}
	Vector2D(float sx, float sy) : x(sx), y(sy) {}
	~Vector2D() = default;
};