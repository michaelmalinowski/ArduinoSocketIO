

#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "Amigo";        // your network SSID (name)
char pass[] = "ginatony";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(10,0,0,8);  // numeric IP for Google (no DNS)
char server[] = "10.0.0.8";
int port = 80; 

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient wifi;

WebSocketClient client = WebSocketClient(wifi, server, port);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  //while (!Serial) { // wait for serial port to connect. Needed for native USB port only}
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWiFiStatus();

  Serial.println("\nStarting connection to server...");
}

void loop() {
    int start_time = millis();
    int current_time = millis();
    Serial.println("starting WebSocket client");
    client.begin("/socket.io/?transport=websocket");



    int count = 0;
    while (client.connected()) {
      current_time = millis();
      if ((current_time - start_time)/1000 >= 15){
        ++count;
        client.beginMessage(TYPE_TEXT);
        client.print("42[\"arduino\",\"Keep Arduino Alive\"]");
        client.endMessage();   
        start_time = millis();
        Serial.println("Keep Alive");
        lcd.clear();
        lcd.print(count);
      }

      byte b = client.read();
      if (int(b) <= 254){
        Serial.print(char(b));
      } 
      //client.beginMessage(TYPE_TEXT);
      //client.print("42[\"hello\",\"there\"]");
      //client.endMessage();
    }
    Serial.println("DC");
    
      // check if a message is available to be received
}


void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
