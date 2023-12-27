#include <stdint.h>

#define Reg_Enable_RCC    (uint32_t*) 0x40021018 // Adresse du registre RCC_APB2ENR pour activer l'horloge des ports A et C
#define Reg_Config_Led    (uint32_t*) 0x40011004 // Adresse du registre de configuration du Port C (reli� aux LEDs)
#define Reg_BSRR_Led      (uint32_t*) 0x40011010 // Adresse du registre BSRR pour les LEDs
#define Reg_BRR_Led       (uint32_t*) 0x40011014 // Adresse du registre BRR pour les LEDs

#define Reg_Config_Bouton (uint32_t*) 0x40010800 // Adresse du registre de configuration du port A (reli� au bouton)
#define Reg_Bouton        (uint32_t*) 0x40010808 // Adresse du registre en entr�e (IDR) du port A

int etat_bouton; // Variable permettant de lire l'�tat du bouton

int main() {
  // Activer les horloges des ports reli�s aux LEDs et au bouton
  *Reg_Enable_RCC |= (1 << 2) | (1 << 4); // Activer l'horloge pour les ports A et C (bit 2 et bit 4)

  // Configurer les bits reli�s aux LEDs (Port C)
  *Reg_Config_Led &=~(0xFF); // Configurer PC8 et PC9 comme des sorties g�n�rales � 10 MHz
	*Reg_Config_Led |= 0x22;
  // Configurer le bit reli� au bouton (Port A)
  *Reg_Config_Bouton &= ~0x0F; // R�initialiser les bits
  *Reg_Config_Bouton |= 0x04;  // Mettre en mode "Input Floating" pour le bit 0 (bouton)

  while (1) {
    etat_bouton = (*Reg_Bouton) & 0x00000001; // Lire l'�tat du bit reli� au bouton (bit 0 de IDR)

    if (etat_bouton == 0x0001) { // Si le bouton est appuy�
      *Reg_BSRR_Led = 0x0300; // Allumer les LEDs (bits 8 et 9 de BSRR)
    } else { // Sinon
      *Reg_BRR_Led = 0x0300;  // �teindre les LEDs (bits 8 et 9 de BRR)
    }
  }

  return 0;
}
