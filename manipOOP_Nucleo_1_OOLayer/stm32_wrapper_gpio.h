#include "stm32f10x.h"
#include "Pin_Mode_Names.h"

#ifndef __STM32_WRAPPER_GPIO_H
#define __STM32_WRAPPER_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* =======================================*/
/* 1 : Functions For PinAsInput Class --- */
/*----------------------------------------*/
	
void gpio_init_in_def(PinName pin);	
	
void gpio_init_in(PinName pin, PinInMode mode);

static void _gpio_init_in(PinName pin, PinInMode mode );

int gpio_read (PinName thepin);	
	
static int get_gpio_in_mode (PinInMode mode);	
/*==========================================*/


	
/* --- 2 : Common Functions ---- */

/*  Get the GPIOx From PinName  */
static GPIO_TypeDef* get_gpioport (PinName pin);
	

#ifdef __cplusplus
}
#endif


#endif //__STM32_WRAPPER_GPIO_H
