#include "Keypad.h"

unsigned int ncols = 0;
unsigned int nrows = 0;                                                                    
uint8_t symbol[N_row][N_col] = {{ '1', '2',  '3', '+'},      
																{ '4', '5',  '6', '-'},      
																{ '7', '8',  '9', '*'},      
                                { '.', '0',  '=', '/'}}; 

void keypad_Init(void)
{
  SYSCTL_RCGCGPIO_R |= 0x02;            //enable clc for port B
  while ((SYSCTL_RCGCGPIO_R&0x02)==0);  //wait for clock to be enabled
  GPIO_PORTB_CR_R  |= 0xFF;             //allow changes to all the bits in port D
  //GPIO_PORTE_CR_R  |= 0x1E;             //allow changes to all the bits in port E
  GPIO_PORTB_DIR_R |= 0xF0;             //set directions cols are o/ps
  //GPIO_PORTE_DIR_R |= 0x00;             //set directions raws are i/ps
  GPIO_PORTB_PDR_R |= 0x0F;             //pull down resistor on Raws
  GPIO_PORTB_DEN_R |= 0xFF;             //digital enable pins in port D
  //GPIO_PORTE_DEN_R |= 0x1E;             //digital enable pins in port E
}

uint8_t KeyPad_getPressedKey(void)
{
	uint32_t i,j;
  while(1)
  {
    for(i = 0; i < N_col; i++)                        //to determine the column
    {
      GPIO_PORTC_DATA_R = (1 << (i+4) );
      for(j = 0; j < N_row; j++)                     //to determine the row
      {
        if((GPIO_PORTE_DATA_R & 0x1E) & (1U << (j+1)) ) //
          return symbol[j][i];
      }
    }
  }
}
