#ifndef PINCE_INPUT_H
#define PINCE_INPUT_H

#include <Arduino.h>
#include <Servo.h>
#include "servo_Control.h"
enum Etat_Pince {
    FERMER,
    OUVERT,
    PINCE_LANCEMENT
};

struct Pince_Data{
    Servo Moteur_Pince;
    float angle_ouvert;
    float angle_fermer;
    float angle_lancer;
    Etat_Pince pince_etat;
};

void pince_Init(Pince_Data* pince);
void pince_ouvert(Pince_Data* pince);
void pince_fermer(Pince_Data* pince);
void pince_lancer(Pince_Data* pince);
Etat_Pince pince_get_etat(Pince_Data* pince);







#endif
