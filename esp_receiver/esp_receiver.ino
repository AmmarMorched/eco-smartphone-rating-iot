#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include <MFRC522.h>
#include <SPI.h>

const char* ssid = "HomeInKernel";         // Replace with your Wi-Fi network name
const char* password = "H0m31nR0uter8010"; // Replace with your Wi-Fi password

ESP8266WebServer server(80);  // Create a server object on port 80
Servo myServo;  // Create a Servo object

#define RST_PIN D8   
#define SS_PIN D2

MFRC522 rfid(SS_PIN, RST_PIN);


void handleData() {
  if (server.hasArg("plain")) {  // Check if there's data in the request body
    String data = server.arg("plain");
    Serial.println("Data received from Raspberry Pi:");
    Serial.println(data);  // Print the received data to the Serial Monitor

    // Parse JSON
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, data);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.f_str());
      return;
    }
    // Extract eco_rating value from JSON
    String ecoRatingStr = doc["eco_rating"].as<String>();
    String model = doc["model_number_info"].as<String>(); 
    int ecoRating = ecoRatingStr.toInt();  // Convert eco_rating to integer

    // Debug print statements
    Serial.print("Extracted eco_rating: ");
    Serial.println(ecoRatingStr);  // Print the extracted string value
    Serial.print("Parsed eco_rating: ");
    Serial.println(ecoRating);  // Print the parsed integer value
    Serial.print("Extracted Model: ");
    Serial.println(model); 

    // Map eco_rating (0-100) to servo angle (0-180 degrees)
    int servoAngle = map(ecoRating, 0, 100, 0, 180);
    servoAngle = servoAngle  +35;
    myServo.write(servoAngle);   // Move servo to the corresponding angle
    delay(1000)  ;
  
    Serial.print("Servo Angle: ");
    Serial.println(servoAngle); 
    

    // Wait for RFID card to be placed
    Serial.println("Waiting for RFID card...");
    while (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
      delay(100);  // Short delay to prevent too many serial prints
    }

    // At this point, the card is detected
    Serial.println("RFID card detected! Writing eco_rating to RFID tag...");
    writeDataToRFID(model);  // Write eco_rating to RFID tag

    // Halt the RFID reading process
    rfid.PICC_HaltA();

  server.send(200, "text/plain", "Data received");  // Send response back
}
}

void setup() {
  Serial.begin(115200);  
  myServo.attach(D4);  
  SPI.begin();  // Initialize SPI bus
  rfid.PCD_Init();
  Serial.println("RFID Reader Initialized");
  WiFi.begin(ssid, password);  

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());  

  server.on("/", HTTP_POST, handleData);  
  server.begin();  // Start the server
  Serial.println("Server started");

}

void loop() {
  myServo.write(0);
  server.handleClient();  
}


void writeDataToRFID(String data) {
  MFRC522::StatusCode status;
  byte buffer[16];
  byte block = 4;  // The block number to write to (4 is a common user block)
  MFRC522::MIFARE_Key key;

  // Using default key for authentication (all 0xFF)
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  data.getBytes(buffer, sizeof(buffer));

  // Authenticate to block 4 using the default key
  status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(rfid.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Authentication failed: ");
    Serial.println(rfid.GetStatusCodeName(status));
    return;
  }

  // Write the data to block 4 of the RFID tag
  status = rfid.MIFARE_Write(block, buffer, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("MIFARE_Write() failed: ");
    Serial.println(rfid.GetStatusCodeName(status));
  } else {
    Serial.println("Data written to RFID tag successfully.");
  }

  // Stop authentication
  rfid.PICC_HaltA(); 
  rfid.PCD_StopCrypto1(); 
}




