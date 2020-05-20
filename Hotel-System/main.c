#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "UART/UART.h"

int main(){
	UART_INIT();
	
	//Test
	SYSCTL_RCGCGPIO_R|=0x20; //activate portF
	GPIO_PORTF_DIR_R|=0x0E;  //pin 1,2,3 ouyput
	GPIO_PORTF_DEN_R|=0X0E;
	while(1){
		GPIO_PORTF_DATA_R=0x00;
		GPIO_PORTF_DATA_R=0xFF;
		
		
	}
}