#include <msp430.h>

#include "led.h"

#include "libTimer.h"



#define SW2 BIT0



int redControl(int on) {

  int r = 0;

  if(on) {

    P1OUT |= LED_RED;

  } else {

    P1OUT &= ~LED_RED;

    r = 1;

  }



  return r;



}
