#pragma once
#include <vector>

enum class Enemys
{
	None,
	CrackEnemy,
	SplitEnemy,
	BurstEnemy,
	FrogEnemy,
	SnakeEnemy,
};


std::vector<std::vector<int>> enemy_array =
{
	{0,1,3,1,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,4,0,0},
	{0,0,0,0,0},
	{4,0,0,0,4},
	{0,0,0,0,0},
	{0,0,0,3,0},
	{0,3,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,5},
	{5,0,0,0,0},
	{0,0,0,0,0},
	{0,2,0,2,0},
};
