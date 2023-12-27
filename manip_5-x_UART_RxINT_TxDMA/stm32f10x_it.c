// Interupts EXTI Project

/**
  ******************************************************************************
  * @file    EXTI/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15/09/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */



/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

void Delay(vu32 nCount);
uint8_t stringCompare(char str1[],char str2[], uint8_t StrLength);


/** @addtogroup Examples
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles External line0 interrupt request.
  * @param  None
  * @retval None
  */

void EXTI15_10_IRQHandler(void)
{
    

	if (EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
        // Code à ajouter pour assurer le fonctionnement désiré
        // Allumer les deux LEDs, par exemple
        GPIO_SetBits(GPIOA, GPIO_Pin_5);  // Allumer la LED connectée à la broche PA5
        GPIO_SetBits(GPIOC, GPIO_Pin_5);  // Allumer une autre LED connectée à la broche PB5
        
        // Remise à zéro du bit déclenchant l'interruption
        EXTI_ClearITPendingBit(EXTI_Line13);
    }

}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles DMA interrupt requests.
  * @param  None
  * @retval None
  */
extern char Transmit_Buffer[11];
void DMA1_Channel7_IRQHandler(void)
{
//		 /* Test on DMAx Channely Transfer Complete interrupt */
		if (DMA_GetITStatus(DMA1_IT_TC7))
  {
//    /* Code a ajouter pour assurer le fonctionnement désiré */		
      DMA1_Channel7->CMAR = (uint32_t)&Transmit_Buffer[0]; // Réinitialiser le pointeur mémoire
      DMA1_Channel7->CNDTR = sizeof(Transmit_Buffer); // Réinitialiser le nombre d'éléments à transférer

//		
//		/* Clear DMAx Channely TC interrupt pending bit*/
		DMA_ClearITPendingBit(DMA1_IT_TC7); 
	}

//  /* Test on DMAx Channely Transfer Half interrupt */
		if (DMA_GetITStatus(DMA1_IT_HT7))
		{
//    /* Code a ajouter pour assurer le fonctionnement désiré */
			DMA1_Channel7->CMAR = (uint32_t)&Transmit_Buffer[0]; // Réinitialiser le pointeur mémoire
      DMA1_Channel7->CNDTR = sizeof(Transmit_Buffer) / 2; // Réinitialiser le nombre d'éléments à transférer

//		/* Clear DMAx Channely HT interrupt pending bit */
		DMA_ClearITPendingBit(DMA1_IT_HT7);
		}

}


  int i;
	extern char Receive_Buffer[10];
	extern char password[];
	extern uint8_t Nbre_Received_Caracters;
/**
  * @brief  This function handles USART1 RX interrupt requests.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void) {
    if (USART_GetITStatus(USART2, USART_IT_RXNE)) {
        char received_char = USART_ReceiveData(USART2);

        // Votre code pour traiter le caractère reçu
        Receive_Buffer[Nbre_Received_Caracters] = received_char;
        Nbre_Received_Caracters++;

        if (Nbre_Received_Caracters == 10) {
            if (stringCompare(Receive_Buffer, password, 10)) {
                // Code correct, allumer la LED
                GPIO_SetBits(GPIOA, GPIO_Pin_5);
                Delay(0xFFFFF);
            } else {
                // Code incorrect, faire clignoter la LED lentement
                for (int i = 0; i < 3; ++i) {
                    GPIO_SetBits(GPIOA, GPIO_Pin_5);
                    Delay(0xFFFFF);
                    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
                    Delay(0xFFFFF);
                }
            }

            // Réinitialiser le compteur de caractères reçus
            Nbre_Received_Caracters = 0;
        }
    }
}

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
