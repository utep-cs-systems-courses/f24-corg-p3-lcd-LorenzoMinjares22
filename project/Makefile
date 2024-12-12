all: libLcd.a lcddemo.elf lcddemo-s.elf



CPU             = msp430g2553

CFLAGS          = -mmcu=${CPU} -Os -I../h

LDFLAGS 	= -L/opt/ti/msp430_gcc/include -L../lib

#switch the compiler (for the internal make rules)

CC              = msp430-elf-gcc

AS              = msp430-elf-as

AR              = msp430-elf-ar



libLcd.a: font-11x16.o font-5x7.o font-8x12.o lcdutils.o lcddraw.o

	$(AR) crs $@ $^



lcddraw.o: bounce.c lcddraw.c lcddraw.h lcdutils.h

lcdutils.o: lcdutils.c lcdutils.h

buzzer.c: buzzer.h

redControl-c.o: led.h

drawFilledTriangle-c.o: led.h

drawThing.o: led.h

wdInterruptHandler.o: led.h





install: libLcd.a

	mkdir -p ../h ../lib

	mv $^ ../lib

	cp *.h ../h



clean:

	rm -f libLcd.a *.o *.elf *.c# *.c~ *~ *#



lcddemo-c.elf: main.o bounce.c buzzer.o redControl-c.o drawFilledTriangle-c.o drawTriangle-c.o drawThing-c.o  libLcd.a

	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lTimer



lcddemo-s.elf: main.o bounce.c buzzer.o redControl-s.o drawFilledTriangle-c.o drawTriangle-s.s drawThing-c.o libLcd.a

	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lTimer



load-c: lcddemo-c.elf

	msp430loader.sh $^



load-s: lcddemo-s.elf

	msp430loader.sh $^
