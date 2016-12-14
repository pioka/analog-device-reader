#include <stdint.h>
#include "main.h"

// 回転が止まったとみなされてからピン出力を0にするまでのインターバル[ms]
// (これがないと受取側で連打判定になってしまう)
#define REPEAT_MS 100

#define NUM_REPEAT (REPEAT_MS * 2)

// 回転方向の定義
typedef enum {
  DIR_NONE,
  DIR_CW,
  DIR_CCW,
} DIR_ENC;

// ======== Global variables declaration ========
// 今のエンコーダの状態
uint8_t g_enc_stat[NUM_OF_ENCODER] = {0};

// 前のエンコーダの状態
uint8_t g_prev_enc_stat[NUM_OF_ENCODER] = {0};

// エンコーダの回転方向
DIR_ENC g_enc_dir[NUM_OF_ENCODER] = {DIR_NONE};
// ==============================================

// ======== Functions definition ========
// 初期化用関数
void initialize(void);

// 回転方向をピンに出力
void sendEncoderStatus(void);
// ======================================


// 0.5msごとに割り込みでA相,B相を読み取り、
// 回転方向を判別
void interrupt interTimer(void){
  int i;
  uint8_t dir;

  if (TMR2IF){
    TMR2IF = 0;

    // 回転の有無,方向を判別
    for (i = 0; i < NUM_OF_ENCODER; i++){
      g_enc_stat[i] = 
        (GPIORead(ENC_INPUT_A[i].port, ENC_INPUT_A[i].pin) << 1) ^
        (GPIORead(ENC_INPUT_B[i].port, ENC_INPUT_B[i].pin));
      
      // 入力の状態が変化していたら
      // 前の状態と比較して回転方向を判別
      if (g_enc_stat[i] != g_prev_enc_stat[i]){
        dir = (((g_prev_enc_stat[i] << 1) ^ (g_enc_stat[i])) & 0x03);

        if (dir == 0x00 || dir == 0x01){
          g_enc_dir[i] = DIR_CCW;
        }
        else {
          g_enc_dir[i] = DIR_CW;
        }
      }

      // 入力の状態が変化していなければ
      // 回転していないものとする
      else {
        g_enc_dir[i] = DIR_NONE;
      }

      g_prev_enc_stat[i] = g_enc_stat[i];
    }
  }
  // 回転方向をピンに出力
  sendEncoderStatus();
}

// 初期化以外は何もしないメイン関数
void main(void) {
  initialize();
  
  while (1);
}

// 初期化用関数
void initialize(void){ 
  // Fosc = 8*4 = 32MHz
  OSCCON = 0x70;
  
  TRISA = 0x0F;
  TRISC = 0xF0;
  ANSELA = 0x00;
  LATC = 0x00;

  T2CON = 0b00000110;
  PR2 = 249;
  TMR2 = 0;
  TMR2IF = 0;
  TMR2IE = 1;
  PEIE = 1;
  GIE = 1;
}

// 回転方向をピン出力
void sendEncoderStatus(void){
  int i;
  static int s_count = 0;
  
  for (i = 0; i < NUM_OF_ENCODER; i++){
    switch (g_enc_dir[i]){ 
    case DIR_NONE:
      if (s_count > NUM_REPEAT){
        GPIOSet(ENC_OUT_CW[i].port, ENC_OUT_CW[i].pin); 
        GPIOSet(ENC_OUT_CCW[i].port, ENC_OUT_CCW[i].pin);
      }
      else {
        s_count++;
      }
      break;

    case DIR_CW:
      GPIOClear(ENC_OUT_CW[i].port, ENC_OUT_CW[i].pin); 
      GPIOSet(ENC_OUT_CCW[i].port, ENC_OUT_CCW[i].pin);
      s_count = 0;
      break;
   
    case DIR_CCW:
      GPIOSet(ENC_OUT_CW[i].port, ENC_OUT_CW[i].pin); 
      GPIOClear(ENC_OUT_CCW[i].port, ENC_OUT_CCW[i].pin);
      s_count = 0;
      break;
  
    default:
      GPIOSet(ENC_OUT_CW[i].port, ENC_OUT_CW[i].pin); 
      GPIOSet(ENC_OUT_CCW[i].port, ENC_OUT_CCW[i].pin);
      break;
    }
  }
}
