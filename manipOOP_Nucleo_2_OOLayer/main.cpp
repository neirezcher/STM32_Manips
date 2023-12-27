#include "stm32f10x.h"
#include "PinAsInput.h"
#include "PinAsOutput.h"

using namespace OOlayer;


	PinAsInput  MyButton (PC_13);
	PinAsOutput GreenLed (PA_5);


int main ()
{	
	// PA5 ON with OO repr
	 
		GreenLed =1;
	
	while (1)
	{		

		if (!MyButton){ //button pressed = 0
					
				/*Invert PA5 using Greenled object*/
		
			GreenLed = !GreenLed;
		
				for (int i=0x7FFFFF; i>0; i--);
		}

	}
}
