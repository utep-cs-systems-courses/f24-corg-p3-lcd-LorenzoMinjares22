// Updated main.c for MSP430 project

#include <msp430.h>

#include <libTimer.h>

#include "lcdutils.h"

#include "lcddraw.h"

#include "led.h"

#include "buzzer.h"



#define SW1 BIT3 // P1.3

#define SW2 BIT0 // P2.0

#define SW3 BIT1 // P2.1

#define SW4 BIT2 // P2.2

#define SW5 BIT3 // P2.3



#define SWITCH_1 SW1

#define SWITCH_2 SW2

#define SWITCH_3 SW3

#define SWITCH_4 SW4

#define SWITCH_5 SW5



#define SWITCH_P2 (SWITCH_2 | SWITCH_3 | SWITCH_4 | SWITCH_5)



volatile int cpuOff = 0;

volatile int graphicsState = 0;

volatile int timerCount = 0;

// Function prototypes
void drawCatShape();


void main(void) {

  WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

  configureClocks();

  enableWDTInterrupts();

  lcd_init();

  buzzer_init();



  P1DIR |= LEDS; // Set LED pins as outputs

  P1OUT &= ~LEDS; // Turn off LEDs



  P1REN |= SWITCH_1; // Enable pull-up resistor

  P1OUT |= SWITCH_1;

  P1IE |= SWITCH_1; // Enable interrupt for SW1



  P2REN |= SWITCH_P2;

  P2OUT |= SWITCH_P2;

  P2IE |= SWITCH_P2; // Enable interrupts for P2 sw

  or_sr(0x18); // Enter LPM3 with interrupts enabled
}

void switch_interrupt_handler_P1() {
  char p1val = P1IN;
  P1IES |= (p1val & SWITCH_1); // Detect falling edge
  P1IES &= (p1val | ~SWITCH_1); // Detect rising edge

  if (!(p1val & SW1)) { // SW1 pressed
    if (cpuOff) {
      cpuOff = 0;
      P1OUT &= ~LED_RED;
      P1OUT |= LED_GREEN;
      and_sr(~0x10); // Wake CPU
    } else {
      cpuOff = 1;
      P1OUT &= ~LED_GREEN;
      P1OUT |= LED_RED;
      or_sr(0x18); // Enter LPM3
    }
  }
  P1IFG &= ~SWITCH_1; // Clear interrupt flag
}

void switch_interrupt_handler_P2() {
  char p2val = P2IN;

  if (!(p2val & SW2)) { // SW2 pressed: Play DVD animation
    graphicsState = 1;
  }
  if (!(p2val & SW3)) { // SW3 pressed: Draw cat shape
    graphicsState = 2;
  }

  if (!(p2val & SW5)) { // SW5 pressed: Play song
    buzzer_set_period(6590);
    __delay_cycles(5000000);
    buzzer_set_period(4400);
    __delay_cycles(12500000);
    buzzer_set_period(0);
  }

  P2IFG &= ~SWITCH_P2; // Clear all P2 interrupt flags
}

void __interrupt_vec(PORT1_VECTOR) Port_1() {
  if (P1IFG & SWITCH_1) {
    switch_interrupt_handler_P1();
  }
}

void __interrupt_vec(PORT2_VECTOR) Port_2() {
  if (P2IFG & SWITCH_P2) {
    switch_interrupt_handler_P2();
  }
}

void __interrupt_vec(WDT_VECTOR) WDT() {
  timerCount++;
  if (timerCount == 250) { // Update graphics every ~250ms
    if (graphicsState == 1) {
      bounceDVDLogo();
    } else if (graphicsState == 2){

      drawCatShape();
    }
    timerCount = 0;
}
}

// Additional functions
void drawCatShape() {
  // Call C and assembly functions to draw shapes
  clearScreen(COLOR_PINK);
  drawTriangle(screenWidth / 2, screenHeight / 2, 20, COLOR_BLACK);
  
}



