#include <stdint.h>
#include "../tm4c123gh6pm.h"

void UART_INIT(void); 
void UART_TRANS_CHAR(char x);
char UART_REC_CHAR(void);
