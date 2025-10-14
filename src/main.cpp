/*
 * ============================================================================
 * PONG ARENA -  Mobilité axe X
 * ============================================================================
 * Le joystick contrôle le servo qui déplace le chariot
 */

#include <Arduino.h>
#include "servo_Control.h"
#include "joystick_Input.h"
#include "Config.h"
// Variables globales
Servo_Data servo_chariot;
Servo_Data servo_move;
Joystick_Data joystick;

void setup() {
    Serial.begin(9600);
    delay(500);
    
    Serial.println(F("\n╔═══════════════════════════════════════╗"));
    Serial.println(F("║  PONG ARENA - Sprint 1 : Mobilité    ║"));
    Serial.println(F("║  Joystick → Servo → Chariot          ║"));
    Serial.println(F("╚═══════════════════════════════════════╝\n"));
    
    // ===== INITIALISATION SERVO =====
    Serial.println(F("--- Initialisation Servo ---"));
    servo_Init(&servo_chariot, 9);  // Pin 9
    servo_Init(&servo_move,A2);
    delay(500);
    
    // ===== INITIALISATION JOYSTICK =====
    Serial.println(F("\n--- Initialisation Joystick ---"));
    joystick_Init(&joystick, PIN_JOY_X, PIN_JOY_Y, 2);  // X=A0, Y=A1, Button=D2
    
    // Calibration automatique
    joystick_Calibrate(&joystick);
    
    Serial.println(F("\n╔═══════════════════════════════════════╗"));
    Serial.println(F("║  SYSTÈME PRÊT                         ║"));
    Serial.println(F("║  Bougez le joystick en X (gauche/droite) ║"));
    Serial.println(F("╚═══════════════════════════════════════╝\n"));
    
    delay(1000);
}

void loop() {
    // ===== LECTURE JOYSTICK =====
    joystick_Read(&joystick);
     Serial.print("Raw X: ");
    Serial.print(joystick.raw_X);
    Serial.print(" Speed X: ");
    Serial.println(joystick.speed_X);
    // ===== CONTRÔLE SERVO AVEC JOYSTICK X =====
    int16_t vitesse_chariot = joystick_GetSpeedX(&joystick);
    int16_t vitesse_Move = joystick_GetSpeedY(&joystick);

    servo_SetSpeed(&servo_chariot, vitesse_chariot);
    servo_SetSpeed(&servo_move,vitesse_Move);
    // ===== AFFICHAGE DEBUG =====
    Serial.print(F("Joy X: "));
    Serial.print(joystick.speed_X);
    Serial.print(F(" → Servo: "));
    Serial.print(vitesse_chariot);
    Serial.print(F(" | Raw: "));
    Serial.println(joystick.raw_X);
    Serial.print(F("Joy Y: "));
    Serial.print(joystick.speed_Y);
    Serial.print(F(" → Servo: "));
    Serial.print(vitesse_Move);
    Serial.print(F(" | Raw: "));
    Serial.println(joystick.raw_Y);
    // Pause pour ne pas surcharger Serial
    delay(50);  // 20 lectures par seconde
}