#ifndef MAIN_H
#define MAIN_H

#include <pic16f1938.h>
#include "GPIO.h"

// ======== Configuration Bits ========
//CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection->INTOSC oscillator: I/O function on CLKIN pin
#pragma config WDTE = OFF    // Watchdog Timer Enable->WDT disabled
#pragma config PWRTE = OFF    // Power-up Timer Enable->PWRT disabled
#pragma config MCLRE = ON    // MCLR Pin Function Select->MCLR/VPP pin function is MCLR
#pragma config CP = OFF    // Flash Program Memory Code Protection->Program memory code protection is disabled
#pragma config CPD = OFF    // Data Memory Code Protection->Data memory code protection is disabled
#pragma config BOREN = ON    // Brown-out Reset Enable->Brown-out Reset enabled
#pragma config CLKOUTEN = OFF    // Clock Out Enable->CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin
#pragma config IESO = ON    // Internal/External Switchover->Internal/External Switchover mode is enabled
#pragma config FCMEN = ON    // Fail-Safe Clock Monitor Enable->Fail-Safe Clock Monitor is enabled

// CONFIG2
#pragma config WRT = OFF    // Flash Memory Self-Write Protection->Write protection off
#pragma config VCAPEN = OFF    // Voltage Regulator Capacitor Enable->All VCAP pin functionality is disabled
#pragma config PLLEN = ON    // PLL Enable->4x PLL enabled
#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable->Stack Overflow or Underflow will cause a Reset
#pragma config BORV = LO    // Brown-out Reset Voltage Selection->Brown-out Reset Voltage (Vbor), low trip point selected.
#pragma config LVP = OFF    // Low-Voltage Programming Enable->Low-voltage programming disabled
// ====================================


#define NUM_OF_ENCODER 2

typedef struct {
  GPIO_PORT port;
  uint8_t   pin;
} IO_MAP;

// エンコーダの入力ピン定義
const IO_MAP ENC_INPUT_A[NUM_OF_ENCODER] = {
  {GPIO_PORTA, 0},
  {GPIO_PORTA, 2},
};

const IO_MAP ENC_INPUT_B[NUM_OF_ENCODER] = {
  {GPIO_PORTA, 1},
  {GPIO_PORTA, 3},
};

// 回転方向の出力先ピン定義
const IO_MAP ENC_OUT_CW[NUM_OF_ENCODER] = {
  {GPIO_PORTC, 0},
  {GPIO_PORTC, 2},
};

const IO_MAP ENC_OUT_CCW[NUM_OF_ENCODER] = {
  {GPIO_PORTC, 1},
  {GPIO_PORTC, 3},
};

#endif
