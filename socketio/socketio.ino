#include <WiFiNINA.h>
#include <SPI.h>
#include "ArduinoSocketIO.h"

char ssid[] = "Amigo";        // your network SSID (name)
char pass[] = "ginatony";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiClient wifi;
int port = 80;
char server[] = "10.0.0.6";
ArduinoSocketIO socket(wifi, server, port, 10);

void event1(String data){
  socket.emit("hello", "WE IN THE FUNCTION");
}


void setup(){
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  //while (!Serial) { // wait for serial port to connect. Needed for native USB port only}
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
  socket.on("hello", event1);

  socket.startConnection();
  socket.emit("hello", "YOOO");
}

void loop(){
  socket.eventListener();
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
