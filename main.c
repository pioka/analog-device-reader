#include <stdint.h>
#include "main.h"

// 回転が止まったとみなされてから、
// ピン出力を0にするまでのインターバル[ms]
// (これがないと受取側で連打判定になってしまう)
#define REPEAT_MS 100

#define NUM_REPEAT (REPEAT_MS * 2)

// 回転方向
typedef enum {
  DIR_NONE,
  DIR_CW,
  DIR_CCW,
} DIR_ENC;

// 今のエンコーダの状態
uint8_t g_enc_stat[NUM_OF_ENCODER] = {0};

// 前のエンコーダの状態
uint8_t g_prev_enc_stat[NUM_OF_ENCODER] = {0};

// エンコーダの回転方向
DIR_ENC g_enc_dir[NUM_OF_ENCODER] = {DIR_NONE};

// 初期化用関数
void initialize(void);

// 回転方向をピンに出力
void sendEncoderStatus(void);


// 0.5msごとに割り込みでA相,B相を読み取り、
// 回転方向を判別
void interrupt interTimer(void){
  int i;
  uint8_t dir;

  if (TMR2IF){
    TMR2IF = 0;

    // A相, B相を読み取る
    g_enc_stat[0] = (ENC_0_ASPECT_A << 1) ^ (ENC_0_ASPECT_B);
    g_enc_stat[1] = (ENC_1_ASPECT_A << 1) ^ (ENC_1_ASPECT_B);
    
    // 現在過去の状態から回転方向を判別
    for (i = 0; i < NUM_OF_ENCODER; i++){
      if (g_enc_stat[i] != g_prev_enc_stat[i]){
        dir = (((g_prev_enc_stat[i] << 1) ^ (g_enc_stat[i])) & 0x03);
        if (dir == 0x00 ||dir ==  0x01){
          g_enc_dir[i] = DIR_CCW;
        }
        else {
          g_enc_dir[i] = DIR_CW;
        }
      }
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
  static int s_count[NUM_OF_ENCODER] = {0};
  uint8_t target;

  target = 0;
  switch (g_enc_dir[target]){
    case DIR_NONE:
      if (s_count[target] > NUM_REPEAT){
        ENC_0_CW_OUTPUT   = SEND_FALSE;
        ENC_0_CCW_OUTPUT  = SEND_FALSE;
      }
      else {
        s_count[target]++;
      }
      break;
    case DIR_CW:
      ENC_0_CW_OUTPUT   = SEND_TRUE;
      ENC_0_CCW_OUTPUT  = SEND_FALSE;
      s_count[target] = 0;
      break;
    case DIR_CCW:
      ENC_0_CW_OUTPUT   = SEND_FALSE;
      ENC_0_CCW_OUTPUT  = SEND_TRUE;
      s_count[target] = 0;
      break;
    default:
      ENC_0_CW_OUTPUT   = SEND_FALSE;
      ENC_0_CCW_OUTPUT  = SEND_FALSE;
      break;
  }
  
  target = 1;
  switch (g_enc_dir[target]){
    case DIR_NONE:
      if (s_count[target] > NUM_REPEAT){
        ENC_1_CW_OUTPUT   = SEND_FALSE;
        ENC_1_CCW_OUTPUT  = SEND_TRUE;
      }
      else {
        s_count[target]++;
      }
      break;
    case DIR_CW:
      ENC_1_CW_OUTPUT   = SEND_TRUE;
      ENC_1_CCW_OUTPUT  = SEND_FALSE;
      s_count[target] = 0;
      break;
    case DIR_CCW:
      ENC_1_CW_OUTPUT   = SEND_FALSE;
      ENC_1_CCW_OUTPUT  = SEND_TRUE;
      s_count[target] = 0;
      break;
    default:
      ENC_1_CW_OUTPUT   = SEND_FALSE;
      ENC_1_CCW_OUTPUT  = SEND_FALSE;
      break;
  }
}
