#include <gpio.h>


//#define RCC_APB2ENR (*((volatile uint32_t*)0x40021018))
#define   RCC_APB2ENR     (uint32_t*) 0x40021018
uint8_t EtatBouton;


int main() {
		// Déclarez la variable GPIO_Struct pour la configuration
    GPIO_Struct GPIO_InitStruct;
    // Activation de l'horloge pour GPIOA (Push Button) et GPIOC (LEDs)
    //RCC_APB2ENR |= (1 << 2) | (1 << 4);
		*RCC_APB2ENR |= 0x014;
    /*
	//Configure GPIO Pins (Push Button)=PA0:Input Floating Mode
	GPIOA->CRL &= ~((uint32_t) 0x0F);;
	GPIOA->CRL |= GPIO_Mode_InputFloating;
	//Configure GPIO Pins (LED)=PC9/PC8:Output Push Pull 2 MHZ
	GPIOC->CRH &= ~((uint32_t) 0xFF);
	GPIOC->CRH |= GPIO_Mode_OutputPP2Mhz;
	GPIOC->CRH |= GPIO_Mode_OutputPP2Mhz <<4 ;
	*/

    // Configure GPIO Pins (Push Button) = PA0: Input Floating Mode
    GPIO_InitStruct.GPIO_PIN = GPIO_PIN_0;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_InputFloating;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Configure GPIO Pins (LEDs) = PC8 and PC9: Output Push-Pull, 2 MHz
    GPIO_InitStruct.GPIO_PIN = GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OutputPP2Mhz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

	

    while (1)
  {		
		//Test Push Button
 		//Read Oush Button State (0=Pressed, 1=Released)
		EtatBouton=GPIO_TestPin(GPIOA,GPIO_PIN_0);
		
	if (EtatBouton==0)  //If Pressed, Led ON	
	GPIO_SetPin(GPIOC, GPIO_PIN_8|GPIO_PIN_9);
	else //Released, Led OFF
	GPIO_ResetPin(GPIOC, GPIO_PIN_8|GPIO_PIN_9);				
}
}
