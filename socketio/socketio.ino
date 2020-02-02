#include <WiFiNINA.h>
#include <SPI.h>

#include "ArduinoSocketIO.h"


WiFiClient wifi;
int port = 80;
char server[] = "localhost";
ArduinoSocketIO socket(wifi, server, port);

void setup(){

}

void loop(){

}
