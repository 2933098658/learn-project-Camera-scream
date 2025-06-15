
#ifndef __LCD_H__
#define __LCD_H__



int lcd_init();

void lcd_close();

void display_point( int x, int y, int color );

void show_a_pure_color( int color );

void display_Rectangle( int x0, int y0, int w, int h, int color );

void display_Circle( int x0, int y0, int r, int color );

void display_pentastar( int x0, int y0,int r,int color);



#endif

