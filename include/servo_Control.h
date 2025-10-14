/*
 * ============================================================================
 * SERVO CONTROL
 * ============================================================================
 * Génération PWM  pour servo 
 */

#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H
#include <Config.h>
#include <Servo.h>
typedef struct {
    Servo Motor_Servo;
    uint8_t pin;            // Pin physique
    uint16_t neutral_pwm ;   // Valeur arrêt (ticks Timer1)
    uint16_t min_pwm;       // Rotation arrière
    uint16_t max_pwm;       // Rotation avant
    int16_t current_speed;  // Vitesse
} Servo_Data;

// Fonctions publiques
void servo_Init(Servo_Data* servo, int pin);
void servo_SetSpeed(Servo_Data* servo, int speed);
void servo_Stop(Servo_Data* servo);
int servo_GetCurrentSpeed(Servo_Data* servo);
#endif // SERVO_CONTROL_H