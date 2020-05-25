#include "UART.h"

void UART_INIT(void){
	SYSCTL_RCGCUART_R |= SYSCTL_DC2_UART0;   //activate UART0
	SYSCTL_RCGCGPIO_R |= 0x0001;    //activate port A
	UART0_CTL_R &= ~0x0001;         //disbale UART
	UART0_IBRD_R=104;               // for 9600 baudrate and clk=16 MHZ
	UART0_FBRD_R=11;
	UART0_LCRH_R = 0x0070;          //8 bits length & 1 stop bit & FIFO 16 bits
	UART0_CTL_R = 0x0301;           //enable RXE and TXE
	GPIO_PORTA_AFSEL_R |= 0x03;
	GPIO_PORTA_PCTL_R =(GPIO_PORTA_PCTL_R&0xFFFFFF00) + 0x00000011;
	GPIO_PORTA_DEN_R |= 0x03;         //B0 and B1
	GPIO_PORTA_AMSEL_R &= ~0x03;      //Not analog
 
}

void UART_TRANS_CHAR(uint16_t x){
	while((UART0_FR_R&UART_FR_TXFF) !=0);  //waiting for FIFO to be empty
	UART0_DR_R=x;
}

uint16_t UART_REC_CHAR(void){
	
	while((UART0_FR_R&UART_FR_RXFE) !=0);
	return UART0_DR_R;
}

void UART_TRANS_STRING(char* str){
	int i=0;
	while(str[i] != '\0'){
		UART_TRANS_CHAR(str[i]);
		i++;
	}
}	