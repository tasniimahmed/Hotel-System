#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "UART/UART.h"
#include "Keypad/Keypad.h"
#define PASSWORD_SIZE 4
#define FREE 0
#define OCCUPIED 1
#define CLEANING 2

void Turn_on_lock(void);
void Turn_off_lock(void);
uint16_t get_room_number(void);
uint16_t* set_password(void);
uint16_t set_status(void);
uint16_t valid( uint16_t* t_pw);

int main(){
	UART_INIT();
	keypad_Init();
	uint16_t first_reservation_flag=0;
	uint16_t room_status;
	uint16_t *password_set;
	
	while(1){
		uint16_t room_num= get_room_number();         //get room number
		room_status= set_status();                    //room is now occupied
		
		
		if (room_status == OCCUPIED){
			if (first_reservation_flag == 0){
				password_set =set_password();       //receptionist sets the pw
				first_reservation_flag = 1;
			}
			if(valid(password_set)) Turn_on_lock();
			else Turn_off_lock();
		}
		
		else if (room_status == CLEANING){
			Turn_on_lock();
		}
		
		else if (room_status == FREE){
			Turn_off_lock();
		}
		
		
		
		
		
	}
}

void Turn_on_lock(void){
	SYSCTL_RCGCGPIO_R|=0x20; //activate portF
	GPIO_PORTF_DIR_R|=0x0E;  //pin 1,2,3 ouyput
	GPIO_PORTF_DEN_R|=0X0E;
	GPIO_PORTF_DATA_R=0x0E;
}
void Turn_off_lock(void){
	SYSCTL_RCGCGPIO_R|=0x20; //activate portF
	GPIO_PORTF_DIR_R|=0x0E;  //pin 1,2,3 ouyput
	GPIO_PORTF_DEN_R|=0X0E;
	GPIO_PORTF_DATA_R=0x00;
}

uint16_t get_room_number(void){
	return UART_REC_CHAR();
}
uint16_t set_status(void){
	return UART_REC_CHAR();
}
uint16_t* set_password(void){
	static uint16_t password_set[4];
	for (int i=0; i<PASSWORD_SIZE; i++){
		password_set[i]= UART_REC_CHAR();
	}
	return password_set;
}
uint16_t valid(uint16_t* t_pw){
	uint16_t pw[4];
	
	//getting password from the client by keypad and check if it's valid or not
	for(int i=0; i<4; i++){
		uint16_t pw= KeyPad_getPressedKey();
		if(pw != t_pw[i]) return 0;
	}
	return 1;
}
