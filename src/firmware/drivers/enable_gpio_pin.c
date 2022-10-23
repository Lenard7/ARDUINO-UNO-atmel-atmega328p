#include <avr/io.h>
#include <util/delay.h>

// TODO [lpavic]: complete this function declaration (return value and arguments)
int enable_gpio_pin()
{
    DDRB |= (1 << DDB5);

    while(1)
    {
        PORTB |= (1 << PORTB5);
        _delay_ms(1000);
        PORTB &= ~(1 << PORTB5);
        _delay_ms(1000);
    }
}