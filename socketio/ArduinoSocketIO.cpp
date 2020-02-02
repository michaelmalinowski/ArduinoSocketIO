#include "ArduinoSocketIO.h"

ArduinoSocketIO::ArduinoSocketIO(WiFiClient &wifi, char server[], int port) : client(wifi, server, port){
}
