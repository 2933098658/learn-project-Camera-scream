
#include "touch.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <stdlib.h>


//获取手指触摸的坐标 
int get_touch( int *x, int *y  )
{
    //1.打开触摸屏 /dev/input/event0 
    int fd = open( "/dev/input/event0", O_RDWR );
    if( fd == -1 )
    {
        perror("open event0 error  ");
        return -1;
    }

    //2.读取输入事件的信息 
    int x0 = -1;
    int y0 = -1;

    struct input_event  ev;
    while( 1 )
    {
        //读取坐标信息 
        read( fd, &ev, sizeof(ev) );

        //解析坐标
        if( ev.type ==EV_ABS )      //触摸事件 
        {
            if( ev.code == ABS_X )  //x轴 
            {
                x0 = ev.value;
            }
            else if( ev.code == ABS_Y ) //y轴 
            {
                y0 = ev.value;
            }
            else if( ev.code == ABS_PRESSURE && ev.value == 0 )  //触摸屏压力事件
            {
                //退出条件，压力事件也压力为0 
                if( x0 != -1 && y0 != -1 )
                {
                    break;
                }
            }
        }
        else if( ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)    //按键事件 
        {
            //退出 
            if( x0 != -1 && y0 != -1 )
            {

                break;
            }
        }

    }

	//坐标换算：触摸屏(1024*600) / 显示屏(800*480)
	*x = x0 / 1.28;
	*y = y0 / 1.25;

    //打印
    printf("( %d , %d )\n", *x, *y );

    //关闭屏幕  
    close( fd );

}


/*
获取手指滑动的方向 
返回值： 
    1 上
    2 下
    3 左
    4 右
*/
int get_direction()
{
    //1.打开触摸屏 /dev/input/event0 
    int fd = open( "/dev/input/event0", O_RDWR );
    if( fd == -1 )
    {
        perror("open event0 error  ");
        return -1;
    }

    //2.读取输入事件的信息 
    int x0 = -1, y0 = -1;       //起点
    int x1 = -1, y1 = -1;       //终点

    struct input_event  ev;
    while( 1 )
    {
        //读取坐标信息 
        read( fd, &ev, sizeof(ev) );

        //解析坐标
        if( ev.type == EV_ABS )      //触摸事件 
        {
            if( ev.code == ABS_X )  //x轴 
            {
                if( x0 == -1 )      //起点还没赋值
                {
                    x0 = ev.value;
                }
                x1 = ev.value;      //后面所获取的坐标一直去更新终点
            }
            else if( ev.code == ABS_Y ) //y轴 
            {
                if( y0 == -1 )
                {
                    y0 = ev.value;
                }
                y1 = ev.value;
            }
            else if( ev.code == ABS_PRESSURE && ev.value == 0 )  //触摸屏压力事件
            {
                //退出条件，压力事件的压力为0 
                if( x0 != -1 && y0 != -1 )
                {
                    break;
                }
            }
        }
        else if( ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)    //按键事件 
        {
            //退出 
            if( x0 != -1 && y0 != -1 )
            {
                break;
            }
        }

    }

    //打印
    printf("( %d , %d ) --> ( %d , %d )\n", x0, y0, x1, y1 );

    //关闭屏幕  
    close( fd );

    //滑动方向的判定 
    int xx = abs( x0 - x1 );
    int yy = abs( y0 - y1 );

    if( xx > yy )   //水平方向 
    {
        if( x0 > x1 )   
        {
            return 3;   //左
        }
        else 
        {
            return 4;   //右
        }
    }
    else            //垂直方向 
    {
        if( y0 > y1 )
        {
            return 1;   //上
        }
        else 
        {
            return 2;   //下
        }
    }
}



