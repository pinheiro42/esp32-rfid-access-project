#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>

#define SS_PIN 5
#define RST_PIN 2
#define LED_RED 12
#define LED_GREEN 13
#define BUZZER_PIN 27
#define RELAY_PIN 26
int status = 0;

MFRC522 rfid(SS_PIN, RST_PIN);
byte authorizedUID[] = { 0xD3, 0x57, 0xB1, 0x0D };

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  EEPROM.get(0, status);
  
  if (status != 0 && status != 1) {  
    Serial.println("No valid value found, setting default OFF");
    status = 0;
    EEPROM.put(0, status);
    EEPROM.commit();
  }

  digitalWrite(RELAY_PIN, status == 1 ? LOW : HIGH);
  digitalWrite(LED_GREEN, status == 1 ? HIGH : LOW);
  Serial.print("Stored relay status: ");
  Serial.println(status);
  
  Serial.println("Scan an RFID tag...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  } 

  Serial.print("Scanned UID: ");
  bool isAuthorized = true;
  
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (authorizedUID[i] != rfid.uid.uidByte[i]) {
      isAuthorized = false;
    }
  }

  Serial.println();
  
  if (isAuthorized) {
    Serial.println("Access Granted!");

    status = (status == 0) ? 1 : 0;
    digitalWrite(LED_GREEN, status ? HIGH : LOW);
    digitalWrite(RELAY_PIN, status ? LOW : HIGH);
    Serial.println(status ? "Relay ON" : "Relay OFF");

    EEPROM.put(0, status);
    EEPROM.commit();
  } else {
    Serial.println("Access Denied!");
    digitalWrite(LED_RED, HIGH);
    tone(BUZZER_PIN, 500, 500);
    delay(500);
    digitalWrite(LED_RED, LOW);
  }

  rfid.PICC_HaltA();
}
