#include <msp430.h>

#include <libTimer.h>

#include "lcdutils.h"

#include "lcddraw.h"



void drawTriangle(u_char acol, u_char arow, u_char size, u_int color) {

  int i;

  /*

  for(i = arow-size; i < size+arow; i++) {

    for(j = acol-size; j < size+acol; j++) {

      drawPixel(j, i, color);

    } 

    }   */



  for(i = arow-size;i < size+arow;i++) {

    drawPixel(i,i,color);

  }

  for(i = arow+size;i > arow-size;i--) {

    drawPixel(i,arow+size,color);

  }

  for(i = arow-size; i < arow+size;i++) {

    drawPixel(acol,i,color);

  }



}
