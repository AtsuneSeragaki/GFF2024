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
	{0,1,0,1,0},
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
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,3,0,3,0},
	{1,0,1,0,1},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{4,0,5,0,4},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{2,0,2,0,2},
	{0,0,0,0,0},
	{0,3,0,3,0},
	{1,0,0,0,1},
	{0,1,0,1,0},
};

/*
* 	0:None,
	1:CrackEnemy,
	2:SplitEnemy,
	3:BurstEnemy,
	4:FrogEnemy,
	5:SnakeEnemy,
*/