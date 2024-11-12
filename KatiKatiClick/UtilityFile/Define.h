#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

#define OBJECT_MAX_NUM 100

#define Sqiosh_Enemy_MAX 20

#define SCREEN_WIDTH 360

#define SCREEN_HEIGHT 800

#define ONE_LANE_HEIGHT (SCREEN_HEIGHT / 10)//横切りのレーンの高さ

#define GET_LANE_HEIGHT(num) (ONE_LANE_HEIGHT*num)

#define LANE_WIDTH_NUM 3//レーンの数

#define LANE_WIDTH (SCREEN_WIDTH / LANE_WIDTH_NUM)//１レーンの幅をもらう

#define LANE_WIDTH_HALF (LANE_WIDTH / 2)

//デグリーからラジアンに変換
#define DEGREE_RADIAN(_deg) (M_PI*(_deg)/180.0)
