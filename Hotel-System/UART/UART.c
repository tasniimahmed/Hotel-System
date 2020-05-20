#include "UART.h"

void UART_INIT(void){
	SYSCTL_RCGCUART_R |= 0x0002;   //activate UART1
	SYSCTL_RCGCGPIO_R |= 0x0002;   //activate port B
	UART1_CTL_R &= ~0x0001;        //disbale UART
	UART1_IBRD_R=104;              // for 9600 baudrate and clk=16 MHZ
	UART1_FBRD_R=11;
	UART1_LCRH_R = 0x0070;          //8 bits length & 1 stop bit & FIFO 16 bits
	UART1_CTL_R = 0x0301;           //enable RXE and TXE
	GPIO_PORTB_AFSEL_R |= 0x03;
	GPIO_PORTB_PCTL_R =(GPIO_PORTB_PCTL_R&0xFFFFFF00) + 0x00000011;
	GPIO_PORTB_DEN_R |= 0x03;         //B0 and B1
	GPIO_PORTB_AMSEL_R &= ~0x03;      //Not analog
 
}