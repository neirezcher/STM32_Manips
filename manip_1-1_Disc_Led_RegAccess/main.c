#include <stdint.h>

#define Reg_Enable_RCC   ((uint32_t*)0x40021018)  // Adresse du registre APB2ENR (pour activer les GPIOs utilisés)
#define GPIOC_CRL        ((uint32_t*)0x40011000)  // Adresse du registre (GPIO C) Configuration de basse
#define GPIOC_CRH        ((uint32_t*)0x40011004)  // Adresse du registre (GPIO C) Configuration de haute
#define Reg_BSRR_Led     ((uint32_t*)0x40011010)  // Adresse du registre permettant la mise à 1 des bits du GPIO C
#define Reg_BRR_Led      ((uint32_t*)0x40011014)  // Adresse du registre permettant la mise à 0 des bits du GPIO C

int main()
{
    int i;

    // Activer l'horloge du port C (relié aux LEDs)
    *Reg_Enable_RCC |= (1U << 4);  // Bit 4 correspondant au GPIOC

    // Configurer les bits reliés aux LEDs en mode de sortie (push-pull)
    *GPIOC_CRL = (*GPIOC_CRL & 0xFF0FFFFF) | 0x00200000;  // PC8
    *GPIOC_CRH = (*GPIOC_CRH & 0xFFF0FFFF) | 0x02000000;  // PC9

    while (1)
    {
        // allumer les deux leds
        *Reg_BSRR_Led = 0x00003000;  // Set BS8 (bit 8) et BS9 (bit 9)

        for (i = 0xFFFFF; i != 0; i--); // Delay

        // Eteindre les deux leds.
        *Reg_BRR_Led = 0x00003000;  // Reset BR8 (bit 8) et BR9 (bit 9)

        for (i = 0xFFFFF; i != 0; i--); // Delay
    }

    return 0;
}
