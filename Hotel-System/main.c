#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "UART/UART.h"
#include "Keypad/Keypad.h"
#define PASSWORD_SIZE 4
#define FREE '0'
#define OCCUPIED '1'
#define CLEANING '2'

void Turn_on_lock(void);
void Turn_off_lock(void);
void set_password(char *set_pw);
uint16_t valid( char* t_pw);

struct room{    
	char room_num;    
  char room_status;
  char password[4];	
};   

int main(){
	UART_INIT();
	keypad_Init();
	
	struct room available_rooms[100];
	
	/*flag to check if the room is first time to be reserved
	then the reciptionist will set password
	else the user will enter the password to be verified*/
	uint16_t first_reservation_flag=0;

	UART_TRANS_STRING("WELCOME TO THE HOTEL");
	
	/*get the available rooms from the user*/
	/*send 'a' from uart if you finished entering rooms*/
	UART_TRANS_STRING("Please Enter The Available rooms:");
	char room=UART_REC_CHAR();
	uint16_t i=0;
	while(room != 'a'){ 
		available_rooms[i].room_num= room;
		room =UART_REC_CHAR();
		i++;
	}
	
	
	while(1){
		int room_index;
		UART_TRANS_STRING("Enter room number:");
		char room_n= UART_REC_CHAR();               //get room number
		
		//get the index of the chosen room in the array
		for (int x=0 ; x<i ;x++){
			if(available_rooms[x].room_num == room_n){ room_index=x; break;}
		}
		UART_TRANS_STRING("Enter room status:");
		available_rooms[room_index].room_status = UART_REC_CHAR();   //get room status
		
		if (available_rooms[room_index].room_status == OCCUPIED){
			if (first_reservation_flag == 0){
				set_password(available_rooms[room_index].password);       //receptionist sets the pw
				first_reservation_flag = 1;
			}
			else{
				if(valid(available_rooms[room_index].password)) Turn_on_lock();
				else Turn_off_lock();
			}
		}
		
		else if (available_rooms[room_index].room_status == CLEANING){
			Turn_on_lock();
		}
		
		else if (available_rooms[room_index].room_status == FREE){
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


void set_password(char *set_pw){
	for (int i=0; i<PASSWORD_SIZE; i++){
		set_pw[i]= UART_REC_CHAR();
	}
}
uint16_t valid(char* t_pw){
	//getting password from the client by keypad and check if it's valid or not
	for(int i=0; i<4; i++){
		uint16_t pw= KeyPad_getPressedKey();
		/*convert the char password to int
		to compare it with the input from keypad*/
		int password_toInt = t_pw[i]-'0';
		if(pw != password_toInt) return 0;
	}
	return 1;
}
