# TODO [lpavic]: erase this file when CMake is configured in this project
default:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o enable_gpio_pin.o enable_gpio_pin.c
	avr-gcc -o enable_gpio_pin.bin enable_gpio_pin.o
	avr-objcopy -O ihex -R .eeprom enable_gpio_pin.bin enable_gpio_pin.hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:enable_gpio_pin.hex