/*
 * ============================================================================
 * JOYSTICK INPUT - Implémentation
 * ============================================================================
 */

#include "joystick_Input.h"
#include "Config.h"
// Initialiser le joystick
void joystick_Init(Joystick_Data* joy, uint8_t pin_x, uint8_t pin_y, uint8_t pin_button) {
    // Sauvegarder les pins
    joy->pin_X = pin_x;
    joy->pin_Y= pin_y;
    joy->pin_button = pin_button;
    joy->dead_Zone = JOY_DEADZONE;  
    // Initialiser les valeurs
    joy->raw_X = 0;
    joy->raw_Y = 0;
    joy->speed_X = 0;
    joy->speed_Y = 0;

    // Configurer le pin du bouton en INPUT_PULLUP
    if (pin_button != 255) {  // 255 = pas de bouton
        pinMode(pin_button, INPUT_PULLUP);
    }
    
    Serial.print(F("Joystick init - X:A"));
    Serial.print(pin_x - A0);  // Afficher A0, A1, etc.
    Serial.print(F(" Y:A"));
    Serial.println(pin_y - A0);
}

// Calibrer le joystick (trouver le point central)
void joystick_Calibrate(Joystick_Data* joy) {
    Serial.println(F("Calibration joystick..."));
    Serial.println(F("Relâchez le joystick (position neutre)"));
    delay(2000);
    
    // Faire plusieurs lectures pour moyenner
    long sum_x = 0;
    long sum_y = 0;
    const int number_Read = 100; // nombre de lectures
    // On lit 100 fois X et y et on additionne
    for (int i = 0; i < number_Read; i++) {
        sum_x += analogRead(joy->pin_X);
        sum_y += analogRead(joy->pin_Y);
        delay(10);
    }
    // On divise la somme pour obtenir la moyenne qui va devenir le centre du joystick
    joy->center_X = sum_x / number_Read;
    joy->center_Y = sum_y / number_Read;
    
    Serial.print(F("Centre X: "));
    Serial.println(joy->center_X);
    Serial.print(F("Centre Y: "));
    Serial.println(joy->center_Y);
    Serial.println(F("Calibration terminée\n"));
}

// Lire les valeurs du joystick
// Lire les valeurs du joystick
void joystick_Read(Joystick_Data* joy) {
    // Lecture des valeurs analogiques brutes (0-1023)
    joy->raw_X = analogRead(joy->pin_X);
    joy->raw_Y = analogRead(joy->pin_Y);
    
    // Calculer les déviations par rapport au centre
    int16_t deviation_x = joy->raw_X - joy->center_X;
    int16_t deviation_y = joy->raw_Y - joy->center_Y;
    
    // Appliquer la zone morte (deadzone)
    if (abs(deviation_x) < joy->dead_Zone) {
        deviation_x = 0;
    }
    if (abs(deviation_y) < joy->dead_Zone) {
        deviation_y = 0;
    }
    
    // Plage positive = distance du centre jusqu'à 1023
    // Plage négative = distance du centre jusqu'à 0
    int16_t max_positive_x = 1023 - joy->center_X;  // Ex: 1023 - 518 = 505
    int16_t max_negative_x = joy->center_X;         // Ex: 518
    int16_t max_positive_y = 1023 - joy->center_Y;  // Ex: 1023 - 502 = 521
    int16_t max_negative_y = joy->center_Y;         // Ex: 502
    
    // Convertir déviation X en vitesse (-100 à +100)
    if (deviation_x == 0) {
        joy->speed_X = 0;
    }
    else if (deviation_x > 0) {
        // Droite : utiliser la plage positive réelle
        joy->speed_X = map(deviation_x, 
                          joy->dead_Zone,      // Début : deadzone
                          max_positive_x,     
                          0,                   // Vitesse min
                          100);                // Vitesse max
        // Sécurité : limiter à 100
        if (joy->speed_X > 100) joy->speed_X = 100;
    }
    else {
        // Gauche : utiliser la plage négative réelle
        joy->speed_X = map(deviation_x, 
                          -max_negative_x,    
                          -joy->dead_Zone,     // Fin : deadzone
                          -100,                // Vitesse min
                          0);                  // Vitesse max
        // Sécurité : limiter à -100
        if (joy->speed_X < -100) joy->speed_X = -100;
    }
    
    // Convertir déviation Y en vitesse (-100 à +100)
    if (deviation_y == 0) {
        joy->speed_Y = 0;
    }
    else if (deviation_y > 0) {
        // Haut : utiliser la plage positive réelle
        joy->speed_Y = map(deviation_y, 
                          joy->dead_Zone, 
                          max_positive_y,      // ✅ Plage réelle
                          0, 
                          100);
        if (joy->speed_Y > 100) joy->speed_Y = 100;
    }
    else {
        // Bas : utiliser la plage négative réelle
        joy->speed_Y = map(deviation_y, 
                          -max_negative_y,     // ✅ Plage réelle
                          -joy->dead_Zone, 
                          -100, 
                          0);
        if (joy->speed_Y < -100) joy->speed_Y = -100;
    }
    
   
}

// Obtenir la vitesse X
int16_t joystick_GetSpeedX(Joystick_Data* joy) {
    return joy->speed_X;
}

// Obtenir la vitesse Y
int16_t joystick_GetSpeedY(Joystick_Data* joy) {
    return joy->speed_Y;
}

