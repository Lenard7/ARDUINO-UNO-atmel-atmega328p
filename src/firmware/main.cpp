/**
 * @file main.cpp
 * @author https://github.com/Lenard7
 * @brief description of this file
 * 
 */

#include "enable_gpio_pin.h"

int main(void)
{
    // TODO [lpavic]: put useful code here
    // for now, Round Robin implementation (infinite while loop)
    enable_gpio_pin();

    while(1)
    {
        turn_on_gpio_pin();
        turn_off_gpio_pin();
    }
}