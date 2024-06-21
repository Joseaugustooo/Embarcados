avr-gcc -mmcu=atmega328p -Os Ondadentedeserra.c -o Ondadentedeserra.out
avr-objcopy -j .text -j .data -O ihex Ondadentedeserra.out Ondadentedeserra.hex
avrdude -P /dev/ttyUSB0 -c arduino -p atmega328p -b115200 -v -D -U flash:w:Ondadentedeserra.hex:i
