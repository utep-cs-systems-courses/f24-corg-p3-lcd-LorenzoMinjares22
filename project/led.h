#ifndef led_included

#define led_included



#define LED_RED BIT6

#define LED_GREEN BIT0

#define LEDS (BIT6 | BIT0)



int redControl(int on);

//void  blink();

void song();

void play(int dur);



#endif
