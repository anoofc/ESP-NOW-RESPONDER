#define DEBUG      1
#define LEDPIN     18
#define NUMPIXELS  25

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

// // Define a data structure
typedef struct struct_message {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} struct_message;

// Create a structured object
struct_message myData;


// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  if (DEBUG){Serial.print("Red: "); Serial.println(myData.red);}
  if (DEBUG){Serial.print("Green: "); Serial.println(myData.green);}
  if (DEBUG){Serial.print("Blue: "); Serial.println(myData.blue);}
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(myData.red, myData.green, myData.blue));
  }
  strip.show();
}

// On Data Receive Callback

// void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
//   Serial.print("Received data: ");
//   for (int i = 0; i < len; i++) {
//     Serial.print(incomingData[i]);
//     Serial.print(" ");
//   }
//   Serial.println();
// }


void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);
  
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    if (DEBUG){Serial.println("Error initializing ESP-NOW");}
    return;
  }
  
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}