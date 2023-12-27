#include <stdint.h>
#include <stm32map.h>


//1- Define the GPIO Pins
#define GPIO_PIN_0                 ((uint16_t)0x0001)  
#define GPIO_PIN_1                 ((uint16_t)0x0002)
#define GPIO_PIN_8                 ((uint16_t)0x0100)  // Ajout de GPIO_PIN_8
#define GPIO_PIN_9                 ((uint16_t)0x0200)  // Ajout de GPIO_PIN_9

typedef struct {
    uint16_t GPIO_PIN;
    uint8_t GPIO_Mode;
} GPIO_Struct;

//2 - Define The Mode Values
#define GPIO_Mode_InputFloating 0x01
#define GPIO_Mode_OutputPP2Mhz 0x02
#define GPIO_Mode_OutputPP10Mhz 0x04
#define GPIO_Mode_OutputPP50Mhz 0x08

//3- Functions Proyotypes

int GPIO_TestPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_PIN);
void GPIO_SetPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_PIN);
void GPIO_ResetPin (GPIO_TypeDef* GPIOx, uint16_t GPIO_PIN);
void GPIO_Init (GPIO_TypeDef* GPIOx,  GPIO_Struct*   GPIO_InitStruct);

