#include "EnemyBase.h"

void EnemyBase::MoveShapeChange()
{
	//５カウントずつ幅の大きさを変えて歩いているように
	if (shape_change_cnt++ > 5)
	{
		shape_change_cnt = 0;
		if (shape_change_x == 0)
		{
			shape_change_x = 3;
			shape_change_y = 2;
		}
		else if (shape_change_y == 2)
		{
			shape_change_y = 5;
		}
		else
		{
			shape_change_x = 0;
			shape_change_y = 0;
		}
	}

}
