#include <msp430.h>

#include <libTimer.h>

#include "lcdutils.h"

#include "lcddraw.h"

#include "led.h"

#include "buzzer.h"



#define SW1 BIT3


#define SW2 BIT0

#define SW3 BIT1

#define SW4 BIT2

#define SW5 BIT3

 
#define SWITCH_1 SW1
#define SWITCH_2 SW2

#define SWITCH_3 SW3

#define SWITCH_4 SW4

#define SWITCH_5 SW5



#define SWITCH_P2 (SWITCH_2 | SWITCH_3 | SWITCH_4 | SWITCH_5)



volatile int red_on = 0;

volatile int green_on = 0;

volatile int redDim = 0;
volatile int isCpuOff = 0; // Flag to track CPU state
volatile u_char width = screenWidth>>1, height = screenHeight>>1;



int main(void) {
  WDTCTL = WDTPW + WDTHOLD;    // Stop watchdog timer
  configureClocks();           // Setup master clock
  enableWDTInterrupts();       // Enable watchdog timer interrupts
  buzzer_init();               // Initialize buzzer
  
  P1DIR |= LEDS;               // Set LED pins as outputs
  P1OUT &= ~LEDS;              // Turn off all LEDs

  P1REN |= SWITCH_1;
 
  P1IE |= SWITCH_1;

  P1OUT |= SWITCH_1;

  P1DIR &= ~SWITCH_1;

    
  P2REN |= SWITCH_P2;          // Enable pull-up resistors for P2 buttons

  P2OUT |= SWITCH_P2;

  P2IE |= SWITCH_P2;  
  
  or_sr(0x18); // Start in sleep mode (CPU off, GIE on)
}




void switch_interrupt_handler_P1() {
  char p1val = P1IN;



  P1IES |= (p1val & SWITCH_1);

  P1IES &= (p1val | ~SWITCH_1);

  
  if (p1val & SW1) {
    // Button released, do nothing
  } else {
    // Button pressed, toggle CPU state
    if (isCpuOff) {
      // Wake the CPU
      P1OUT &= ~LED_RED;
      P1OUT |= LED_GREEN; // Turn on LED as indication
      isCpuOff = 0;             // Mark CPU as active
      and_sr(~0x10);            // Clear CPUOFF bit (wake CPU)
    } else {
      // Put the CPU to sleep
      P1OUT &= ~LED_GREEN;        // Turn off LED as indication
      P1OUT |= LED_RED;
      isCpuOff = 1;             // Mark CPU as off
      or_sr(0x18);              // Set CPUOFF and GIE 


    }
  }

  P1IFG &= ~SWITCH_1; // Clear interrupt flag for SW1
}

void switch_interrupt_handler_P2_2() {

  char p2val = P2IN;

  // Update interrupt edge to detect button press and release

  P2IES |= (p2val & SWITCH_2); // Set high-to-low edge if button is not pressed

  P2IES &= (p2val | ~SWITCH_2); // Set low-to-high edge if button is pressed

  if (p2val & SW2) {

    // Button released, do nothing

  } else {

    bounceDVDLogo();
  }
}

  

void switch_interrupt_handler_P2_3() {

  char p2val = P2IN;

  P2IES |= (p2val & SWITCH_3);

  P2IES &= (p2val | ~SWITCH_3);



  if(p2val & SW3) {

    //P1OUT &= ~LED_GREEN;

    green_on = 0;

    //buzzer_set_period(0);

  } else {

    //P1OUT |= LED_GREEN;

    //buzzer_set_period(3300);

    char size = 60;

    green_on = 1;

    clearScreen(COLOR_PINK);

    // drawFilledTriangle(width, height, COLOR_BLACK,size);

    drawString5x7(50,30, "(o_0)", COLOR_WHITE, COLOR_BLACK);



  }

}

volatile int dimDutyCycle = 0; // Duty cycle (0-100%)

volatile int dimEnabled = 0;  // Whether dimming is active


void switch_interrupt_handler_P2_4() {

  char p2val = P2IN;

  P2IES |= (p2val & SWITCH_4);

  P2IES &= (p2val | ~SWITCH_4);

  if (p2val & SW4) {



  }else {

    clearScreen(COLOR_WHITE);

    //drawTriangle(width, height, 15, COLOR_RED);

    // P1OUT &= ~LED;

  }

}






void switch_interrupt_handler_P2_5() {

  char p2val = P2IN;

  P2IES |= (p2val & SWITCH_5);

  P2IES &= (p2val | ~SWITCH_5);

  if(p2val & SW5) {

    buzzer_set_period(0);

  } else {

    buzzer_set_period(6590);

    __delay_cycles(5000000);

    buzzer_set_period(4400);

    __delay_cycles(12500000);

    buzzer_set_period(6590);

    __delay_cycles(5000000);

    buzzer_set_period(4400);

    __delay_cycles(12500000); //a

    buzzer_set_period(6590);

    __delay_cycles(5000000);

    buzzer_set_period(4400);

    __delay_cycles(5000000);

    buzzer_set_period(4940); //b

    __delay_cycles(5000000);

    buzzer_set_period(5540);//c#

    __delay_cycles(5000000);

    buzzer_set_period(6590);

    __delay_cycles(5000000);

    buzzer_set_period(8800);

    //__delay_cycles(5000000);

    //buzzer_set_period(4400);

    __delay_cycles(12500000);

    buzzer_set_period(0);



    /* buzzer_set_period(4940);

    __delay_cycles(2500000);

    buzzer_set_period(5240);

    */

  }

}



void __interrupt_vec(PORT1_VECTOR) Port_1() {

  if(P1IFG & SWITCH_1) {

    P1IFG &= ~SWITCH_1;

    switch_interrupt_handler_P1();

  }

}



void __interrupt_vec(PORT2_VECTOR) Port_2() {
 
  if (P2IFG & SW2) {

    P2IFG &= ~SW2;

    switch_interrupt_handler_P2_2();

  }

  if (P2IFG & SW3) {

    P2IFG &= ~SW3;

    switch_interrupt_handler_P2_3();

  }

  if (P2IFG & SW4) {

    P2IFG &= ~SW4;

    switch_interrupt_handler_P2_4();

  }

  if (P2IFG & SW5) {

    P2IFG &= ~SW5;

    switch_interrupt_handler_P2_5();

  }

}


void __interrupt_vec(WDT_VECTOR) WDT() {

  if (P2IFG & SW2) {



    P2IFG &= ~SW2;



    switch_interrupt_handler_P2_2();



  }

  

}

