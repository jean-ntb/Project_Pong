#include "button_Input.h"
#include <Arduino.h>

void button_Init(Button_Data* btn) {
    // Configuration de la broche en entrée avec pull-up interne
    pinMode(btn->pin, INPUT_PULLUP);
    
    // Initialisation de l'état
    // Avec INPUT_PULLUP, le bouton non appuyé = HIGH
    btn->etat_actuel = BTN_RELEASED;
    btn->appuie_detect = false;
}

void button_Update(Button_Data* btn) {
    // Lecture de l'état actuel de la broche
    // Avec INPUT_PULLUP : LOW = bouton appuyé, HIGH = bouton relâché
    int lecture = digitalRead(btn->pin);
    
    // Détection d'un front descendant (transition HIGH -> PRESSED)
    if (btn->etat_actuel == HIGH && lecture == LOW) {
        btn->etat_actuel = BTN_PRESSED;
        btn->appuie_detect = true;
    }
    // Détection d'un front montant (transition PRESSED -> HIGH)
    else if (btn->etat_actuel == BTN_PRESSED && lecture == HIGH) {
        btn->etat_actuel = BTN_RELEASED;
    }
}

bool button_EstAppuye(Button_Data* btn) {
    // Retourne true si le bouton est actuellement appuyé
    return (btn->etat_actuel == BTN_PRESSED);
}

bool button_AppuiDetecte(Button_Data* btn) {
    // Retourne true une seule fois par appui
    if (btn->appuie_detect) {
        btn->appuie_detect = false;  // Réinitialisation du flag
        return true;
    }
    return false;
}