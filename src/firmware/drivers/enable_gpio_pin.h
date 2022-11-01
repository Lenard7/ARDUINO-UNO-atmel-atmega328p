/**
 * @file enable_gpio_pin.h
 * @author https://github.com/Lenard7
 * @brief description of this file
 * 
 */

# ifndef ENABLE_GPIO_PIN_H
# define ENABLE_GPIO_PIN_H

#include <avr/io.h>
#include <util/delay.h>

#ifdef _cplusplus
extern "C"
{
#endif

/**
 * @brief enable output pin
 * @param
 * 
 */
int enable_gpio_pin()

// TODO [lpavic]: add dox
int turn_on_gpio_pin()

// TODO [lpavic]: add dox
int turn_off_gpio_pin()

#ifdef _cplusplus
}
#endif

# endif // ENABLE_GPIO_PIN_H