#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialisation de l'écran LCD avec l'adresse I2C, 16 colonnes, et 2 lignes
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variables des services
String services[30];
int nbServices = 0;
int serviceActuel = 0;

// Gestion du temps pour l'affichage automatique
unsigned long dernierChangement = 0;
const unsigned long intervalleAffichage = 6000; // 6 secondes

void setup() {
    lcd.init();              // Initialisation de l'écran LCD
    lcd.backlight();         // Allumer le rétroéclairage
    Serial.begin(9600);
    lcd.print("Attente donnees...");
}

void loop() {
    // Vérification des données reçues via Serial
    if (Serial.available() > 0 && nbServices == 0) {
        String data = Serial.readString();
        parseServices(data);
        afficherService();
    }

    // Si des services sont disponibles, les afficher automatiquement
    if (nbServices > 0) {
        if (millis() - dernierChangement >= intervalleAffichage) {
            serviceActuel = (serviceActuel + 1) % nbServices; // Passer au service suivant
            afficherService();
            dernierChangement = millis(); // Mettre à jour le temps du dernier changement
        }
    }
}

void afficherService() {
    lcd.clear();
    lcd.print("Service:");
    lcd.setCursor(0, 1);
    lcd.print(services[serviceActuel]);
}

void parseServices(String data) {
    int start = 0;
    int index = 0;

    while ((index = data.indexOf(';', start)) != -1 && nbServices < 30) {
        services[nbServices++] = data.substring(start, index);
        start = index + 1;
    }
}
