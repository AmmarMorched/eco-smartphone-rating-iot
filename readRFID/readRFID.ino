#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN D2   // Reset pin
#define SS_PIN D8    // Slave select pin

MFRC522 rfid(SS_PIN, RST_PIN);  // Create an MFRC522 instance

void setup() {
  Serial.begin(115200);  // Initialize serial communications
  SPI.begin();           // Init SPI bus
  rfid.PCD_Init();       // Init MFRC522
  Serial.println("RFID Reader Initialized. Bring the card near the reader to read the data...");
}

void loop() {
  // Look for a new RFID card
  if (!rfid.PICC_IsNewCardPresent()) {
    return;  // No card detected, exit
  }

  // Select one of the cards
  if (!rfid.PICC_ReadCardSerial()) {
    return;  // Couldn't read card, exit
  }

  Serial.println("Card detected!");

  // Block number to read from (same block where the data was written)
  byte block = 4;
  byte buffer[18];  // Buffer to hold read data (16 bytes of data + 2 bytes of CRC)
  byte size = sizeof(buffer);
  MFRC522::MIFARE_Key key;

  // Use the default key (all 0xFF) for authentication
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  // Authenticate to block 4 using the default key
  MFRC522::StatusCode status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(rfid.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Authentication failed: ");
    Serial.println(rfid.GetStatusCodeName(status));
    return;
  }

  // Read block data
  status = rfid.MIFARE_Read(block, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("MIFARE_Read() failed: ");
    Serial.println(rfid.GetStatusCodeName(status));
  } else {
    Serial.print("Data read from block ");
    Serial.print(block);
    Serial.print(": ");

    // Print data as characters
    for (uint8_t i = 0; i < 16; i++) {  // Block size is 16 bytes
      Serial.write(buffer[i]);
    }
    Serial.println();
  }
  // Halt PICC and stop encryption on PCD
  rfid.PICC_HaltA(); 
  rfid.PCD_StopCrypto1(); 
}
