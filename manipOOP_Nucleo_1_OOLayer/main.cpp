#include "stm32f10x.h"
#include "PinAsInput.h"

using namespace OOlayer;


	PinAsInput  MyButton (PC_13);


int main ()
{	
		//Clock and Pins Config 
	RCC->APB2ENR |=0x04;
	GPIOA->CRL &= ~(0xFu <<20); 
	GPIOA->CRL |=  0x1<<20;
	
	//PA5 ON 
	GPIOA->BSRR=0x1<<5;

while (1)
	{		

		if (!MyButton){ //button pressed = 0
		
		//Invert PA5 using register access  ( ^: XOR)
		GPIOA->ODR ^= 0x20; 			
		
		for (int i=0x7FFFFF; i>0; i--);
		}

	}
}
