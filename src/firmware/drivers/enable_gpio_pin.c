/**
 * @file enable_gpio_pin.c
 * @author https://github.com/Lenard7
 * @brief description of this file
 * 
 */

#include "enable_gpio_pin.h"

// TODO [lpavic]: complete this functions declarations (return value and arguments) and 
// definitions here and inside .h file

int enable_gpio_pin()
{
    DDRB |= (1 << DDB5);

    return 0;
}


int turn_on_gpio_pin()
{
    PORTB |= (1 << PORTB5);
    _delay_ms(1000);

    return 0;
}


int turn_off_gpio_pin()
{
    PORTB &= ~(1 << PORTB5);
    _delay_ms(1000);

    return 0;
}