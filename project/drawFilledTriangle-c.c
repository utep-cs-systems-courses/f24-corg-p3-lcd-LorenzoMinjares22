#include <msp430.h>

#include <libTimer.h>

#include "lcdutils.h"

#include "lcddraw.h"

//#include "led.h"

//#include "buzzer.h"



void drawFilledTriangle(u_char acol, u_char arow, u_int color, u_char size) {

  int i;

  int j;



  for(i = 0; i <= size; i++) {

    for(j = acol-i; j < acol+i; j++) {

      drawPixel(j,i+arow, COLOR_YELLOW);

      drawPixel(j,(-1)*(i)+arow, COLOR_BLUE);

    }

  }



  for(j = 0; j <= size; j++) {

    for(i = arow-j; i<=arow+j; i++) {

      drawPixel(j+acol,i,COLOR_RED);

      drawPixel((-1)*(j)+acol,i,COLOR_GREEN);

    }

  }



}
