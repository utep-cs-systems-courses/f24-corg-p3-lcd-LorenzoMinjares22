/** \file lcddraw.c
 *  \brief Adapted from RobG's EduKit
 */
#include "lcdutils.h"
#include "lcddraw.h"


/** Draw single pixel at x,row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR) 
{
  lcd_setArea(col, row, col, row);
  lcd_writeColor(colorBGR);
}

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, 
		   u_int colorBGR)
{
  u_char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total) {
    lcd_writeColor(colorBGR);
  }
}

/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR) 
{
  u_char w = screenWidth;
  u_char h = screenHeight;
  fillRectangle(0, 0, screenWidth, screenHeight, colorBGR);
}

/** 5x7 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 */
void drawChar5x7(u_char rcol, u_char rrow, char c, 
     u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 4, rrow + 7); /* relative to requested col/row */
  while (row < 8) {
    while (col < 5) {
      u_int colorBGR = (font_5x7[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}

/** Draw string at col,row
 *  Type:
 *  FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 *  FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 *  Adapted from RobG's EduKit
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString5x7(u_char col, u_char row, char *string,
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar5x7(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 6;
  }
}
void drawChar11x16(u_char rcol, u_char rrow, char c,
		   u_int fgColorBGR, u_int bgColorBGR) {
  u_char col = 0;
  u_char row = 0;
  u_char oc = c - 0x20; // Offset to font array

  lcd_setArea(rcol, rrow, rcol + 10, rrow + 15); /* relative to requested col/row */

  for (row = 0; row < 16; row++) {
    for (col = 0; col < 11; col++) {
      u_int colorBGR = (font_11x16[oc][col] & (1 << row)) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
    }
  }
}

void drawString11x16(u_char col, u_char row, char *string,
		     u_int fgColorBGR, u_int bgColorBGR) {
  u_char cols = col;
  while (*string) {
    drawChar11x16(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 12; // Move to the next character position
  }
}
/** Draw rectangle outline
 *  
 *  \param colMin Column start
 *  \param rowMin Row start 
 *  \param width Width of rectangle
 *  \param height Height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
		     u_int colorBGR)
{
  /**< top & bot */
  fillRectangle(colMin, rowMin, width, 1, colorBGR);
  fillRectangle(colMin, rowMin + height, width, 1, colorBGR);

  /**< left & right */
  fillRectangle(colMin, rowMin, 1, height, colorBGR);
  fillRectangle(colMin + width, rowMin, 1, height, colorBGR);
}




/** Draw the CORG logo at a specific position

 *  

 *  \param col The column to start drawing the logo

 *  \param row The row to start drawing the logo

 *  \param color The color of the logo

 *  \param bgColor The background color of the logo

 */

void drawDVDLogo(u_char col, u_char row, u_int color, u_int bgColor) {

  // Adjust the size of the rectangle for "CORG"

  u_char logoWidth = 40;  // Wider rectangle to fit "CORG"

  u_char logoHeight = 15; // Height of the rectangle



  // Draw the logo as a filled rectangle

  fillRectangle(col, row, logoWidth, logoHeight, color);



  // Draw "CORG" text inside the rectangle

  drawString11x16(col + 5, row + 5, "CORG", bgColor, color); // Adjust offsets for alignment

}



void bounceDVDLogo() {

  u_char col = 0, row = 0;  // Initial position

  int colSpeed = 1, rowSpeed = 1; // Speed of movement

  u_int bgColor = COLOR_BLACK; // Screen background color

  u_int logoColor = COLOR_RED; // CORG logo color



  clearScreen(bgColor); // Clear the screen



  while (1) {

    // Clear the current logo

    drawDVDLogo(col, row, bgColor, bgColor);



    // Update position

    col += colSpeed;

    row += rowSpeed;



    // Check for screen boundaries and reverse direction if needed

    if (col <= 0 || col + 40 >= screenWidth) { // Adjust width to logoWidth

      colSpeed = -colSpeed;

    }

    if (row <= 0 || row + 15 >= screenHeight) { // Adjust height to logoHeight

      rowSpeed = -rowSpeed;

    }



    // Draw the logo at the new position

    drawDVDLogo(col, row, logoColor, bgColor);



    // Add a delay to control the speed of movement

    __delay_cycles(200000);

  }

}


