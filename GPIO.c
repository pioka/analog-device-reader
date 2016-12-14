#include "GPIO.h"

uint8_t GPIOSet(GPIO_PORT port, unsigned uint8_t pin){
  switch (port){
  case GPIO_PORTA:
    if (pin < PORTA_PINS){
      LATA |= (1 << pin);
    }
    else {
      return -1;
    }
    break;

  case GPIO_PORTB:
    if (pin < PORTB_PINS){
      LATB |= (1 << pin);
    }
    else {
      return -1;
    }
    break;
  
  case GPIO_PORTC:
    if (pin < PORTC_PINS){
      LATC |= (1 << pin);
    }
    else {
      return -1;
    }
    break;
  
  default:
    return -1;
  }

  return 0;
}

uint8_t GPIOClear(GPIO_PORT port, uint8_t pin){
  switch (port){
  case GPIO_PORTA:
    if (pin < PORTA_PINS){
      LATA &= ~(1 << pin);
    }
    else {
      return -1;
    }
    break;
  case GPIO_PORTB:
    if (pin < PORTB_PINS){
      LATB &= ~(1 << pin);
    }
    else {
      return -1;
    }
    break;
  case GPIO_PORTC:
    if (pin < PORTC_PINS){
      LATC &= ~(1 << pin);
    }
    else {
      return -1;
    }
    break;
  default:
    return -1; 
  }

  return 0;
}

uint8_t GPIORead(GPIO_PORT port, uint8_t pin){
  uint8_t ret;

  switch (port){
  case GPIO_PORTA:
    if (pin < PORTA_PINS){
      ret = ((PORTA >> pin) & 1);
    }
    else {
      ret = -1;
    }
    break;
  case GPIO_PORTB:
    if (pin < PORTB_PINS){ 
      ret = ((PORTB >> pin) & 1);
    }
    else {
      ret = -1;
    }
    break;
  case GPIO_PORTC:
    if (pin < PORTC_PINS){ 
      ret = ((PORTC >> pin) & 1);
    }
    else {
      ret = -1;
    }
    break;
  default:
    ret = -1;
  }

  return ret;
}
