#include <gpio.h>

/*
Cette fonction lit l'état de la broche spécifiée (GPIO_PIN) en effectuant un "et" logique avec le registre IDR 
("Input Data Register" - pour lire l'état de la broche)
Si le résultat n'est pas zéro, cela signifie que la broche est à l'état haut (1),
sinon, elle est à l'état bas (0). La fonction renvoie 1 pour l'état haut et 0 pour l'état bas.
*/
int	GPIO_TestPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN) {
    // Utilisez IDR pour lire l'état de la broche.
    if ((GPIOx->IDR & GPIO_PIN) != 0) {
        // La broche est à l'état haut (1)
        return 1;
    } else {
        // La broche est à l'état bas (0)
        return 0;
    }
}

void GPIO_SetPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN) {
    // Utilisez BSRR pour définir la broche à l'état haut.
    GPIOx->BSRR = (1 << GPIO_PIN);
}

void GPIO_ResetPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN) {
    // Utilisez BRR pour réinitialiser la broche à l'état bas.
    GPIOx->BRR = (1 << GPIO_PIN);
}
void GPIO_Init (GPIO_TypeDef* GPIOx,  GPIO_Struct*   GPIO_InitStruct){
	int t=0;
	int i=0;
	for (i=0;i<16;i++){
		t=GPIO_InitStruct->GPIO_PIN & (1<<i);
		if (t!=0){
			if (i<=7){
				GPIOx->CRL &= ~(0xF<<(4*i));
				GPIOx->CRL |= GPIO_InitStruct->GPIO_Mode <<(4*i);
			}
			else{
				GPIOx->CRH &= ~(0xF<<(4*(i-8)));
				GPIOx->CRH |= GPIO_InitStruct->GPIO_Mode <<(4*(i-8));
			}						
		}
	}
}

