/* ***************************************************************************/
/* WRAPPER LAYER : ADAPT OO Pin REPRESENTATION (mbed) TO ST Firmware Libraray*/
/* OO Representation : PA_0 = 0x01, PA_1=0x01, ...., PA_15=0x0F              */
/*                   : PB_0 = 0x11, PB_1=0x11, ...., PB_15=0x1F              */
/*																																           */
/* OO --> ST Firmware  : PA_0 --> GPIOA, GPIO_Pin_0 							           */
/*											 PB_12 --> GPIOB, GPIO_Pin_12							           */
/* Emir DAMERGI  -  INSAT 2021                                               */

/* ***************************************************************************/

#include "stm32_wrapper_gpio.h"

/*================================================*/
/*     Part 1: Functions For PinAsInput Class     */
/*================================================*/


/*=== Functions Called by The PinAsInput Constructors ===*/

/*Constructor Without Mode = Default = Floating*/
void gpio_init_in_def(PinName pin) 
{
    gpio_init_in (pin, InDefault);
}

/*Constructor With Mode */
void gpio_init_in (PinName pin, PinInMode mode)
{
    _gpio_init_in(pin, mode);
}


/*=== Function To get gpio mode for ST FW lib === */
static int get_gpio_in_mode (PinInMode mode)
{	
	switch (mode){
		case 0: return GPIO_Mode_IN_FLOATING;
		case 1: return GPIO_Mode_IPU;
		case 2: return GPIO_Mode_IPD;
		default: return GPIO_Mode_IN_FLOATING; 
		}
}

/*=== Function To read Pin Value from IDR ====== */
	int gpio_read(PinName pin)
{
	int pinID = (pin & 0x0F);
	int pinValue =  (get_gpioport(pin)->IDR) & (1<<pinID);
	return (pinValue) ;
}

/*--------------------------------------------------------------*/
/*   INITIALLIZATION FUNCTION for PinAsInput Objects :          */          
/*      - Translates OO Pin Represetation (Px_i) to ST FWL      */
/*      - And Calls ST FWLibrary Functions                      */
/*--------------------------------------------------------------*/
static void _gpio_init_in(PinName pin, PinInMode mode)
{

		//get the gpioID from PinName (0 for GPIOA, 1 for GPIOB, ...) 	
	int gpioID = (pin & 0xF0) >> 4; 
	
	RCC_APB2PeriphClockCmd( 1<<(gpioID+2) , ENABLE);	
	
	  //convert gpioID to GPIOx
	GPIO_TypeDef* GPIOx = get_gpioport(pin);


		//Fills GPIO Structure and Calls GPIO_Init (ST FW Lib)
	GPIO_InitTypeDef GPIO_InitStruct; 

	GPIO_InitStruct.GPIO_Pin = 1<<(pin & 0x0F);
	
	GPIO_InitStruct.GPIO_Mode = (GPIOMode_TypeDef)get_gpio_in_mode(mode);

	GPIO_Init( GPIOx,  &GPIO_InitStruct);		
	}

/*=========== End PinAsInput Class Functions =============*/


	
/*-------------------------------------------------*/
	/* Common Function : To get GPIOx From PinName Value */
/*_________________________________________________*/
	
static GPIO_TypeDef* get_gpioport (PinName pin)
{
	int gpioID = (pin & 0xF0) >> 4; 
		
	GPIO_TypeDef* GPIOx;
	
	switch (gpioID){
		case 0x00: GPIOx=GPIOA; break;
		case 0x01: GPIOx=GPIOB; break;
		case 0x02: GPIOx=GPIOC; break;
		case 0x03: GPIOx=GPIOD; break;
		default: break;
		}
	return GPIOx;
}
