#include <gpio.h>

/*
Cette fonction lit l'�tat de la broche sp�cifi�e (GPIO_PIN) en effectuant un "et" logique avec le registre IDR 
("Input Data Register" - pour lire l'�tat de la broche)
Si le r�sultat n'est pas z�ro, cela signifie que la broche est � l'�tat haut (1),
sinon, elle est � l'�tat bas (0). La fonction renvoie 1 pour l'�tat haut et 0 pour l'�tat bas.
*/
int	GPIO_TestPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN) {
    // Utilisez IDR pour lire l'�tat de la broche.
    if ((GPIOx->IDR & GPIO_PIN) != 0) {
        // La broche est � l'�tat haut (1)
        return 1;
    } else {
        // La broche est � l'�tat bas (0)
        return 0;
    }
}

void GPIO_SetPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN) {
    // Utilisez BSRR pour d�finir la broche � l'�tat haut.
    GPIOx->BSRR = (1 << GPIO_PIN);
}

void GPIO_ResetPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN) {
    // Utilisez BRR pour r�initialiser la broche � l'�tat bas.
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

