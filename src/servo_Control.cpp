/*
 * ============================================================================
 * SERVO CONTROL - Implémentation
 * ============================================================================
 * Module de pilotage servo-moteur continu FS5103R
 */

#include <servo_Control.h>
#include <Arduino.h>
#include  <Config.h>
void servo_Init(Servo_Data* servo, int pin) {
    servo->pin = pin;
    servo-> neutral_pwm = SERVO_NEUTRAL_PWM;
    servo->min_pwm  = SERVO_MIN_PWM ;
    servo->max_pwm = SEVRVO_MAX_PWM ;
    servo->current_speed = 0;
    servo-> Motor_Servo.attach(pin);
    servo->Motor_Servo.writeMicroseconds(servo->neutral_pwm);
    Serial.println(pin);
}

void servo_SetSpeed(Servo_Data*servo, int speed) {
    // Limiter
    if (speed > 100) speed = 100;
    if (speed < -100) speed = -100;
    servo->current_speed = speed;
    // Conversion vitesse → PWM
    int pwm_value;
    if (speed == 0) {
        pwm_value = servo->neutral_pwm;
    }
    else if (speed > 0) {
        pwm_value = map(speed, 0, 100, servo->neutral_pwm, servo->max_pwm);
                    
    }
    else {
        pwm_value = map(speed, -100, 0, servo->min_pwm, servo->neutral_pwm);
    }
    
    servo->Motor_Servo.writeMicroseconds(pwm_value);
}

void servo_Stop(Servo_Data* servo) {
    servo_SetSpeed(servo, 0);
}

int servo_GetCurrentSpeed(Servo_Data* servo) {
    return servo->current_speed;
}
