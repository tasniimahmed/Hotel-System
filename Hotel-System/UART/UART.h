#include <stdint.h>
#include "../tm4c123gh6pm.h"

void UART_INIT(void); 
void UART_TRANS_CHAR(uint16_t x);
uint16_t UART_REC_CHAR(void);
