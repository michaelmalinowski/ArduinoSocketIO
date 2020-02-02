#include "WebSocketClient.h"
#include "WiFiNINA.h"

#ifndef ArduinoSocketIO_h
#define ArduinoSocketIO_h

class ArduinoSocketIO {

  private:
    WebSocketClient client;

  public:
  
    ArduinoSocketIO(WiFiClient &wifi, char server[], int port);
    
  };

#endif
