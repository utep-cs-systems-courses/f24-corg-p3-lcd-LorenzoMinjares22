/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int bounce() {

  configureClocks();     // Initialize the clock

  lcd_init();            // Initialize the LCD

  bounceDVDLogo();       // Start the bouncing DVD logo

  return 0;

}


