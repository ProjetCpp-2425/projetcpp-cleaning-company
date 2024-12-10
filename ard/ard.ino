#include <SPI.h>
#include <MFRC522.h>

// Définir les broches pour le module RFID
#define RST_PIN 9 // Broche RST du module RFID
#define SS_PIN 10 // Broche SS du module RFID

// Définir les broches pour la LED et le buzzer
#define LED_VERTE 3
#define BUZZER 4

// Initialiser le module RFID
MFRC522 rfid(SS_PIN, RST_PIN);

// UID attendu (carte autorisée)
byte uidAutorise[] = {0xD3, 0x61, 0xE3, 0x0C};

void setup() {
  // Initialisation des périphériques
  pinMode(LED_VERTE, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(LED_VERTE, LOW);
  digitalWrite(BUZZER, LOW);

  // Initialisation du port série pour le débogage
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("Scanner RFID prêt.");
}

void loop() {
  // Vérifier s'il y a une nouvelle carte
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.println("Carte détectée!");

  // Vérifier si le UID correspond
  if (verifierUID(rfid.uid.uidByte, rfid.uid.size)) {
    Serial.println("Carte autorisée!");
    digitalWrite(LED_VERTE, HIGH);
    buzzerIntermittent(); // Bip intermittent
  } else {
    Serial.println("Carte non reconnue!");
    digitalWrite(LED_VERTE, LOW);
    buzzerContinu(); // Bip continu
  }

  delay(2000); // Attendre 2 secondes avant de réinitialiser
  digitalWrite(LED_VERTE, LOW);
  digitalWrite(BUZZER, LOW);

  rfid.PICC_HaltA(); // Arrêter la communication avec la carte
}

// Fonction pour vérifier le UID
bool verifierUID(byte *uid, byte taille) {
  if (taille != sizeof(uidAutorise)) return false;
  for (byte i = 0; i < taille; i++) {
    if (uid[i] != uidAutorise[i]) return false;
  }
  return true;
}

// Fonction pour faire un bip intermittent
void buzzerIntermittent() {
  for (int i = 0; i < 5; i++) { // 5 bips
    digitalWrite(BUZZER, HIGH);
    delay(200); // 200ms ON
    digitalWrite(BUZZER, LOW);
    delay(200); // 200ms OFF
  }
}

// Fonction pour faire un bip continu
void buzzerContinu() {
  digitalWrite(BUZZER, HIGH);
  delay(2000); // 2 secondes de bip continu
  digitalWrite(BUZZER, LOW);
}