#ifndef MAIN_H
#define MAIN_H

#include <pic16f1938.h>

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


#define NUM_OF_ENCODER 2
#define SEND_TRUE 0
#define SEND_FALSE 1

// エンコーダの入力ピン定義
#define ENC_0_ASPECT_A PORTAbits.RA0
#define ENC_0_ASPECT_B PORTAbits.RA1
#define ENC_1_ASPECT_A PORTAbits.RA2
#define ENC_1_ASPECT_B PORTAbits.RA3

// 回転方向の出力先ピン定義
#define ENC_0_CW_OUTPUT  LATCbits.LATC0
#define ENC_0_CCW_OUTPUT LATCbits.LATC1
#define ENC_1_CW_OUTPUT  LATCbits.LATC2
#define ENC_1_CCW_OUTPUT LATCbits.LATC3

#endif
