#include <stdint.h>
#include "../tm4c123gh6pm.h"

#define N_col 4
#define N_row 4


void keypad_Init(void);
uint8_t KeyPad_getPressedKey(void);
