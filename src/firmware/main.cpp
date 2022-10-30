// TODO [lpavic]: for now, this code is here only for checking if build is set properly
// after the build is set, this code needs to be erased and useful code should be put here

#include <avr/io.h>
#include <util/delay.h>

// TODO [lpavic]: put useful includes here
int main(void)
{
    // TODO [lpavic]: put useful code here
    // for now, Round Robin implementation (infinite while loop)
    DDRB |= (1 << DDB5);

    while(1)
    {
        PORTB |= (1 << PORTB5);
        _delay_ms(1000);
        PORTB &= ~(1 << PORTB5);
        _delay_ms(1000);
    }
}