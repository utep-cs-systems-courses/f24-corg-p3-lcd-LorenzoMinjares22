#include <msp430.h>

#include <libTimer.h>

#include "lcdutils.h"

#include "lcddraw.h"



void drawPart(char col, char row, int color) {



  for(int i = row - 5; i <= row + 5; i++) {



    for(int j = col - 5; j <= col + 5; j++) {



      drawPixel(j, i, color);



    }

  }

}



void drawThing() {

  int i = 0;

  int j = 0;

  //ROW + 30

  drawPart(40,80,COLOR_BLACK);//TOP LEFT EAR

  drawPart(30,90,COLOR_BLACK);

  drawPart(40,90,COLOR_GRAY);

  drawPart(50,90,COLOR_BLACK);



  drawPart(30,100,COLOR_BLACK);//leftmost

  drawPart(40,100,COLOR_GRAY);

  drawPart(50,100,COLOR_GRAY);

  drawPart(60,100,COLOR_BLACK);//top long part

  drawPart(70,100,COLOR_BLACK);

  drawPart(80,100,COLOR_BLACK);

  drawPart(90,100,COLOR_BLACK);

  drawPart(100,100,COLOR_GRAY);

  drawPart(110,100,COLOR_GRAY);

  drawPart(110,90,COLOR_GRAY);



  drawPart(100,90,COLOR_BLACK);//black outline top right

  drawPart(110,80,COLOR_BLACK);

  drawPart(120,90,COLOR_BLACK);

  drawPart(120,100,COLOR_BLACK );



  drawPart(20,110,COLOR_BLACK); //2nd two left pixels short

  drawPart(20,120,COLOR_BLACK);



  for (i = 0; i < 2;i++) {

    for(j = 0;j < 10; j++) {

      drawPart(30+(j*10),110+(i*10),COLOR_GRAY);

    }

  }



  for(i = 0; i <4; i++) { drawPart(10,130+(i*10),COLOR_BLACK); } //leftmost long black bit



  for(i = 0; i < 12; i++) { drawPart(20+(i*10),130,COLOR_GRAY); }

  drawPart(140,130,COLOR_BLACK);

  drawPart(140,120, COLOR_BLACK);

  drawPart(140,110, COLOR_BLACK);





  drawPart(20,140, COLOR_GRAY);

  drawPart(30,140, COLOR_GRAY);

  drawPart(40,140, COLOR_BLACK);

  drawPart(50,140, COLOR_GRAY);

  drawPart(60,140, COLOR_GRAY);

  drawPart(70,140, COLOR_BLACK);

  drawPart(80,140, COLOR_GRAY);

  drawPart(90,140, COLOR_GRAY);

  drawPart(100,140, COLOR_BLACK);

  for(i = 1; i <=3; i++) { drawPart(100+(i*10),140, COLOR_GRAY); }

  drawPart(140,140, COLOR_BLACK); //end of 7th line



  drawPart(20,150, COLOR_GRAY);

  drawPart(30,150, COLOR_RED);

  drawPart(40,150, COLOR_GRAY);

  drawPart(50,150, COLOR_GRAY);

  drawPart(60,150, COLOR_BLACK);

  drawPart(70,150, COLOR_GRAY);

  drawPart(80,150, COLOR_BLACK);

  drawPart(90,150, COLOR_GRAY);

  drawPart(100,150, COLOR_GRAY);

  drawPart(110,150, COLOR_RED);

  drawPart(120,150, COLOR_GRAY);

  drawPart(130,150, COLOR_GRAY);

  drawPart(140,150, COLOR_BLACK); //end of 8th line



  for(i = 1; i <= 12;i++) { drawPart(10+(i*10),160, COLOR_GRAY); }



  for(i = 0; i < 3; i++) {

    for(j = 0; j < 11; j++) {

      drawPart(10+(j*10),10+(i*10),COLOR_WHITE);

    }

  }

  drawString5x7(15,15," ~~ m e o w ~~ ",COLOR_BLACK, COLOR_WHITE);



  for(i = 0; i < 2; i++) {

    for(j = 0; j < 2; j++) {

      drawPart(45+(j*10),45+(i*10),COLOR_WHITE);

    }

  }



  drawPart(70,70,COLOR_WHITE);

}
