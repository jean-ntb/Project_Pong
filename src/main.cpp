/*
 * ============================================================================
 * PONG ARENA - Mobilité + Contrôle Pince
 * ============================================================================
 */

#include <Arduino.h>
#include "servo_Control.h"
#include "joystick_Input.h"
#include "button_Input.h"
#include "pince_Control.h"
#include "Config.h"

// Variables globales
Servo_Data servo_move;
Joystick_Data joystick;
Button_Data bouton;
Pince_Data pince;

void setup() {
    Serial.begin(9600);
    delay(500);
    
    Serial.println(F("\n╔═══════════════════════════════════════╗"));
    Serial.println(F("║  PONG ARENA - Contrôle Complet        ║"));
    Serial.println(F("║  Joystick + Bouton + Pince            ║"));
    Serial.println(F("╚═══════════════════════════════════════╝\n"));
    
    // ===== INITIALISATION SERVO DÉPLACEMENT =====
    Serial.println(F("--- Initialisation Servo Déplacement ---"));
    servo_Init(&servo_move, PIN_SERVO_X);
    delay(500);
    
    // ===== INITIALISATION PINCE =====
    Serial.println(F("--- Initialisation Pince ---"));
    pince_Init(&pince);
    delay(500);
    
    // ===== INITIALISATION BOUTON =====
    Serial.println(F("--- Initialisation Bouton ---"));
    bouton.pin = PIN_BUTTON;
    button_Init(&bouton);
    
    // ===== INITIALISATION JOYSTICK =====
    Serial.println(F("\n--- Initialisation Joystick ---"));
    joystick_Init(&joystick, PIN_JOY_X, PIN_JOY_Y, 255);  // Pas de bouton joystick
    joystick_Calibrate(&joystick);
    
    Serial.println(F("\n╔═══════════════════════════════════════╗"));
    Serial.println(F("║  SYSTÈME PRÊT                         ║"));
    Serial.println(F("║  Joystick = Déplacement               ║"));
    Serial.println(F("║  Bouton = Fermer/Lancer pince         ║"));
    Serial.println(F("╚═══════════════════════════════════════╝\n"));
    
    delay(1000);
}

void loop() {
    // ===== MISE À JOUR BOUTON =====
    button_Update(&bouton);
    
    // ===== GESTION PINCE AVEC BOUTON =====
    if (button_AppuiDetecte(&bouton)) {
        Serial.println(F("🔒 Bouton appuyé → Pince FERMÉE"));
        pince_fermer(&pince);
    }
    
    if (button_RelacheDetecte(&bouton)) {
        Serial.println(F("🚀 Bouton relâché → Pince LANCE la balle"));
        pince_lancer(&pince);
    }
    
    // ===== LECTURE JOYSTICK =====
    joystick_Read(&joystick);
    
    // ===== CONTRÔLE SERVO AVEC JOYSTICK =====
    int16_t vitesse_deplacement = joystick_GetSpeedY(&joystick);
    servo_SetSpeed(&servo_move, vitesse_deplacement);
    
    // ===== AFFICHAGE DEBUG =====
    #ifdef DEBUG_MODE
    Serial.print(F("Joy Y: "));
    Serial.print(joystick.speed_Y);
    Serial.print(F(" → Servo: "));
    Serial.print(vitesse_deplacement);
    Serial.print(F(" | Pince: "));
    
    switch(pince_get_etat(&pince)) {
        case OUVERT:
            Serial.print(F("OUVERTE"));
            break;
        case FERMER:
            Serial.print(F("FERMÉE"));
            break;
        case PINCE_LANCEMENT:
            Serial.print(F("LANCEMENT"));
            break;
    }
    
    Serial.print(F(" | Bouton: "));
    Serial.println(button_EstAppuye(&bouton) ? F("APPUYÉ") : F("RELÂCHÉ"));
    #endif
    
    delay(50);  // 20 Hz
}