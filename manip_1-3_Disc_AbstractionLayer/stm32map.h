#include <stdint.h>



//GPIO BASE ADDRESSES REGISTERS
#define   GPIOA_BASE	  (0x40010800)
#define   GPIOB_BASE	  (0x40010C00)
#define   GPIOC_BASE	  (0x40011000)


//Define GPIO_Typedef strcuture containing The GPIO Registers

typedef struct {
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_TypeDef;


//define Pointers to GPIO Strcutures 
	
#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *)GPIOC_BASE)
