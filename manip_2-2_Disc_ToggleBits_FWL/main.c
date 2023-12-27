
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/*----------------- Déclaration des structures relatives aux periphs utilisés ---------------*/
GPIO_InitTypeDef  GPIO_InitStructure;

/* ---------------Private functions ---------------*/
void Delay(vu32 nCount);
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t appui; // variable appui pour lire l'etat du bouton

int main(void)
{ /*---------- Activer les horloges des ports utilsés (port A et port C)------------ */ 
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA,ENABLE);

/*-------------- Configure the GPIO_LED pin -----------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

/*-------------- Configure the GPIO_ Pushbutton pin -----------------*/
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	
/*-------------- Initialization -----------------*/
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  
/* ---------  Led PC8 ON, Led PC9 OFF ---------- */
GPIO_SetBits(GPIOC,GPIO_Pin_8);
GPIO_ResetBits(GPIOC,GPIO_Pin_9);


while (1)
 	 {
		 appui = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);

if(appui)	         {
 GPIO_ToggleBits(GPIOC,GPIO_Pin_8|GPIO_Pin_9);
 Delay (0xFF);
  	          }

          }
   }
/*******************************************************************************
* Function Name  : Delay
* Description    : Inserts a delay time.
* Input          : nCount: specifies the delay time length.
*******************************************************************************/
void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->ODR ^= GPIO_Pin;
}

/*GPIOx->ODR accède au registre Output Data Register du port GPIO spécifié.

^= est l'opérateur XOR (ou exclusif). En utilisant cet opérateur avec GPIO_Pin, cela bascule les bits correspondants du registre ODR. Si un bit est à 1, il deviendra 0, et s'il est à 0, il deviendra 1.*/
