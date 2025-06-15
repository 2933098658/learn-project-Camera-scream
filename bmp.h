
#ifndef __BMP_H__
#define __BMP_H__


#include "bilinklist.h"


int show_bmp( int x0, int y0, char * filename );

int show_bmp_dynamic_v1( char * filename );

int show_bmp_dynamic_v2( int x0, int y0, char * filename );

int get_bmp_name( char * pathname, struct Linklist * list );

int Circle_show_bmp( char * pathname );


#endif

