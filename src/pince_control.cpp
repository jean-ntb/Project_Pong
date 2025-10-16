#include "Config.h"
#include "pince_Control.h"

void pince_Init(Pince_Data* pince){
    pince->angle_fermer = 0;
    pince->angle_ouvert = 90;
    pince->angle_ouvert = 180;
    pince->pince_etat = OUVERT;
    pince->Moteur_Pince.attach(PIN_SERVO_Y);
    pince->Moteur_Pince.write(pince->angle_ouvert);
}

void pince_ouvert(Pince_Data* pince) {
    pince->Moteur_Pince.write(pince->angle_ouvert);
    pince->pince_etat = OUVERT;
}

void pince_fermer(Pince_Data* pince) {
    pince->Moteur_Pince.write(pince->angle_fermer);
    pince->pince_etat = FERMER;

}
void pince_lancer(Pince_Data* pince) {
    pince->Moteur_Pince.write(pince->angle_fermer);
    pince->pince_etat = PINCE_LANCEMENT;

    pince->Moteur_Pince.write(pince->angle_ouvert);
        pince->pince_etat = OUVERT;

}
Etat_Pince pince_get_etat(Pince_Data * pince) {
    return pince->pince_etat;
}

