
#include "bmp.h"
#include "touch.h"

#include "lcd.h"
#include "bilinklist.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>


//显示bmp图片 
int show_bmp( int x0, int y0, char * filename )
{
    //1.打开图片文件 
    int fd = open( filename, O_RDWR );
    if( fd == -1 )
    {
        perror("open bmp error ");
        return -1;
    }

    //2.读取文件 
        //读取 宽、高、色深 
        int width = 0;  
        lseek( fd, 0x12, SEEK_SET );
        read( fd, &width, 4 );

        int height = 0;
        lseek( fd, 0x16, SEEK_SET );
        read( fd, &height, 4 );

        short depth = 0;
        lseek( fd, 0x1C, SEEK_SET );
        read( fd, &depth, 2 );
            
        //读取 像素点的颜色数据 
        int line_size = 0;      //一行实际的字节数 
        int laizi = 0;          //填充的字节数 

        laizi = 4 - ( abs(width) * (depth/8) ) % 4;
        if( laizi == 4 )
        {
            laizi = 0;
        }

        //一行实际的字节数： 有效字节数 + 填充字节数 
        line_size = abs(width) * (depth/8) + laizi;

        //一次性将图像的像素点数据 全部读取出来 
        unsigned char buf[ abs(height) * line_size ];
        lseek( fd, 0x36, SEEK_SET );
        read( fd, buf, abs(height) * line_size );

    //3.显示  
    int i,j;
    int color;
    int num = 0;
    unsigned a,r,g,b;

    for( j=0; j<abs(height); j++ )
    {
        for( i=0; i<abs(width); i++ )
        {
            //合成颜色值 
            b = buf[num++];
            g = buf[num++];
            r = buf[num++];
            if( depth == 32 )
            {
                a = buf[num++];
            }
            else 
            {
                a = 0;
            }
            color = (a<<24) | (r<<16) | (g<<8) | b;

            //画点 
            display_point(  width>0 ? i+x0 : abs(width)-1-i+x0 , 
                            height>0 ? abs(height)-1-j+y0 : j+y0 , 
                            color );
        }
        num = num + laizi;
    }        
    
    //4.关闭图片文件 
    close( fd );
}

/* 
    以动圆形态效果输出图片
*/
int show_bmp_dynamic_v1( char * filename )
{
	//1.打开图片文件 
    int fd = open( filename, O_RDWR );
    if( fd == -1 )
    {
        perror("open bmp error ");
        return -1;
    }

    //2.读取文件 
        //读取 宽、高、色深 
        int width = 0;  
        lseek( fd, 0x12, SEEK_SET );
        read( fd, &width, 4 );

        int height = 0;
        lseek( fd, 0x16, SEEK_SET );
        read( fd, &height, 4 );

        short depth = 0;
        lseek( fd, 0x1C, SEEK_SET );
        read( fd, &depth, 2 );
            
        //读取 像素点的颜色数据 
        int line_size = 0;      //一行实际的字节数 
        int laizi = 0;          //填充的字节数 

        laizi = 4 - ( abs(width) * (depth/8) ) % 4;
        if( laizi == 4 )
        {
            laizi = 0;
        }

        //一行实际的字节数： 有效字节数 + 填充字节数 
        line_size = abs(width) * (depth/8) + laizi;

        //一次性将图像的像素点数据 全部读取出来 
        unsigned char buf[ abs(height) * line_size ];
        lseek( fd, 0x36, SEEK_SET );
        read( fd, buf, abs(height) * line_size );

    //3.显示  
    int i,j;
    int color;
    int num = 0;
    unsigned a,r,g,b;

    int radius = 10;

    for( radius=10; radius<470; radius+=5 )
    {
		num = 0;
		
	    for( j=0; j<abs(height); j++ )
	    {
	        for( i=0; i<abs(width); i++ )
	        {
	            //合成颜色值 
	            b = buf[num++];
	            g = buf[num++];
	            r = buf[num++];
	            if( depth == 32 )
	            {
	                a = buf[num++];
	            }
	            else 
	            {
	                a = 0;
	            }
	            color = (a<<24) | (r<<16) | (g<<8) | b;

				//以圆形 从中间进行扩散
	        	if( (i-400)*(i-400) + (j-240)*(j-240) <= radius*radius )
	        	{
		            //画点
		            display_point(  width>0 ? i : abs(width)-1-i, 
		                            height>0 ? abs(height)-1-j: j, 
		                            color );
		        }
	        }
	        num = num + laizi;
	    }        
        show_bmp( 700, 50, "./picture/botten.bmp" ); 

    }
    
    //4.关闭图片文件 
    close( fd );
}
/* 
    以百叶窗动态显示图片
*/
int show_bmp_dynamic_v2( int x0, int y0, char * filename )
{
    //1.打开图片文件 
    int fd = open( filename, O_RDWR );
    if( fd == -1 )
    {
        perror("open bmp error ");
        return -1;
    }

    //2.读取文件 
        //读取 宽、高、色深 
        int width = 0;  
        lseek( fd, 0x12, SEEK_SET );
        read( fd, &width, 4 );

        int height = 0;
        lseek( fd, 0x16, SEEK_SET );
        read( fd, &height, 4 );

        short depth = 0;
        lseek( fd, 0x1C, SEEK_SET );
        read( fd, &depth, 2 );
            
        //读取 像素点的颜色数据 
        int line_size = 0;      //一行实际的字节数 
        int laizi = 0;          //填充的字节数 

        laizi = 4 - ( abs(width) * (depth/8) ) % 4;
        if( laizi == 4 )
        {
            laizi = 0;
        }

        //一行实际的字节数： 有效字节数 + 填充字节数 
        line_size = abs(width) * (depth/8) + laizi;

        //一次性将图像的像素点数据 全部读取出来 
        unsigned char buf[ abs(height) * line_size ];//此时的图片像素应该是480 * 2400个字符char大小
        lseek( fd, 0x36, SEEK_SET );
        read( fd, buf, abs(height) * line_size );

    //3.显示  
    int i,j;
    int color;
    int num = 0;
    unsigned a,r,g,b;
    int step = 96;//设置百叶窗显示的步距
    for(int check = 0 ; check < step ; check++)
    {
        for( j=0; j<abs(height); j++ )
        {
            if(j % step == check)
            {    
                num = j*line_size;
                for( i=0; i<abs(width); i++ )
                {
                    //合成颜色值 
                    b = buf[num++];
                    g = buf[num++];
                    r = buf[num++];
                    if( depth == 32 )
                    {
                        a = buf[num++];
                    }
                    else 
                    {
                        a = 0;
                    }
                    color = (a<<24) | (r<<16) | (g<<8) | b;

                    //画点 
                    display_point(  width>0 ? i+x0 : abs(width)-1-i+x0 , 
                                    height>0 ? abs(height)-1-j+y0 : j+y0 , 
                                    color );//这里的代码有一个抽象点：这里传递给画点函数的x值和y值应该根据color在图像中实际的像素点来确定。
                                    //这里的color很明显是帧缓冲中的第一个像素点。而在bmp图片中存储行为来看，第一个像素点就是原点的位置：即（0，0），也就是图片的左下角坐标
                                    //因为图片的像素高度和像素宽度都大于0，所以图片应该是位于第一象限的，首地址即左下角坐标。以行优先进行存储。
                                    //解释：画点函数是从左上角向右向下优先打印的，这是固定的，但是由于帧缓冲的像素顺序由像素高度及像素宽度的正负决定，所以打印位置也应该进行动态调整
                }
            }
        }
        show_bmp( 700, 50, "./picture/botten.bmp" );  
        usleep(15000);     
    }
    //4.关闭图片文件 
    close( fd );

}


//读取一个目录，将该目录下所有的bmp图片的路径名，全部保存到一个 双向链表中 
int get_bmp_name( char * pathname, struct Linklist * list )
{
    //1.打开目录 
    DIR * dir = opendir( pathname );
    if( dir == NULL )
    {
        perror("open dir error ");
        return -1;
    }

    //2.读取目录 
    struct dirent * d;
    while( d = readdir( dir ) )
    {
        //过滤 . 和 ..
        if( strcmp( d->d_name , "." ) == 0  || strcmp( d->d_name , ".." ) == 0  )
        {
            continue;
        }

        //合成路径名   "路径/文件名"
        char filename[128] = {0};
        strcpy( filename, pathname );       
        if( filename[ strlen(filename)-1 ] != '/' )
        {
            filename[ strlen(filename) ] = '/';
        }
        strcat( filename, d->d_name );


        if( d->d_type == DT_REG )  //普通文件 
        {
            //判断是否为bmp图片 （判断后缀名是否为 .bmp ）
            if( strcmp( filename + (strlen(filename)-4), ".bmp" ) == 0 )
            {
                //创建数据节点 
                Binode * pnew = create_binode( filename );

                //添加到链表中 
                tail_insert_binode( list, pnew );
            }
        }
        else if( d->d_type == DT_DIR )  //子目录，则继续去打开读取
        {
            //递归
            get_bmp_name( filename, list );
        } 
    }

    //关闭目录 
    closedir( dir );
}



//循环播放bmp图片 
int Circle_show_bmp( char * pathname )
{
    //创建双向链表 
    Bilinklist * list = create_bilinklist();

    //获取指定目录下的所有的bmp图片
    get_bmp_name( pathname, list );
    printf_bilinklist( list );	//打印链表

    //首尾相连 --> “循环链表”
    list->last->next = list->first;
    list->first->prev = list->last;

    struct binode *p = list->first;    //遍历指针

    int show = 1;
    int direc = 0;
    while( 1 )
    {
        //显示bmp  
        printf("bmp : %s\n", p->data );
        // switch(show)
        // {
        //     case 1:
        //     {   
//                show_bmp( 0,0,p->data );
//                show_bmp_dynamic_v1( p->data );
//                 show = 2;
//                 break;
//             }
//             case 2:
//             {
//                 show_bmp( 0,0,p->data );
// //                show_bmp_dynamic_v2( 0, 0, p->data );
//                 show = 1;
//                 break;
//             }
        show_bmp( 0,0,p->data );
        direc = get_direction();
        switch(direc)
        {
            case 3:
            {
                p = p->prev;
                break;
            }
            case 4:
            {
                p = p->next;
                break;
            }
            case 1:
            {
                p = p->prev;
                break;
            }
            case 2:
            {
                p = p->next;
                break;
            }
            case -1:
            {
                return -1;
            }
            default :
                break;
        }

        
        //延时 
//        sleep( 2 );

//        p = p->next;
    }

	//销毁链表 
	delete_bilinklist( list );
}


