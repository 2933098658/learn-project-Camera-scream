
#ifndef __TOUCH_H__
#define __TOUCH_H__

//坐标
typedef struct Point
{
	int x;
	int y;
} Point ;

//其它地方去获取触摸坐标的方法：（3种）
//Point get_touch();		//构造新类型，返回值
//int get_touch( int *x, int *y );		//传参 
// 全局变量 

int get_touch( int *x, int *y );

int get_direction();



#endif


