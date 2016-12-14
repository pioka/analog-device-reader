#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <pic16f1938.h>

#define PORTA_PINS 8
#define PORTB_PINS 8
#define PORTC_PINS 8

typedef enum {
  GPIO_PORTA,
  GPIO_PORTB,
  GPIO_PORTC,
} GPIO_PORT;

uint8_t GPIOSet(GPIO_PORT port, unsigned uint8_t pin);
uint8_t GPIOClear(GPIO_PORT port, unsigned uint8_t pin);
uint8_t GPIORead(GPIO_PORT port, unsigned uint8_t pin);

#endif
