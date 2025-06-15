
#include "lcd.h"
#include "bmp.h"
#include "touch.h"

#include <stdio.h>
#include <unistd.h>

/* 
	argv[]：输入要进行循环播放图片的文件夹。“幻灯片的保存地址”
*/

int main(int argc, char * argv[] )		//程序入口	 
{
	//1.初始化屏幕 
	lcd_init();


	//2.操作 ---> 进行功能调用

		//显示一张纯色的图像 --> 清屏效果
		//show_a_pure_color( 0xFFFFFF );

		//矩形 
		//display_Rectangle( 200, 200, 100, 100, 0xFF0000 );

 
		//显示bmp图片 
		//show_bmp( 0, 0, "1.bmp" );
		//show_bmp( 100, 100, "1.bmp" );
		//show_bmp_dynamic_v1( "1.bmp" );

		//读取当前目录下所有的bmp图片，进行循环显示
		Circle_show_bmp( "./picture/backgraund/" );
/* 
		//触摸屏
		while( 1 )
		{
			//触摸坐标
			//get_touch();

			//滑动方向
			int fx = get_direction();
			printf("fx = %d\n", fx );
		}
	
 */
	//3.关闭屏幕
	lcd_close();
}


