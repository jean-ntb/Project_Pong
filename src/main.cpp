#include <Arduino.h>
#include <HardwareSerial.h>

// Déclaration fonction
int myFunction(int, int);

void setup() {
    // ✅ INITIALISER Serial
    Serial.begin(9600);
    // Attendre que Serial soit prêt (optionnel mais recommandé)
    delay(500);
    // Message de démarrage
    Serial.println("=== DÉMARRAGE ===");
    // Test de la fonction
    int result = myFunction(2, 3);
    Serial.print("Résultat myFunction: ");
    Serial.println(result);
}

void loop() {
    // ✅ Utiliser Serial.println() au lieu de printf()
    Serial.println("Gabriel Santana de la Vega Dasilva Montero de Montenegro");
    digitalWrite(LED_BUILTIN,LOW);
}

// Définition fonction
int myFunction(int x, int y) {
    return x + y;
}