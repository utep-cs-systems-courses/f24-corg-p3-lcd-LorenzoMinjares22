COMMON_OBJECTS = main.o

CPU = msp430g2553

CFLAGS = -mmcu=${CPU} -I../h

LDFLAGS = -L/opt/ti/msp430_gcc/include



CC = msp430-elf-gcc

AS = msp430-elf-as





all: led-c.elf #led-s.elf





led-s.elf: ${COMMON_OBJECTS} buzzer.o redControl-s.o blink.o  

	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/libTimer.a



led-c.elf: ${COMMON_OBJECTS} buzzer.o redControl-c.o blink.o  song.o

	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/libTimer.a



load-s: led-s.elf

	msp430loader.sh $^

load-c: led-c.elf

	msp430loader.sh $^



clean:

	rm -f *.o *.elf *~ *.c# *#



buzzer.c: buzzer.h



main.o: led.h

redControl-c.o: led.h

wdInterruptHandler.o: led.h

blink.o: blink.h

song.o: led.h
